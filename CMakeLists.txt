cmake_minimum_required(VERSION 3.14...3.27)

project(
    GAFT
    VERSION 0.1
    DESCRIPTION "Library, GUI, and CLI to flatten and tag file trees."
    LANGUAGES CXX
)

# if main project
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set(CMAKE_CXX_STANDARD 20)
    #set(CMAKE_CXX_EXTENSIONS OFF)

    set_property(GLOBAL PROPERTY USE_FOLDERS ON)

    find_package(Doxygen)
    if(DOXYGEN_FOUND)
        add_subdirectory(docs)
    else()
        message(STATUS "Doxygen not found. Not building Docs.")
    endif()
endif()

# dependencies
include(FetchContent)

FetchContent_Declare(
  Boost
  GIT_REPOSITORY https://github.com/boostorg/boost.git
  GIT_TAG boost-1.83.0
)

FetchContent_MakeAvailable(Boost)
find_package(Boost)

FetchContent_Declare(raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib
    GIT_TAG "master"
    GIT_PROGRESS TRUE
)

FetchContent_MakeAvailable(raylib)
find_package(raylib)

add_subdirectory(src)
add_subdirectory(apps)
