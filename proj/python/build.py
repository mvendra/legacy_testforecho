#!/usr/bin/env python

import sys
import os

from subprocess import check_output
from subprocess import CalledProcessError

class Builder():

    def __init__(_self, basepath, options):

        _self.basepath = basepath
        _self.options = options
        if _self.options is None:
            _self.options = "all"

        _self.appname = "testforecho"
        _self.compiler = "g++"

        _self.src = ["main.cpp", "test_testforecho.cpp"]

        _self.src_base = "../../src/"
        _self.obj_base = "../../build/"
        _self.run_base = "../../run/"

        _self.include = "-I%s" % _self.src_base
        _self.ldflags = ""

        _self.plat = "linux"
        _self.arch = "x64"
        _self.mode = "debug"

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
            _self.cpp_flags_use.join += _self.cpp_flags_release

    def run(_self):

        if _self.options == "clean":
            _self.do_clean()
        elif _self.options == "compile":
            _self.do_compile()
        elif _self.options == "link":
            _self.do_link()
        elif _self.options == "rebuild":
            _self.do_rebuild()
        elif _self.options == "all":
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
            if _self.include is not "":
                cmd.append(_self.include)
            cmd += _self.cpp_flags_use
            cmd += ["-c", _self.src_base + s, "-o", _self.obj_full + "/" +  s.replace("cpp", "o")]
            _self.call_cmd(cmd)

    def do_link(_self):

        cmd = [_self.compiler, "-o", _self.app_full_name]
        cmd += [_self.obj_full + "/" + x for x in _self.all_objs]
        if _self.ldflags is not "":
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
        opt = sys.argv[1]

    bd = Builder(os.path.abspath(os.path.dirname(sys.argv[0])), opt)
    bd.run()

