set(P_NAME "CacheCleaner")
set(P_DESCRIPTION "CacheCleaner - console utility for clean usused trash files.Learn More at: https://github.com/SG123it/CacheCleaner")
set(P_VER 1.0)

file(WRITE "version.txt" "${P_VER}")

cmake_minimum_required(VERSION 3.10...3.30)
project(${P_NAME} VERSION ${P_VER})

set(SRC
    "src/main.cpp"
    "src/JSONworker.cpp"
    "src/Folderworker.cpp"
    "src/Interactive.cpp"
    "src/RequestWorker.cpp"
)
include_directories(
    "header"
    "include/argparse-master/include"
    "include/json-master/single_include"
)

set(CPR_USE_SYSTEM_CURL OFF)
set(CPR_CURL_USE_LIBPSL OFF)
include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git GIT_TAG f091b2c061b307ee89b164c39976fc9202a1c79d)
FetchContent_MakeAvailable(cpr)

add_executable(${P_NAME} ${SRC})
target_link_libraries(${P_NAME} PUBLIC cpr::cpr)

target_compile_definitions(${P_NAME} PRIVATE VERSION="${P_VER}")
target_compile_definitions(${P_NAME} PRIVATE ProgramName="${P_NAME}")
target_compile_definitions(${P_NAME} PRIVATE ProgramDescription="${P_DESCRIPTION}")
