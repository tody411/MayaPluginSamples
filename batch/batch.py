# -*- coding: utf-8 -*-
## @package batch
#
#  Generate Maya batch files for testing plug-ins.
#  @author      Tody
#  @date        2015/03/18

import os
import re

## directories ignored by toolDirs().
ignore_dirs = [".git", "batch", "build", "cmake"]

## Autodesk location for Maya installation path.
autodesk_location = "C:/Program Files/Autodesk"

## Return the bach directory.
def batchDir():
    return os.path.dirname(__file__)

## Return the tool root directory.
def toolRootDir():
    batch_dir = batchDir()
    return os.path.abspath(os.path.dirname(batch_dir))


## Return the list of tool directories.
#
#  ignore_dirs are not included in tool_dirs
def toolDirs():
    dirs = os.listdir(toolRootDir())

    tool_dirs = []
    for tool_dir in dirs:
        if tool_dir in ignore_dirs:
            continue
        tool_dir = os.path.join(toolRootDir() , tool_dir)

        if os.path.isdir(tool_dir):
            tool_dirs.append(tool_dir)
    return tool_dirs


## Return plug-in directory.
def pluginDir(tool_dir):
    return os.path.abspath(os.path.join(tool_dir, "plugins"))


## Return mell script directory.
def melScriptDir(tool_dir):
    return os.path.abspath(os.path.join(tool_dir, "scripts", "mel"))


## Return python script directory.
def pythonScriptDir(tool_dir):
    return os.path.abspath(os.path.join(tool_dir, "scripts", "python"))


## Return icon directory.
def iconDir(tool_dir):
    return os.path.abspath(os.path.join(tool_dir, "icons"))


## Return the batch file path for the target version and language.
def batchFile(version, lang):
    return os.path.join(batchDir(), "Maya%s_%s.bat" %(version, lang))


## Set plug-in environment variable.
def pluginPathEnv(f, tool_dir):
    appendPathEnv(f, "MAYA_PLUG_IN_PATH", pluginDir(tool_dir))

## Set mell environment variable.
def melScriptPathEnv(f, tool_dir):
    appendPathEnv(f, "MAYA_SCRIPT_PATH", melScriptDir(tool_dir))


## Set python environment variable.
def pythonScriptPathEnv(f, tool_dir):
    appendPathEnv(f, "PYTHONPATH", pythonScriptDir(tool_dir))


## Set icon environment variable.
def iconPathEnv(f, tool_dir):
    appendPathEnv(f, "XBMLANGPATH", iconDir(tool_dir))


## Append a path to exiting path environment variable.
#
#  set path_name=%path_name%;dir_path
def appendPathEnv(f, path_name, dir_path):
    if not os.path.exists(dir_path):
        return

    rel_path = os.path.relpath(dir_path, toolRootDir())
    print "%s: %s" % (path_name, rel_path)

    f.write("set %s=%%%s%%;%s\n" %(path_name, path_name, dir_path))


## Set language environment variable.
def langEnv(lang):
    if lang == "EN":
        return "set MAYA_UI_LANGUAGE=en_US\n"
    elif lang == "JP":
        return "set MAYA_UI_LANGUAGE=ja_JP\n"


## Find Maya version from autodesk_location.
def findMayaVersions():
    search_versions = range(2010, 2017)
    versions = []

    for search_version in search_versions:
        maya_location = os.path.join(autodesk_location, "Maya%s" %search_version)

        if os.path.exists(maya_location):
            versions.append(search_version)

    return versions


## Find Maya exe from autodesk_location and version.
def findMayaEXE(version):
    maya_exe = os.path.join(autodesk_location, "Maya%s/bin/maya.exe" %version)
    maya_exe = maya_exe.replace("/", os.path.sep)
    return maya_exe

## Generate batch files for the target versions and languages.
def generateBatch(versions=findMayaVersions(), langs=["EN", "JP"]):
    print "================="
    print "Generate Maya batch files"
    print "================="
    print "Foud Maya versions: %s" % versions
    print "Target languages: %s" % langs
    print ""

    for version in versions:
        for lang in langs:
            f = open(batchFile(version, lang), 'w')

            for tool_dir in toolDirs():
                print "Tool name: %s" % os.path.basename(tool_dir)
                print "-----------------"

                pluginPathEnv(f, tool_dir)
                melScriptPathEnv(f, tool_dir)
                pythonScriptPathEnv(f, tool_dir)
                iconPathEnv(f, tool_dir)

                print ""

            f.write(langEnv(lang))
            f.write('"%s"' % findMayaEXE(version))
            f.close()

if __name__ == '__main__':
    generateBatch()