#!/bin/env python

import sys
import time
Import("env")


# print("\n\nCurrent CLI targets:", COMMAND_LINE_TARGETS)
# print("Current Build targets:\n", BUILD_TARGETS)


def check_ram_usage(target, source, env):
    memory_stats = env["PROGNAME"] + ".map"
    map_file = env.subst("$BUILD_DIR/") + memory_stats

    # print("\n\nmemory_stats: %s" % memory_stats)
    # print("map_file:     %s\n" % map_file)

    try:
        content = {}
        with open(map_file, "r") as file:
            content = file.read()

        memZones = (".bss", ".noinit", ".data")
        ram_usage = 0
        for line in content.splitlines():
            if not line.startswith(memZones):
                continue

            pp = line.split()
            size = 0
            size = int(pp[2], 0)

            ram_usage += size

        ram_perc = (ram_usage / int(env.GetProjectOption("max_ram")) * 100)
        print("RAM USAGE:   %d / %d [%.2f%%]" %
              (ram_usage, int(env.GetProjectOption("max_ram")), ram_perc))
        print("FLASH FLASH: N/A / %d" % int(env.GetProjectOption("max_flash")))

        if ram_perc > float(env.GetProjectOption("max_ram_perc")):
            print("RAM USAGE EXCEEDS LIMIT")
            sys.exit(1)

    except FileNotFoundError:
        print("Coult not find map_file %s" % map_file)
        sys.exit(1)


env.AddPreAction("upload", check_ram_usage)
