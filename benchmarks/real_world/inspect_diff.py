import json
import subprocess

EXE = r"d:\patch-viewer\target\release\patch-viewer.exe"
for name in ["cjson_setval", "cjson_dup_depth", "lz4_errcodes", "httpparser_oob", "httpparser_exec"]:
    old_c = rf"d:\patch-viewer\benchmarks\real_world\pseudocode\{name}_old.c"
    new_c = rf"d:\patch-viewer\benchmarks\real_world\pseudocode\{name}_new.c"
    j = json.loads(subprocess.check_output([EXE, "--json", old_c, new_c], text=True))
    s = j["summary"]
    print(f"=== {name} (+{s['semantic_added_rows']} -{s['semantic_removed_rows']} ~{s['semantic_modified_rows']} | noise={s['noise_filtered_rows']} | cfg={s['cfg_reorders_aligned']}) ===")
    shown = 0
    for r in j["rows"]:
        tag = r.get("cfg_tag")
        if tag and tag.get("type") == "DeclarationBlock":
            continue
        if r["kind"] in ("Added", "Removed", "Modified"):
            o_no = r["old_line"]["line_no"] if r["old_line"] else "-"
            n_no = r["new_line"]["line_no"] if r["new_line"] else "-"
            o = r["old_line"]["raw_text"] if r["old_line"] else ""
            n = r["new_line"]["raw_text"] if r["new_line"] else ""
            print(f"  {r['kind']:8} | O:{str(o_no):>4} {o[:45]:<45} | N:{str(n_no):>4} {n[:45]}")
            shown += 1
            if shown >= 30:
                break
