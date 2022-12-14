#!/usr/bin/env python3

import sys
import os
import platform

from subprocess import check_output
from subprocess import CalledProcessError

# This script is adapted from https://github.com/mvendra/building/blob/master/build.py

class Builder():

    def __init__(_self, basepath, options):

        _self.basepath = basepath
        _self.options = _self.parseoptions(options)

        _self.appname = "legacy_testforecho"
        _self.compiler = "g++"

        _self.src = ["main.cpp", "test_legacy_testforecho.cpp", "test_legacy_testforecho_first.cpp", "test_legacy_testforecho_second.cpp"]

        _self.src_base = "../../self_tests/"
        _self.obj_base = "../../build/"
        _self.run_base = "../../run/"

        _self.include = []
        _self.include.append("-I%s" % _self.src_base)
        _self.include.append("-I../../include")

        _self.ldflags = []

        _self.plat = _self.getplat()
        _self.arch = _self.getarch()
        _self.mode = _self.options["mode"]

        _self.target = _self.plat + "_" + _self.arch + "_" + _self.mode

        _self.obj_full = _self.obj_base + _self.target
        _self.run_full = _self.run_base + _self.target

        _self.app_full_name = _self.run_full + "/" + _self.appname
        _self.all_objs = [x.replace("cpp", "o") for x in _self.src]

        _self.cpp_flags_common = ["-Wall", "-Wextra", "-pedantic", "-Weffc++", "-Werror", "-fPIC", "-std=c++14"] 
        _self.cpp_flags_debug = ["-g", "-D_GLIBCXX_DEBUG"]
        _self.cpp_flags_release = ["-O2"]

        _self.cpp_flags_use = _self.cpp_flags_common
        if _self.mode == "debug":
            _self.cpp_flags_use += _self.cpp_flags_debug
        elif _self.mode == "release":
            _self.cpp_flags_use += _self.cpp_flags_release

    def parseoptions(_self, options):

        opts = {}

        # fill in defaults
        opts["mode"] = "release"
        opts["target"] = "all"
        # other possible options: type (static, shared)

        if options is None:
            return opts

        if "release" in options:
            opts["mode"] = "release"
        if "debug" in options:
            opts["mode"] = "debug"

        if "clean" in options:
            opts["target"] = "clean"
        if "compile" in options:
            opts["target"] = "compile"
        if "link" in options:
            opts["target"] = "link"
        if "rebuild" in options:
            opts["target"] = "rebuild"
        if "all" in options:
            opts["target"] = "all"

        return opts

    def getplat(_self):
        ps = platform.system().lower()
        if ps == "linux":
            return "linux"
        elif ps == "windows":
            return "windows"
        elif ps == "darwin":
            return "macosx"
        else:
            return "unknown_plat"

    def getarch(_self):
        pm = platform.machine().lower()
        if pm == "x86_64":
            return "x64"
        elif pm == "amd64":
            return "x64"
        elif pm == "i686":
            return "x32"
        else:
            return "unknown_arch"

    def run(_self):

        if _self.options["target"] == "clean":
            _self.do_clean()
        elif _self.options["target"] == "compile":
            _self.do_compile()
        elif _self.options["target"] == "link":
            _self.do_link()
        elif _self.options["target"] == "rebuild":
            _self.do_rebuild()
        elif _self.options["target"] == "all":
            _self.do_all()

    def do_clean(_self):

        for o in _self.all_objs:
            cmd = ["rm"]
            full_obj = _self.obj_full + "/" + o
            cmd.append(full_obj)
            _self.call_cmd(cmd)

        cmd = ["rm", _self.app_full_name]
        _self.call_cmd(cmd)

    def do_compile(_self):

        for s in _self.src:
            cmd = [_self.compiler]
            if len(_self.include) > 0:
                for i in _self.include:
                    cmd.append(i)
            cmd += _self.cpp_flags_use
            cmd += ["-c", _self.src_base + s, "-o", _self.obj_full + "/" +  s.replace("cpp", "o")]
            _self.call_cmd(cmd)

    def do_link(_self):

        cmd = [_self.compiler, "-o", _self.app_full_name]
        cmd += [_self.obj_full + "/" + x for x in _self.all_objs]

        if len(_self.ldflags) > 0:
            for l in _self.ldflags:
                cmd.append(_self.ldflags)

        _self.call_cmd(cmd)

    def do_rebuild(_self):
        _self.do_clean()
        _self.do_all()

    def do_all(_self):
        _self.do_compile()
        _self.do_link()

    def call_cmd(_self, cmd):
        try:
            out = check_output(cmd)
            print("Command succeeded")
            return True
        except CalledProcessError as cper:
            print("Failed")
            return False

if __name__ == "__main__":

    opt = None
    if len(sys.argv) > 1:
        opt = sys.argv[1:]

    bd = Builder(os.path.abspath(os.path.dirname(sys.argv[0])), opt)
    bd.run()

