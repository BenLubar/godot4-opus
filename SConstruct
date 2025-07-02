#!/usr/bin/env python
import os

env = SConscript("godot-cpp/SConstruct")

env.Append(CPPDEFINES=["GDOPUS_STANDALONE"])

libname = "gdopus"
projectdir = "demo"

sources = SConscript("./SCsub", {"env": env})

if env["target"] in ["editor", "template_debug"]:
    try:
        doc_data = env.GodotCPPDocData("src/gen/doc_data.gen.cpp", source=Glob("doc_classes/*.xml"))
        sources.append(doc_data)
    except AttributeError:
        print("Not including class reference as we're targeting a pre-4.3 baseline.")

file = "{}{}{}".format(libname, env["suffix"], env["SHLIBSUFFIX"])

if env["platform"] == "macos" or env["platform"] == "ios":
    platlibname = "{}.{}.{}".format(libname, env["platform"], env["target"])
    file = "{}.framework/{}".format(env["platform"], platlibname, platlibname)

libraryfile = "bin/{}/{}".format(env["platform"], file)
library = env.SharedLibrary(libraryfile, source=sources)

copy = env.InstallAs("{}/bin/{}/lib{}".format(projectdir, env["platform"], file), library)

Default(library, copy)
