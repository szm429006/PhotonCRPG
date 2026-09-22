#!/bin/bash

WORKSPACE=../
LUBAN_DLL=$WORKSPACE/Plugins/Luban/Luban.dll
CONF_ROOT=.

dotnet $LUBAN_DLL \
    -t all \
    -c cpp-sharedptr-bin \
    -d bin \
    --conf $CONF_ROOT/luban.conf \
    -x outputCodeDir=$WORKSPACE/Source/PhotonCRPG/Luban/Generated \
    -x outputDataDir=$WORKSPACE/Content/Data/LubanGenerated

BIN_PATH=../../luban_examples/Projects/Cpp_sharedptr_bin/luban

cp -r $BIN_PATH/ByteBuf.cpp $WORKSPACE/Source/PhotonCRPG/Luban/
cp -r $BIN_PATH/ByteBuf.h $WORKSPACE/Source/PhotonCRPG/Luban/
cp -r $BIN_PATH/CfgBean.h $WORKSPACE/Source/PhotonCRPG/Luban/
cp -r $BIN_PATH/CommonMacros.h $WORKSPACE/Source/PhotonCRPG/Luban/
