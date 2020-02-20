# Alexa Auto SDK C++ Sample App

cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

option(SAI_BUILD_FOR_LINUX_ARM32 "build for arm-linux-gnueabihf-" OFF)
option(SAI_BUILD_FOR_LINUX_ARM64 "build for aarch64-linux-gnu-" OFF)
option(SAI_BUILD_FOR_MUSL_OPENWRT "build for arm-openwrt-linux-" OFF)
option(SAI_BUILD_FOR_GLIBC_OPENWRT "build for arm-openwrt-glibc-linux-" OFF)
option(SAI_BUILD_FOR_Android_32 "build for Android armeabi-v7a" OFF)
option(SAI_BUILD_FOR_Android_64 "build for Android arm64-v8a" OFF)
option(SAI_BUILD_FOR_LINUX_X86_64 "build for x86_64-linux-gnu-" OFF)

option(SAI_ENABLE_BUILD_OPENDENOISE "only used in this CMake" OFF)
option(SAI_ENABLE_DEBUG_PCM_LOCAL "enable write RAW/WK/ASR pcm files for debug" OFF)

if((SAI_BUILD_FOR_LINUX_ARM32) OR (SAI_BUILD_FOR_LINUX_ARM64) OR (SAI_BUILD_FOR_MUSL_OPENWRT) OR (SAI_BUILD_FOR_GLIBC_OPENWRT))
    add_definitions(-DSAI_SDK_INTEGRATE_OPENDENOISE)
    set(SAI_ENABLE_BUILD_OPENDENOISE  ON)
endif()

if((SAI_BUILD_FOR_GLIBC_OPENWRT))
    add_definitions(-DSAI_READ_ASR_DATA)
    add_definitions(-DSAI_BUILD_FOR_GLIBC_OPENWRT)
endif()

option(SAI_ENABLE_MIGU "enable migu service for arm-linux-gnueabihf-" OFF)

