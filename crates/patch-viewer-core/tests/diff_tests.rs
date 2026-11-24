use patch_viewer_core::{diff_pseudocode, CfgReorderTag, ChangeKind, DiffOptions};

#[test]
fn test_address_and_comment_normalization() {
    let old = r#"__int64 __fastcall sub_140012A40(__int64 a1)
{
  int v3; // [rsp+20h] [rbp-18h] BYREF

  v3 = sub_140001000(a1, qword_140050000);
  return (unsigned int)v3;
}"#;
    let new = r#"__int64 __fastcall sub_140019B00(__int64 a1)
{
  int v7; // [rsp+30h] [rbp-28h] BYREF

  v7 = sub_140002800(a1, qword_140061200);
  return (unsigned int)v7;
}"#;

    let res = diff_pseudocode(old, new, &DiffOptions::default());
    assert_eq!(res.summary.semantic_added_rows, 0);
    assert_eq!(res.summary.semantic_removed_rows, 0);
    assert_eq!(res.summary.semantic_modified_rows, 0);
    assert!(res.summary.noise_filtered_rows >= 4);
}

#[test]
fn test_variable_shift_does_not_pollute_after_inserted_check() {
    let old = r#"int __fastcall sub_401000(int *a1)
{
  int v3; // eax
  int v4; // ebx

  v3 = *a1;
  v4 = sub_402000(v3);
  return v4 + 1;
}"#;
    let new = r#"int __fastcall sub_401500(int *a1)
{
  int v3; // ecx
  int v4; // eax
  int v5; // ebx

  v4 = *a1;
  v3 = v4 + 4;
  if ( v3 > 100 )
    return -1;
  v5 = sub_402800(v4);
  return v5 + 1;
}"#;

    let res = diff_pseudocode(old, new, &DiffOptions::default());
    // Inserted lines `int v3;`, `v3 = v4 + 4;`, `if ( v3 > 100 )`, `return -1;` should be Added,
    // while `v5 = sub_402800(v4);` and `return v5 + 1;` must be NoiseOnly (not Modified!).
    assert_eq!(res.summary.semantic_modified_rows, 0);
    assert_eq!(res.summary.semantic_removed_rows, 0);
    assert!(res.summary.semantic_added_rows >= 3);

    let call_row = res
        .rows
        .iter()
        .find(|r| {
            r.old_line
                .as_ref()
                .map(|l| l.raw_text.contains("sub_402000"))
                .unwrap_or(false)
        })
        .expect("call row exists");
    assert_eq!(call_row.kind, ChangeKind::NoiseOnly);
}

#[test]
fn test_if_else_branch_inversion_aligned() {
    let old = r#"int __fastcall sub_401000(int a1)
{
  if ( a1 == 16 )
  {
    sub_401100(a1);
    return 1;
  }
  else
  {
    sub_401200(a1);
    return 0;
  }
}"#;
    let new = r#"int __fastcall sub_402000(int a1)
{
  if ( a1 != 16 )
  {
    sub_402200(a1);
    return 0;
  }
  else
  {
    sub_402100(a1);
    return 1;
  }
}"#;

    let res = diff_pseudocode(old, new, &DiffOptions::default());
    assert_eq!(res.summary.semantic_modified_rows, 0);
    assert_eq!(res.summary.semantic_added_rows, 0);
    assert_eq!(res.summary.semantic_removed_rows, 0);
    assert!(res
        .rows
        .iter()
        .any(|r| matches!(r.cfg_tag, Some(CfgReorderTag::BranchInverted { .. }))));
}

#[test]
fn test_guard_clause_vs_nested_if_aligned() {
    let old = r#"int __fastcall sub_401000(int *a1)
{
  int v2; // eax

  if ( !a1 )
    return -1;
  v2 = *a1;
  sub_401100(v2);
  return 0;
}"#;
    let new = r#"int __fastcall sub_402000(int *a1)
{
  int v3; // eax

  if ( a1 )
  {
    v3 = *a1;
    sub_402100(v3);
    return 0;
  }
  return -1;
}"#;

    let res = diff_pseudocode(old, new, &DiffOptions::default());
    assert_eq!(res.summary.semantic_modified_rows, 0);
    assert!(res
        .rows
        .iter()
        .any(|r| matches!(r.cfg_tag, Some(CfgReorderTag::GuardFlattened { .. }))));
    let body_row = res
        .rows
        .iter()
        .find(|r| {
            r.old_line
                .as_ref()
                .map(|l| l.raw_text.contains("sub_401100"))
                .unwrap_or(false)
        })
        .expect("aligned body call row");
    assert_eq!(body_row.kind, ChangeKind::NoiseOnly);
}

