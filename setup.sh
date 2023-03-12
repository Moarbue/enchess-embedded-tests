#!/bin/sh

set -xe

echo 'cmake_minimum_required(VERSION 3.5)
file(GLOB SRC "src/source/*.cpp")
idf_component_register(SRCS ${SRC}
                       INCLUDE_DIRS "src/."
                       REQUIRES "arduino"
)
project(TMCStepper)' > components/TMCStepper/CMakeLists.txt