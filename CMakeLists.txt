add_link_options(-static-libgcc -static-libstdc++)
set(P_NAME "CacheCleaner")
set(P_VER 1.0)

cmake_minimum_required(VERSION 3.10...3.30)
project(${P_NAME} VERSION ${P_VER})

set(SRC
    "src/main.cpp"
)
include_directories(
    "header"
    "include/argparse-master/include"
    "include/json-master/single_include"
)

add_executable(${P_NAME} ${SRC})
target_compile_definitions(${P_NAME} PRIVATE VERSION=${P_VER})
