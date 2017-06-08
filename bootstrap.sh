#!/bin/bash
set -euo
set -x #debug mode

BUILD_DIR_NATIVE="build_native"
if [ ! -d $BUILD_DIR_NATIVE ]
then
    mkdir -p $BUILD_DIR_NATIVE
fi

cd $BUILD_DIR_NATIVE
cmake .. 
cd -


BUILD_DIR_EM="build_em"
if [ ! -d $BUILD_DIR_EM ]
then
    mkdir -p $BUILD_DIR_EM
fi

cd $BUILD_DIR_EM
cmake -DCMAKE_TOOLCHAIN_FILE=$EMSCRIPTEN/cmake/Modules/Platform/Emscripten.cmake  ..
cd -

