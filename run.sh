#!/usr/bin/env bash
if [ "$#" -eq 0 ]; then
echo "Note: build script for Azero demo"
echo "Usage: ./run.sh {arm-linux-gnueabihf|arm32-openwrt|aarch64-gnu|aarch64-poky-linux|arm32-poky|armeabi-v7a|arm64-v8a}"
exit 0
fi


# reset modify
#git checkout   CMakeLists.txt
sed -i "s#option(SAI_BUILD_FOR_LINUX_ARM32.*#option(SAI_BUILD_FOR_LINUX_ARM32 \"build for arm-linux-gnueabihf-\" OFF)#g" CMakeLists.txt
sed -i "s#option(SAI_BUILD_FOR_LINUX_ARM64.*#option(SAI_BUILD_FOR_LINUX_ARM64 \"build for aarch64-linux-gnu-\" OFF)#g" CMakeLists.txt
sed -i "s#option(SAI_BUILD_FOR_OPENWRT.*#option(SAI_BUILD_FOR_OPENWRT \"build for arm-openwrt-linux-\" OFF)#g"  CMakeLists.txt

# config CMake for linux arm64
#sed -i "s#option(SAI_BUILD_FOR_LINUX_ARM64.*#option(SAI_BUILD_FOR_LINUX_ARM64 \"build for aarch64-linux-gnu-\" ON)#g" CMakeLists.txt

BUILD_DIR=build_demo
if [ "$1" = "clean" ]; then
rm -rf "$BUILD_DIR" sai_client
exit 0
fi

# clean last builed
rm -rf "$BUILD_DIR"

echo "Gonna make with $*..."

if [ "$1" = "linux64-x86" ]; then
    CMAKE_OPTS="-DCMAKE_TOOLCHAIN_FILE=./toolchain-cmake/linux64-toolchain.cmake"
elif [ "$1" = "openwrt" ];then
    CMAKE_OPTS="-DCMAKE_TOOLCHAIN_FILE=./toolchain-cmake/openwrt-toolchain.cmake"
elif [ "$1" = "arm-linux-gnueabihf" ];then
    sed -i "s#option(SAI_BUILD_FOR_LINUX_ARM32.*#option(SAI_BUILD_FOR_LINUX_ARM32 \"build for arm-linux-gnueabihf-\" ON)#g" CMakeLists.txt
    CMAKE_OPTS="-DCMAKE_TOOLCHAIN_FILE=./toolchain-cmake/arm-linux-gnueabihf-toolchain.cmake"
elif [ "$1" = "arm32-openwrt" ];then
    sed -i "s#option(SAI_BUILD_FOR_OPENWRT.*#option(SAI_BUILD_FOR_OPENWRT \"build for arm-openwrt-linux-\" ON)#g"  CMakeLists.txt
    CMAKE_OPTS="-DCMAKE_TOOLCHAIN_FILE=./toolchain-cmake/arm32-openwrt-toolchain.cmake"
elif [ "$1" = "aarch64-poky-linux" ];then
    CMAKE_OPTS="-DCMAKE_TOOLCHAIN_FILE=./toolchain-cmake/aarch64-poky-linux-toolchain.cmake"
elif [ "$1" = "poky32" ];then
    CMAKE_OPTS="-DCMAKE_TOOLCHAIN_FILE=./toolchain-cmake/poky32-linux-toolchain.cmake"
elif [ "$1" = "armeabi-v7a" ];then
    CMAKE_OPTS="-DCMAKE_TOOLCHAIN_FILE=./toolchain-cmake/armeabi-v7a-toolchain.cmake"
elif [ "$1" = "aarch64-gnu" ];then
    sed -i "s#option(SAI_BUILD_FOR_LINUX_ARM64.*#option(SAI_BUILD_FOR_LINUX_ARM64 \"build for aarch64-linux-gnu-\" ON)#g" CMakeLists.txt
    CMAKE_OPTS="-DCMAKE_TOOLCHAIN_FILE=./toolchain-cmake/aarch64-gnu-toolchain.cmake"
fi

TARGET=$1
BUILD_TYPE=debug
if [ -n "$2" ] ;then
    BUILD_TYPE=$2
fi


mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"


cmake $CMAKE_OPTS \
    -DCMAKE_BUILD_TYPE=$BUILD_TYPE \
    -DCMAKE_VERBOSE_MAKEFILE=ON  ../

    
make & make install
