cmake_minimum_required(VERSION 3.15)
project(database_scratch LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Executable
add_executable(database_scratch
    src/main.cpp
    src/cli/cli.cpp
    src/db/database.cpp
    src/db/kv_store.cpp
)

target_include_directories(database_scratch PUBLIC include)