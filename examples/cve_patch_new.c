__int64 __fastcall sub_140013F80(__int64 a1, unsigned int *a2, unsigned int a3)
{
  int v4; // r12d
  unsigned int v5; // edi
  unsigned int v6; // esi
  unsigned int v7; // eax
  __int64 v8; // rbx
  void *v9; // r14
  int v10; // [rsp+28h] [rbp-40h] BYREF
  char v11[32]; // [rsp+30h] [rbp-38h] BYREF

  v10 = 0;
  if ( a2 )
  {
    if ( a3 < 0x10 )
      return 3221225485LL;
    v5 = *a2;
    v6 = a2[1];
    v7 = a2[2];
    v8 = qword_14009A100;
    if ( !qword_14009A100 )
      return 3221225473LL;
    switch ( v5 )
    {
      case 5u:
        v10 = sub_140005C10(v8, v6);
        break;
      case 1u:
        sub_140005800(a1, 1LL);
        break;
      case 2u:
        sub_140005920(a1, v6);
        break;
      default:
        goto loc_140014090;
    }
    if ( v7 != 0x100 )
    {
      sub_140006BF0(a1, v7, &v10);
    }
    else
    {
      v4 = v6 + 16;
      if ( v6 > 0x400 || v6 + 16 < v6 )
        goto loc_140014090;
      v9 = (void *)sub_140006870(v4);
      if ( !v9 )
        goto loc_140014090;
      sub_140006890(v9, a2 + 4, v6);
      sub_140006A10(a1, v9, v6);
    }
    sub_140007010(v11, 32LL);
    return 0LL;

loc_140014090:
    sub_140007620(a1, (unsigned int)dword_14009A240);
    return 3221225473LL;
  }
  return 3221225485LL;
}
