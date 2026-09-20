add_link_options(-static-libgcc -static-libstdc++)
set(P_NAME "CacheCleaner")
set(P_DESCRIPTION "CacheCleaner - console utility for clean usused trash files.Learn More at: https://github.com/SG123it/CacheCleaner")
set(P_VER 1.0)

cmake_minimum_required(VERSION 3.10...3.30)
project(${P_NAME} VERSION ${P_VER})

set(SRC
    "src/main.cpp"
    "src/JSONworker.cpp"
    "src/Folderworker.cpp"
    "src/Interactive.cpp"
)
include_directories(
    "header"
    "include/argparse-master/include"
    "include/json-master/single_include"
)

add_executable(${P_NAME} ${SRC})
target_compile_definitions(${P_NAME} PRIVATE VERSION="${P_VER}")
target_compile_definitions(${P_NAME} PRIVATE ProgramName="${P_NAME}")
target_compile_definitions(${P_NAME} PRIVATE ProgramDescription="${P_DESCRIPTION}")
