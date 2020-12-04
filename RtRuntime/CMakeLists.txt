cmake_minimum_required(VERSION 3.8)

file(GLOB_RECURSE SRC CONFIGURE_DEPENDS "src/*.h" "src/*.cpp" "include/*.hpp")

add_library("RtRuntime" STATIC ${SRC})