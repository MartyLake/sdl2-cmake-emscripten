#!/bin/bash
set -euo
set -x #debug mode

# Generate clang_complete file
CLANG_COMPLETE_DIR="build_native" #so that the json works for native compile
if [ ! -d $CLANG_COMPLETE_DIR ]
then
    rm -rf $CLANG_COMPLETE_DIR
fi
mkdir -p $CLANG_COMPLETE_DIR
pushd $CLANG_COMPLETE_DIR
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
mv compile_commands.json ..
rm -rf ./*
CCARGS=$HOME/.vim/bundle/clang_complete/bin/cc_args.py
chmod a+x $CCARGS
CXX="$CCARGS clang++" cmake ..
make
mv .clang_complete ..
popd
rm -rf $CLANG_COMPLETE_DIR

BUILD_DIR_NATIVE="build_native"
if [ ! -d $BUILD_DIR_NATIVE ]
then
    mkdir -p $BUILD_DIR_NATIVE
fi

pushd $BUILD_DIR_NATIVE
cmake .. 
popd



BUILD_DIR_EM="build_em"
if [ ! -d $BUILD_DIR_EM ]
then
    mkdir -p $BUILD_DIR_EM
fi

if [ -z "${EMSCRIPTEN-}" ]
then
    source ../../DevTools/emsdk/emsdk_env.sh
fi

pushd $BUILD_DIR_EM
cmake -DCMAKE_TOOLCHAIN_FILE=$EMSCRIPTEN/cmake/Modules/Platform/Emscripten.cmake  ..
popd

