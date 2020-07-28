cmake_minimum_required(VERSION 2.8)

include($ENV{DEVKIT_LOCATION}/cmake/pluginEntry.cmake)

set(PROJECT_NAME basicNode)

set(SOURCE_FILES
        pluginMain.cpp
        BasicNode.cpp
        BasicNode.h)

set(LIBRARIES
        OpenMaya
        Foundation)

build_plugin()

