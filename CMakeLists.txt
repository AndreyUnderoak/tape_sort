cmake_minimum_required(VERSION 3.10)
project(tape_sort)

find_package(jsoncpp CONFIG REQUIRED)
include_directories(include)

add_executable(tape_sort src/tape_sort.cpp src/Tape.cpp src/ConfigParser.cpp)
target_link_libraries(tape_sort PRIVATE jsoncpp_lib)


add_executable(tape_recorder utils/tape_recorder.cpp src/Tape.cpp src/ConfigParser.cpp)
target_link_libraries(tape_recorder PRIVATE jsoncpp_lib)

add_executable(tape_reader utils/tape_reader.cpp src/Tape.cpp src/ConfigParser.cpp)
target_link_libraries(tape_reader PRIVATE jsoncpp_lib)
