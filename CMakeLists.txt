set(P_NAME "CacheCleaner")
set(P_VER 1.0)

cmake_minimum_required(VERSION 3.10...3.30)
project(${P_NAME} VERSION ${P_VER})

set(SRC
    "src/main.cpp"
)

add_executable(${P_NAME} ${SRC})