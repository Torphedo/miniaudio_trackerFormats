cmake_minimum_required(VERSION 3.13)
project(ma_tracker_formats
    LANGUAGES C
)

set(CMAKE_C_STANDARD 99)

include_directories(
    lib/it2play
)

add_subdirectory(lib/it2play)
add_library(ibxm STATIC lib/micromod/ibxm-ac/ibxm.c)
target_include_directories(ibxm PUBLIC lib/micromod/ibxm-ac)
