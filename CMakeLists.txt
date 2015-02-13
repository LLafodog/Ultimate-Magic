project(Ultimate_Magic)
set(EXECUTABLE_OUTPUT_PATH bin/)
cmake_minimum_required( VERSION 2.8)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SFML2 REQUIRED sfml-graphics>=2.1)

file(

GLOB_RECURSE

src_file

include/*.hpp
src/*.cpp
./main.cpp
)

add_definitions(-std=c++11)
include_directories(

include/
)

add_executable(

Ultimate_Magic

${src_file}
)

target_link_libraries(

Ultimate_Magic
sfml-graphics
sfml-window
sfml-system
)