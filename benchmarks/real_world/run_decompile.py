import json
import os
import subprocess

IDAT64 = r"C:\Program Files\IDA Professional 9.0\idat64.exe"
BASE = r"d:\patch-viewer\benchmarks\real_world"
BIN_DIR = os.path.join(BASE, "bin")
OUT_DIR = os.path.join(BASE, "pseudocode")
SCRIPT = os.path.join(BASE, "idat_export.py")


def main():
    os.makedirs(OUT_DIR, exist_ok=True)
    with open(os.path.join(BIN_DIR, "manifest.json"), "r", encoding="utf-8") as f:
        manifest = json.load(f)

    for item in manifest:
        name = item["name"]
        for side in ("old", "new"):
            bin_path = os.path.join(BIN_DIR, item[f"{side}_bin"])
            addr = item[f"{side}_addr"]
            out_c = os.path.join(OUT_DIR, f"{name}_{side}.c")
            err_file = out_c + ".err"
            if os.path.exists(err_file):
                os.remove(err_file)
            if os.path.exists(out_c):
                os.remove(out_c)

            script_arg = f'-S{SCRIPT} {addr} {out_c}'
            cmd = [IDAT64, "-A", "-c", script_arg, bin_path]
            print(f"[RUN] {name} ({side}) @ {addr} -> {out_c}")
            proc = subprocess.run(cmd, capture_output=True, text=True, timeout=120)

            # Clean up IDA sidecar database files
            for ext in (".i64", ".id0", ".id1", ".id2", ".nam", ".til"):
                sidecar = bin_path + ext
                if os.path.exists(sidecar):
                    try:
                        os.remove(sidecar)
                    except OSError:
                        pass

            if os.path.exists(err_file):
                with open(err_file, "r", encoding="utf-8") as ef:
                    print(f"[ERR] {name} ({side}):\n{ef.read()}")
            elif os.path.exists(out_c):
                with open(out_c, "r", encoding="utf-8") as cf:
                    lines = cf.read().splitlines()
                print(f"[OK] {out_c}: {len(lines)} lines")
            else:
                print(f"[FAIL] {name} ({side}): exit={proc.returncode}, stderr={proc.stderr}")


if __name__ == "__main__":
    main()
