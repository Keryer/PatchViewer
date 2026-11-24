import os
import traceback

import ida_auto
import ida_funcs
import ida_hexrays
import ida_nalt
import idc


def run():
    if len(idc.ARGV) < 3:
        raise RuntimeError(f"Expected 2 args (addr_hex, out_path), got {idc.ARGV}")
    raw_off = int(idc.ARGV[1], 16)
    out_path = idc.ARGV[2]

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
        ida_funcs.add_func(ea)
        ida_auto.auto_wait()
        func = ida_funcs.get_func(ea)

    if func is None:
        raise RuntimeError(f"Could not locate function at {hex(raw_off)} (imagebase={hex(base_ea)})")

    cfunc = ida_hexrays.decompile(func.start_ea)
    if cfunc is None:
        raise RuntimeError(f"Hex-Rays decompile returned None for {hex(func.start_ea)}")

    os.makedirs(os.path.dirname(out_path), exist_ok=True)
    with open(out_path, "w", encoding="utf-8") as f:
        f.write(str(cfunc))


try:
    run()
except Exception:
    err_path = idc.ARGV[2] + ".err" if len(idc.ARGV) >= 3 else r"d:\patch-viewer\benchmarks\real_world\idat_err.txt"
    with open(err_path, "w", encoding="utf-8") as ef:
        ef.write(traceback.format_exc())
finally:
    idc.qexit(0)
