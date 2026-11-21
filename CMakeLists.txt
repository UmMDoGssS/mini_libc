cmake_minimum_required(VERSION 3.21)

if(NOT DEFINED CMAKE_C_COMPILER AND NOT DEFINED CMAKE_TOOLCHAIN_FILE AND "$ENV{CC}" STREQUAL "")
    find_program(MINI_CLANG NAMES clang REQUIRED)
    set(CMAKE_C_COMPILER "${MINI_CLANG}")
endif()

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
project(mini_libc LANGUAGES C ASM)

if(NOT CMAKE_C_COMPILER_ID STREQUAL "Clang")
    message(FATAL_ERROR "mini_libc requires Clang. Configure with -DCMAKE_C_COMPILER=clang.")
endif()

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(runtime_sources
    src/core/Error.c
    src/core/Memory.c
    src/platform/linux/x86_64/Start.s
    src/sys/Sys.c
)

function(add_mini_executable target source)
    add_executable(${target} ${source} ${runtime_sources})
    target_include_directories(${target} PRIVATE include src)
    target_compile_options(${target} PRIVATE
        --target=x86_64-linux-gnu
        "$<$<COMPILE_LANGUAGE:C>:-ffreestanding;-nostdinc;-Wall;-Wextra;-Wpedantic;-Werror>"
        # CMake passes configuration flags such as -O3 to assembly sources.
        "$<$<COMPILE_LANGUAGE:ASM>:-Qunused-arguments>"
    )
    target_link_options(${target} PRIVATE
        --target=x86_64-linux-gnu -nostdlib -static -Wl,-e,_start
    )
endfunction()

add_mini_executable(smoke test/Smoke.c)

include(CTest)
if(BUILD_TESTING)
    find_program(CMAKE_READELF NAMES readelf llvm-readelf REQUIRED)
    find_program(CMAKE_NM NAMES nm llvm-nm REQUIRED)

    add_mini_executable(exit-status test/SysExitTest.c)
    add_mini_executable(sys-io test/SysIoTest.c)
    add_mini_executable(sys-mmap test/SysMmapTest.c)
    add_mini_executable(sys-signal test/SysSignalTest.c)
    add_mini_executable(sys-sigaction test/SysSigActionTest.c)
    add_mini_executable(sys-abort test/SysAbortTest.c)
    add_mini_executable(memory test/MemoryTest.c)
    add_mini_executable(res test/ResTest.c)
    target_sources(res PRIVATE test/ResTestFixture.c)

    function(add_mini_test target status)
        add_test(NAME ${target}
            COMMAND "${CMAKE_COMMAND}"
                "-DEXECUTABLE=$<TARGET_FILE:${target}>"
                "-DEXPECTED_STATUS=${status}"
                "-DREADELF=${CMAKE_READELF}"
                "-DNM=${CMAKE_NM}"
                ${ARGN}
                -P "${CMAKE_CURRENT_SOURCE_DIR}/test/CheckExecutable.cmake"
        )
    endfunction()

    add_mini_test(smoke 0 "-DEXPECTED_OUTPUT=Hello, mini_libc!")
    add_mini_test(exit-status 23)
    add_mini_test(sys-io 0 -DISOLATE_FILES=ON)
    add_mini_test(sys-mmap 0 -DISOLATE_FILES=ON)
    add_mini_test(sys-signal 0)
    add_mini_test(sys-sigaction 0)
    add_mini_test(sys-abort 0)
    add_mini_test(memory 0)
    add_mini_test(res 0)
endif()
