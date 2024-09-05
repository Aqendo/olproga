import sys
import re
import asyncio
import os
from os import getenv, path, remove


async def main():
    download_path = "main1.cpp"
    includes = []
    os.system("cp main.cpp main1.cpp")
    with open(download_path, "r+") as f:
        data = f.read()
        includes = re.findall(r"^\#include .*$", data, flags=re.MULTILINE)
        for i in includes:
            data = data.replace(i, "")
        f.seek(0)
        f.truncate(0)
        f.write(data)
    result_path = "result.cpp"
    process = await asyncio.create_subprocess_exec(
        "g++", "-E", "-nostdinc", "-C", download_path, "-o", result_path
    )
    await process.wait()
    if process.returncode != 0:
        exit(1)
    process = await asyncio.create_subprocess_exec(
        "clang-format", "--style=Google", "-i", result_path
    )
    await process.wait()
    if process.returncode != 0:
        exit(1)
    if path.exists(result_path):
        with open(result_path, "r+") as f:
            data = f.read()
            data = re.sub(r"^\# .*$", "", data, flags=re.MULTILINE)
            data = data.strip()
            data = "#include <bits/stdc++.h>\n\n" + data
            f.seek(0)
            f.truncate(0)
            f.write(data)
            print("ok")
    else:
        exit(1)


asyncio.run(main())
