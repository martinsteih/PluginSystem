cmake_minimum_required(VERSION 3.8)

set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 17)

project( "PluginRuntime" "CXX")

add_subdirectory( "Plugin" )
add_subdirectory( "Runtime" )