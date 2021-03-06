# -*- coding: utf-8 -*-
## @package tool_ui
#
#  Provide plug-in tool GUI.
#  @author      Tody
#  @date        2015/03/18

import os
import sys
import re

import maya.cmds as cmds
import maya.mel as mel

## directories ignored by toolDirs().
ignore_dirs = [".git", "batch", "build", "cmake", "toolUI"]

## Window UI ID.
window_id = 'ToolWindow'


## Return Maya Version.
#
#  @return [version, architecture] e.g. ["2015", "64"] means Maya 2015 64-bit.
def mayaVersion():
    res = ["", ""]
    architecture = "32";
    is64bits = cmds.about(is64=True)
    if is64bits:
        architecture = "64"
    versionString = cmds.about(version=True)
    version = ""
    if re.match(".*2014.*", versionString):
        version = "2014"
    elif re.match(".*2015.*", versionString):
        version = "2015"
    elif re.match(".*2016.*", versionString):
        version = "2016"
    else:
        print "Unknown Maya version :" + versionString

    res[0] = version;
    res[1] = architecture;
    return res


## Return Maya plug-in file name for target toolName.
#
#  @return pluginFileName    examples: NoiseDeformer2014.mll (tool name "NoiseDeformer", Maya 2014)
def getMllName(tool_name):
    maya_version = mayaVersion()
    res = tool_name + maya_version[0]
    res = res + '.mll'
    return res


## Return the tool root directory.
def toolRootDir():
    return os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))

## Return the list of tool names.
#
#  ignore_dirs are not included in tool_names
def toolNames():
    dirs = os.listdir(toolRootDir())

    tool_names = []
    for tool_name in dirs:
        if tool_name in ignore_dirs:
            continue
        tool_dir = os.path.join(toolRootDir() , tool_name)

        if os.path.isdir(tool_dir):
            tool_names.append(tool_name)
    return tool_names

## Tool load command for target plug-in names and optional mel command.
#
#   @param    plugin_names    [plugin_name1, plugin_name2, ...] list of plug-in names.
#   @param    ui_mel           Mel command to launch tool UI.
#   @param    ui_python        Python command to launch tool UI.
def toolLoadCmd(plugin_names, ui_mel=None, ui_python=None):
    def cmdFunction(*args):
        for pluginName in plugin_names:
            cmds.loadPlugin(pluginName)
        if ui_mel is not None:
            mel.eval(ui_mel)
        if ui_python is not None:
            ui_python()
    return cmdFunction


## Create tool menue for target tool.
#  @param    tool_name       target tool name.
#  @param    plugin_names    target plug-in names which will be loaded.
#  @param    ui_mel          Mel command to launch tool UI.
def toolMenue(tool_name, plugin_names, ui_mel=None, ui_python=None):
    tool_root_dir = toolRootDir()
    print "Tool Root",tool_root_dir
    tool_dir = tool_root_dir + '/' + tool_name

    print '-----------------'
    print '%s menue' % (tool_name)

    if not os.path.exists(tool_dir):
        print 'Error: Tool Directory is not found.'
        return

    cmds.menu(label=tool_name, tearOff=True)
    cmds.menuItem(label="Load Plugin", command=toolLoadCmd(plugin_names, ui_mel=ui_mel, ui_python=ui_python))

    print '------------------'


## Create  Tool UI.
def toolUI():
    cmds.window (window_id, title='Maya Tools', menuBar=True, toolbox=True, widthHeight=[350, 80])

    for tool_name in toolNames():
        toolMenue(tool_name, [getMllName(tool_name)])

#     toolMenue('NoiseCmd', [getMllName('NoiseCmd')])
#     toolMenue('NoiseDeformer', [getMllName('NoiseDeformer')])
#     toolMenue('LaplacianSmoother',  [getMllName('LaplacianSmoother')])
#     toolMenue('OpenMeshCmd',  [getMllName('OpenMeshCmd')])
    cmds.showWindow (window_id)