#[test]
fn test_switch_case_reordering_aligned() {
    let old = r#"void __fastcall sub_401000(int a1)
{
  switch ( a1 )
  {
    case 1:
      sub_401010();
      break;
    case 2:
      sub_401020();
      break;
    case 3:
      sub_401030();
      break;
  }
}"#;
    let new = r#"void __fastcall sub_402000(int a1)
{
  switch ( a1 )
  {
    case 3:
      sub_402030();
      break;
    case 1:
      sub_402010();
      break;
    case 2:
      sub_402020();
      break;
  }
}"#;

    let res = diff_pseudocode(old, new, &DiffOptions::default());
    assert_eq!(res.summary.semantic_modified_rows, 0);
    assert_eq!(res.summary.semantic_added_rows, 0);
    assert_eq!(res.summary.semantic_removed_rows, 0);
    assert!(res
        .rows
        .iter()
        .any(|r| matches!(r.cfg_tag, Some(CfgReorderTag::CaseReordered { .. }))));
}

#[test]
fn test_goto_label_block_relocation_aligned() {
    let old = r#"int __fastcall sub_401000(int a1)
{
  if ( a1 < 0 )
    goto loc_401080;
  sub_401100(a1);
  return 0;

loc_401080:
  sub_401900(a1);
  return -1;
}"#;
    let new = r#"int __fastcall sub_402000(int a1)
{
  if ( a1 < 0 )
    goto loc_402020;
  goto loc_402050;

loc_402020:
  sub_402900(a1);
  return -1;

loc_402050:
  sub_402100(a1);
  return 0;
}"#;

    let res = diff_pseudocode(old, new, &DiffOptions::default());
    assert!(res
        .rows
        .iter()
        .any(|r| matches!(r.cfg_tag, Some(CfgReorderTag::LabelMoved { .. }))));
    let err_call = res
        .rows
        .iter()
        .find(|r| {
            r.old_line
                .as_ref()
                .map(|l| l.raw_text.contains("sub_401900"))
                .unwrap_or(false)
        })
        .expect("error label call matched");
    assert_eq!(err_call.kind, ChangeKind::NoiseOnly);
}

#[test]
fn test_cve_example_pair_isolates_security_patch() {
    let old = include_str!("../../../examples/cve_patch_old.c");
    let new = include_str!("../../../examples/cve_patch_new.c");

    let with_opt = diff_pseudocode(old, new, &DiffOptions::default());
    let without_opt = diff_pseudocode(
        old,
        new,
        &DiffOptions {
            ignore_comments: false,
            normalize_addresses: false,
            sequential_address_numbering: false,
            normalize_variables: false,
            collapse_declarations: false,
            simplify_ida_casts: false,
            align_control_flow: false,
            hide_noise_lines: false,
        },
    );

    let sem_with = with_opt.summary.semantic_added_rows
        + with_opt.summary.semantic_removed_rows
        + with_opt.summary.semantic_modified_rows;
    let sem_without = without_opt.summary.semantic_added_rows
        + without_opt.summary.semantic_removed_rows
        + without_opt.summary.semantic_modified_rows;

    // Without normalization/CFG alignment almost the whole file differs;
    // with it enabled, semantic changes collapse down to only the CVE patch + wrapper braces!
    assert!(sem_with < sem_without / 3, "sem_with={sem_with}, sem_without={sem_without}");
    assert!(with_opt.summary.cfg_reorders_aligned >= 3);
    assert!(with_opt.summary.noise_filtered_rows >= 20);
}

#[test]
fn test_hexrays_label_n_fnptr_decl_and_do_loop_container() {
    let old = r#"__int64 __fastcall sub_401000(unsigned __int8 *a1, int a2)
{
  unsigned int (__fastcall *v5)(__int64, char *); // rax
  unsigned __int8 *i; // rsi
  int v7; // ecx

  v7 = 0;
  i = a1;
LABEL_3:
  if ( *i == 58 )
  {
    v7 = 1;
    goto LABEL_18;
  }
  ++i;
  if ( --a2 )
    goto LABEL_3;
  return 0LL;

LABEL_18:
  v5 = (unsigned int (__fastcall *)(__int64, char *))sub_401200;
  return v5(a2, "ok");
}"#;

    let new = r#"__int64 __fastcall sub_402000(unsigned __int8 *a1, int a2)
{
  unsigned __int8 *j; // rsi
  int v8; // ecx
  unsigned int (__fastcall *v6)(__int64, char *); // rax

  v8 = 0;
  j = a1;
  do
  {
    if ( *j == 58 )
    {
      v8 = 1;
      goto LABEL_25;
    }
    ++j;
    --a2;
  }
  while ( a2 );
  return 0LL;

LABEL_25:
  v6 = (unsigned int (__fastcall *)(__int64, char *))sub_402200;
  return v6(a2, "ok");
}"#;

    let res = diff_pseudocode(old, new, &DiffOptions::default());
    // Both LABEL_18 <-> LABEL_25 and function pointer declaration + i <-> j should be NoiseOnly
    assert!(res.summary.noise_filtered_rows >= 8);
    let label_call = res
        .rows
        .iter()
        .find(|r| {
            r.old_line
                .as_ref()
                .map(|l| l.raw_text.contains("sub_401200"))
                .unwrap_or(false)
        })
        .expect("aligned label block call");
    assert_eq!(label_call.kind, ChangeKind::NoiseOnly);
}

