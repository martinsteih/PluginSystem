cmake_minimum_required(VERSION 3.8)

include_directories("../RtRuntime/include")
add_executable( "Runtime" "IPlugin.hpp" "DlLoad.hpp" "DlLoad.cpp" "Source.cpp" )
target_link_libraries("Runtime" "RtRuntime" -ldl -lrt -lpthread -lboost_system)