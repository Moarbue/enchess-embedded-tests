#!/bin/sh

set -xe

echo -e "cmake_minimum_required(VERSION 3.5)\nidf_component_register(SRCS \"src/TMC2209.cpp\"\n                    INCLUDE_DIRS \"src/.\"\n                    REQUIRES \"arduino\"\n                    )\n\nproject(TMC2209)" > components/TMC2209/CMakeLists.txt