import json
import os

import idapro


def main():
    base = r"d:\patch-viewer\benchmarks\real_world"
    bin_dir = os.path.join(base, "bin")
    out_dir = os.path.join(base, "pseudocode")
    os.makedirs(out_dir, exist_ok=True)

    with open(os.path.join(bin_dir, "manifest.json"), "r", encoding="utf-8") as f:
        manifest = json.load(f)

    for item in manifest:
        name = item["name"]
        for side in ("old", "new"):
            bin_path = os.path.join(bin_dir, item[f"{side}_bin"])
            addr_hex = item[f"{side}_addr"]
            sym = item[f"{side}_symbol"]
            if not addr_hex:
                print(f"[SKIP] {name} ({side}): no address in manifest")
                continue
            raw_off = int(addr_hex, 16)
            print(f"[IDA] Opening {bin_path} -> target {addr_hex} ({sym})")
            idapro.open_database(bin_path, True)
            import ida_auto
            import ida_funcs
            import ida_hexrays
            import ida_nalt

            ida_auto.auto_wait()
            if not ida_hexrays.init_hexrays_plugin():
                raise RuntimeError("Hex-Rays plugin failed to initialize")

            base_ea = ida_nalt.get_imagebase()
            ea = raw_off
            func = ida_funcs.get_func(ea)
            if func is None and base_ea != 0:
                ea = base_ea + raw_off
                func = ida_funcs.get_func(ea)
            if func is None:
                # Attempt creating function if IDA didn't auto-create it yet
                ida_funcs.add_func(ea)
                ida_auto.auto_wait()
                func = ida_funcs.get_func(ea)

            if func is None:
                print(f"[ERR] {name} ({side}): could not locate function at {hex(ea)} (base={hex(base_ea)})")
            else:
                cfunc = ida_hexrays.decompile(func.start_ea)
                code = str(cfunc)
                out_file = os.path.join(out_dir, f"{name}_{side}.c")
                with open(out_file, "w", encoding="utf-8") as outf:
                    outf.write(code)
                print(f"[OK] Saved {out_file} ({len(code.splitlines())} lines, start_ea={hex(func.start_ea)})")

            idapro.close_database(False)


if __name__ == "__main__":
    main()
