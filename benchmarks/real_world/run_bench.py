import json
import subprocess

EXE = r"d:\patch-viewer\target\release\patch-viewer.exe"
CASES = ["cjson_setval", "cjson_dup_depth", "lz4_errcodes", "httpparser_oob", "httpparser_exec"]


def run_diff(old_c, new_c, mode="full"):
    args = [EXE, "--json"]
    if mode == "raw":
        args += [
            "--no-addr-norm",
            "--no-var-norm",
            "--no-comment-strip",
            "--no-cfg-align",
            "--no-decl-collapse",
        ]
    elif mode == "nocfg":
        args += ["--no-cfg-align"]
    args += [old_c, new_c]
    out = subprocess.check_output(args, text=True)
    return json.loads(out)


def main():
    for name in CASES:
        old_c = rf"d:\patch-viewer\benchmarks\real_world\pseudocode\{name}_old.c"
        new_c = rf"d:\patch-viewer\benchmarks\real_world\pseudocode\{name}_new.c"
        raw = run_diff(old_c, new_c, "raw")["summary"]
        nocfg = run_diff(old_c, new_c, "nocfg")["summary"]
        full_res = run_diff(old_c, new_c, "full")
        pv = full_res["summary"]
        tags = {}
        for r in full_res["rows"]:
            t = r.get("cfg_tag")
            if t:
                k = t["type"]
                tags[k] = tags.get(k, 0) + 1
        r_sem = raw["semantic_added_rows"] + raw["semantic_removed_rows"] + raw["semantic_modified_rows"]
        n_sem = nocfg["semantic_added_rows"] + nocfg["semantic_removed_rows"] + nocfg["semantic_modified_rows"]
        p_sem = pv["semantic_added_rows"] + pv["semantic_removed_rows"] + pv["semantic_modified_rows"]
        print(f"{name:<16} | raw={r_sem:4d} | nocfg={n_sem:4d} (noise={nocfg['noise_filtered_rows']:3d}) | full={p_sem:4d} (+{pv['semantic_added_rows']} -{pv['semantic_removed_rows']} ~{pv['semantic_modified_rows']}, noise={pv['noise_filtered_rows']:3d}, cfg={pv['cfg_reorders_aligned']}) | tags={tags}")


if __name__ == "__main__":
    main()
