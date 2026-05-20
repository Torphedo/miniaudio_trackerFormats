cmake_minimum_required(VERSION 3.13)
project(ma_tracker_formats
    LANGUAGES C
)

set(CMAKE_C_STANDARD 99)

include_directories(
    lib/it2play
)

set(it2play_SOURCE_DIR ${ma_tracker_formats_SOURCE_DIR}/lib/it2play)

# Bypass normal it2play build script because it tries to find and link with SDL
file(GLOB it2play_SRC
    "${it2play_SOURCE_DIR}/loaders/mmcmp/*.c"
    "${it2play_SOURCE_DIR}/loaders/*.c"
    "${it2play_SOURCE_DIR}/it2drivers/*.c"
    "${it2play_SOURCE_DIR}/*.c"
    "${it2play_SOURCE_DIR}/it2play/src/*.c"
)

add_library(IT2 STATIC ${it2play_SRC} ${it2play_SOURCE_DIR}/audiodrivers/null/nulldriver.c)
target_compile_definitions(IT2 PRIVATE AUDIODRIVER_NULL)

add_library(ibxm STATIC lib/micromod/ibxm-ac/ibxm.c)
target_include_directories(ibxm PUBLIC lib/micromod/ibxm-ac)
