cmake_minimum_required(VERSION 2.6.4)
project(HydrovoltsConnect)

#There are lots of scripts with cmake
#for finding external libraries. 
#see /usr/local/share/cmake-2.6/Modules/Find*.cmake for more examples
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

# Find libs we depend on
find_package(Boost COMPONENTS system filesystem signals REQUIRED)
find_package(Wt)

# -ggdb = gdb debug symbols
# -g = debug symbols
# -Wall = Show all warnings
# set(CMAKE_CXX_FLAGS "-g")
add_subdirectory(src)
