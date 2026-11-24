import json
import os
import subprocess

base = "/mnt/disk4/patch_viewer_bench"
out = os.path.join(base, "out")
os.makedirs(out, exist_ok=True)

cases = [
    {
        "name": "cjson_setval",
        "repo": "cJSON",
        "commit": "d6d5449",
        "old_symbol": "cJSON_SetValuestring",
        "new_symbol": "cJSON_SetValuestring",
        "cflags": ["-O2"],
        "srcs": ["cJSON.c"],
        "driver": """
#include "cJSON.h"
#include <stdio.h>
int main(int argc, char **argv) {
    cJSON *item = cJSON_CreateString(argc > 1 ? argv[1] : "hello");
    char *r = cJSON_SetValuestring(item, argc > 2 ? argv[2] : "world");
    return r ? 0 : 1;
}
""",
    },
    {
        "name": "cjson_dup_depth",
        "repo": "cJSON",
        "commit": "9d1b229",
        "old_symbol": "cJSON_Duplicate",
        "new_symbol": "cJSON_Duplicate_rec",
        "cflags": ["-O2"],
        "srcs": ["cJSON.c"],
        "driver": """
#include "cJSON.h"
int main(int argc, char **argv) {
    cJSON *root = cJSON_Parse(argc > 1 ? argv[1] : "{}");
    cJSON *dup = cJSON_Duplicate(root, argc > 2);
    return dup ? 0 : 1;
}
""",
    },
    {
        "name": "lz4_errcodes",
        "repo": "lz4",
        "commit": "b67d3f5",
        "old_symbol": "LZ4_decompress_safe",
        "new_symbol": "LZ4_decompress_safe",
        "cflags": ["-O2", "-Ilib"],
        "srcs": ["lib/lz4.c"],
        "driver": """
#include "lz4.h"
static char dst_buf[4096];
int main(int argc, char **argv) {
    const char *src = argc > 1 ? argv[1] : "abcd";
    return LZ4_decompress_safe(src, dst_buf, argc, sizeof(dst_buf));
}
""",
    },
    {
        "name": "httpparser_oob",
        "repo": "http-parser",
        "commit": "9ce7316",
        "old_symbol": "http_parser_parse_url",
        "new_symbol": "http_parser_parse_url",
        "cflags": ["-O3"],
        "srcs": ["http_parser.c"],
        "driver": """
#include "http_parser.h"
#include <string.h>
int main(int argc, char **argv) {
    struct http_parser_url u;
    const char *url = argc > 1 ? argv[1] : "http://example.com:8080/a";
    http_parser_url_init(&u);
    return http_parser_parse_url(url, strlen(url), 0, &u);
}
""",
    },
    {
        "name": "httpparser_exec",
        "repo": "http-parser",
        "commit": "7d5c99d",
        "old_symbol": "http_parser_execute",
        "new_symbol": "http_parser_execute",
        "cflags": ["-O2"],
        "srcs": ["http_parser.c"],
        "driver": """
#include "http_parser.h"
#include <string.h>
static int on_url(http_parser *p, const char *at, size_t len) { return (int)len; }
int main(int argc, char **argv) {
    http_parser parser;
    http_parser_settings settings;
    const char *req = argc > 1 ? argv[1] : "GET / HTTP/1.1\\r\\nHost: a\\r\\n\\r\\n";
    memset(&settings, 0, sizeof(settings));
    settings.on_url = on_url;
    http_parser_init(&parser, HTTP_REQUEST);
    return (int)http_parser_execute(&parser, &settings, req, strlen(req));
}
""",
    },
]

manifest = []
for c in cases:
    repo_dir = os.path.join(base, c["repo"])
    driver_path = os.path.join(out, f"{c['name']}_driver.c")
    with open(driver_path, "w") as df:
        df.write(c["driver"])

    entry = {
        "name": c["name"],
        "repo": c["repo"],
        "commit": c["commit"],
        "cflags": c["cflags"],
        "old_symbol": c["old_symbol"],
        "new_symbol": c["new_symbol"],
    }
    for tag, rev in [("old", f"{c['commit']}~1"), ("new", c["commit"])]:
        subprocess.run(["git", "-C", repo_dir, "checkout", "-q", rev], check=True)
        bin_path = os.path.join(out, f"{c['name']}_{tag}.elf")
        cmd = (
            ["gcc"]
            + c["cflags"]
            + [f"-I{repo_dir}"]
            + [os.path.join(repo_dir, s) for s in c["srcs"]]
            + [driver_path, "-o", bin_path]
        )
        subprocess.run(cmd, check=True)
        sym = c[f"{tag}_symbol"]
        nm_out = subprocess.check_output(["nm", "-n", bin_path], text=True)
        addr = None
        for line in nm_out.splitlines():
            parts = line.split()
            if len(parts) >= 3 and parts[2] == sym:
                addr = int(parts[0], 16)
                break
        if addr is None:
            for line in nm_out.splitlines():
                parts = line.split()
                if len(parts) >= 3 and parts[1].lower() == "t" and parts[2].startswith(sym):
                    addr = int(parts[0], 16)
                    entry[f"{tag}_matched_sym"] = parts[2]
                    break
        subprocess.run(["strip", "--strip-all", bin_path], check=True)
        entry[f"{tag}_bin"] = os.path.basename(bin_path)
        entry[f"{tag}_addr"] = hex(addr) if addr is not None else None
    manifest.append(entry)

with open(os.path.join(out, "manifest.json"), "w") as f:
    json.dump(manifest, f, indent=2)
print(json.dumps(manifest, indent=2))
