cmake_minimum_required(VERSION 2.8)

include($ENV{DEVKIT_LOCATION}/cmake/pluginEntry.cmake)

set(PROJECT_NAME dojoStretchyIK)

set(SOURCE_FILES
        pluginMain.cpp
        DojoStretchyIK.cpp
        DojoStretchyIK.h)

set(LIBRARIES
        OpenMaya
        Foundation)

build_plugin()

