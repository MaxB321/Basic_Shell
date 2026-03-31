cmake_minimum_required(VERSION 4.3)

project(basic_shell)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp")

add_executable(basic_shell ${SOURCES})

target_include_directories(basic_shell PRIVATE headers)