project(sai_client LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
    message("No build type specified, defaulting to DEBUG.")
endif()

set(CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG -Wall -Wno-covered-switch-default -Wno-missing-braces -O2 -fPIC")
set(CMAKE_CXX_FLAGS_DEBUG "-DDEBUG -Wall -Wno-covered-switch-default -Wno-missing-braces -g -fPIC")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")
if (CMAKE_BUILD_TYPE STREQUAL "Debug" AND CMAKE_GENERATOR STREQUAL "Unix Makefiles" AND CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -fprofile-instr-generate -fcoverage-mapping")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-instr-generate")
endif()

if (SAI_BUILD_FOR_LINUX_X86_64)
	if (NOT PORTAUDIO)
	    message( FATAL_ERROR "Must enable PORTAUDIO for x86_64-linux platform" )
	endif()
	set(SAI_ENABLE_BUILD_OPENDENOISE  ON)
	add_definitions(-DSAI_BUILD_FOR_LINUX_X86_64)
endif()

if (SAI_ENABLE_BUILD_OPENDENOISE)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DSAI_ENABLE_BUILD_OPENDENOISE")
endif()

if (SAI_BUILD_FOR_LINUX_X86_64)
	set (CXX_HEADER_FILES
		${CMAKE_CURRENT_SOURCE_DIR}/include/azero_sdk_api.h
	    ${CMAKE_CURRENT_SOURCE_DIR}/include/azero_sdk_operator.h
		${CMAKE_CURRENT_SOURCE_DIR}/src/PortAudioMicrophoneWrapper.h )
	set (CXX_SOURCE_FILES
		${CXX_SOURCE_FILES}
		${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/src/PortAudioMicrophoneWrapper.cpp )
else()
	set(CXX_HEADER_FILES
	    ${CMAKE_CURRENT_SOURCE_DIR}/include/azero_sdk_api.h
	    ${CMAKE_CURRENT_SOURCE_DIR}/include/azero_sdk_operator.h
	    ${CMAKE_CURRENT_SOURCE_DIR}/include/sai_micbasex_interface.h
	)
	set(CXX_SOURCE_FILES
	    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
	)
endif()
add_executable(sai_client
    ${CXX_HEADER_FILES}
    ${CXX_SOURCE_FILES}
)

target_include_directories(sai_client PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include> # <prefix>/include
)

if((SAI_BUILD_FOR_LINUX_ARM32) AND (SAI_ENABLE_BUILD_OPENDENOISE))
    target_link_libraries(sai_client
        ${CMAKE_CURRENT_SOURCE_DIR}/link-libs/arm-linux-gnueabihf/lib/libAzeroOS.so
        ${CMAKE_CURRENT_SOURCE_DIR}/link-libs/arm-linux-gnueabihf/lib/libAzeroCBL.so
        ${CMAKE_CURRENT_SOURCE_DIR}/link-libs/arm-linux-gnueabihf/lib/libAzeroNVG.so
        ${CMAKE_CURRENT_SOURCE_DIR}/link-libs/arm-linux-gnueabihf/lib/libAzeroEngine.so
        ${CMAKE_CURRENT_SOURCE_DIR}/link-libs/arm-linux-gnueabihf/lib/libAzeroCore.so
        ${CMAKE_CURRENT_SOURCE_DIR}/link-libs/arm-linux-gnueabihf/libvlc/libvlc.so.5
        ${CMAKE_CURRENT_SOURCE_DIR}/link-libs/arm-linux-gnueabihf/libvlc/libvlccore.so.9
        ${CMAKE_CURRENT_SOURCE_DIR}/link-libs/arm-linux-gnueabihf/libvlc/libidn.so
        ${CMAKE_CURRENT_SOURCE_DIR}/link-libs/arm-linux-gnueabihf/lib/libasound.so
        ${CMAKE_CURRENT_SOURCE_DIR}/link-libs/arm-linux-gnueabihf/lib/libsai_micbasex.so
    )
elseif((SAI_BUILD_FOR_LINUX_ARM64) AND (SAI_ENABLE_BUILD_OPENDENOISE))
    target_link_libraries(sai_client
        ${CMAKE_CURRENT_SOURCE_DIR}/link-libs/aarch64-linux-gnu/lib/libAzeroOS.so
        ${CMAKE_CURRENT_SOURCE_DIR}/link-libs/aarch64-linux-gnu/lib/libAzeroCBL.so
        ${CMAKE_CURRENT_SOURCE_DIR}/link-libs/aarch64-linux-gnu/lib/libAzeroNVG.so
        ${CMAKE_CURRENT_SOURCE_DIR}/link-libs/aarch64-linux-gnu/lib/libAzeroEngine.so
        ${CMAKE_CURRENT_SOURCE_DIR}/link-libs/aarch64-linux-gnu/lib/libAzeroCore.so
        ${CMAKE_CURRENT_SOURCE_DIR}/link-libs/aarch64-linux-gnu/libvlc/libvlc.so.5
        ${CMAKE_CURRENT_SOURCE_DIR}/link-libs/aarch64-linux-gnu/libvlc/libvlccore.so.9
        ${CMAKE_CURRENT_SOURCE_DIR}/link-libs/aarch64-linux-gnu/libvlc/libidn.so
        ${CMAKE_CURRENT_SOURCE_DIR}/link-libs/aarch64-linux-gnu/lib/libasound.so
        ${CMAKE_CURRENT_SOURCE_DIR}/link-libs/aarch64-linux-gnu/lib/libsai_micbasex.so
    )
elseif((SAI_BUILD_FOR_MUSL_OPENWRT) AND (SAI_ENABLE_BUILD_OPENDENOISE)) #need to do
    target_link_libraries(sai_client
        ${CMAKE_CURRENT_SOURCE_DIR}/link-libs/arm-openwrt-musl/lib/libAzeroOS.so
        ${CMAKE_CURRENT_SOURCE_DIR}/link-libs/arm-openwrt-musl/lib/libAzeroCBL.so
        ${CMAKE_CURRENT_SOURCE_DIR}/link-libs/arm-openwrt-musl/lib/libAzeroNVG.so
        ${CMAKE_CURRENT_SOURCE_DIR}/link-libs/arm-openwrt-musl/lib/libAzeroEngine.so
        ${CMAKE_CURRENT_SOURCE_DIR}/link-libs/arm-openwrt-musl/lib/libAzeroCore.so
        ${CMAKE_CURRENT_SOURCE_DIR}/link-libs/arm-openwrt-musl/lib/libAzeroTplayer.so
        ${CMAKE_CURRENT_SOURCE_DIR}/link-libs/arm-openwrt-musl/lib/libsai_micbasex.so
        ${CMAKE_CURRENT_SOURCE_DIR}/link-libs/arm-openwrt-musl/lib/libasound.so
        -Wl,-rpath-link=${CMAKE_SOURCE_DIR}/link-libs/arm-openwrt-musl/libtp
    )
elseif((SAI_BUILD_FOR_GLIBC_OPENWRT) AND (SAI_ENABLE_BUILD_OPENDENOISE))
    target_link_libraries(sai_client
        ${CMAKE_CURRENT_SOURCE_DIR}/link-libs/arm-openwrt-glibc/lib/libAzeroOS.so
        ${CMAKE_CURRENT_SOURCE_DIR}/link-libs/arm-openwrt-glibc/lib/libAzeroCBL.so
        ${CMAKE_CURRENT_SOURCE_DIR}/link-libs/arm-openwrt-glibc/lib/libAzeroNVG.so
        ${CMAKE_CURRENT_SOURCE_DIR}/link-libs/arm-openwrt-glibc/lib/libAzeroEngine.so
        ${CMAKE_CURRENT_SOURCE_DIR}/link-libs/arm-openwrt-glibc/lib/libAzeroCore.so
        ${CMAKE_CURRENT_SOURCE_DIR}/link-libs/arm-openwrt-glibc/lib/libAVSCommon.so
        ${CMAKE_CURRENT_SOURCE_DIR}/link-libs/arm-openwrt-glibc/lib/libAzeroGplayer.so
        ${CMAKE_CURRENT_SOURCE_DIR}/link-libs/arm-openwrt-glibc/gplayer/libgplayer.so
        -Wl,-rpath-link=${CMAKE_SOURCE_DIR}/link-libs/arm-openwrt-glibc/gplayer
    )
elseif(SAI_BUILD_FOR_LINUX_X86_64)
	target_include_directories(sai_client PUBLIC
		"${INCLUDE_DIRECTORIES}"
		"${PORTAUDIO_INCLUDE_DIR}"
	)
		
    target_link_libraries(sai_client
        ${CMAKE_CURRENT_SOURCE_DIR}/link-libs/x86_64-linux/lib/libAzeroOS.so
        ${CMAKE_CURRENT_SOURCE_DIR}/link-libs/x86_64-linux/lib/libAzeroCBL.so
        ${CMAKE_CURRENT_SOURCE_DIR}/link-libs/x86_64-linux/lib/libAzeroNVG.so
        ${CMAKE_CURRENT_SOURCE_DIR}/link-libs/x86_64-linux/lib/libAzeroEngine.so
        ${CMAKE_CURRENT_SOURCE_DIR}/link-libs/x86_64-linux/lib/libAzeroCore.so
        ${CMAKE_CURRENT_SOURCE_DIR}/link-libs/x86_64-linux/lib/libAVSCommon.so
        ${CMAKE_CURRENT_SOURCE_DIR}/link-libs/x86_64-linux/lib/libAzeroGStreamer.so
        ${CMAKE_CURRENT_SOURCE_DIR}/link-libs/x86_64-linux/lib/libSQLiteStorage.so
        "${PORTAUDIO_LIB_PATH}"
        asound
    )
endif()

if(CMAKE_SYSTEM_NAME MATCHES "Darwin")
    if(PORTAUDIO)
        target_link_libraries(sai_client 
            "-framework CoreAudio"
            "-framework AudioToolbox"
            "-framework AudioUnit"
            "-framework CoreServices"
            "-framework Carbon"
        )
    endif()
endif()

if(NOT CMAKE_SYSTEM_NAME MATCHES "(Darwin)")
    # AACE modules must be explicitly linked
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--no-as-needed")
endif()

install(
    TARGETS sai_client
    DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}
)
