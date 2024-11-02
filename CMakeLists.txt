cmake_minimum_required(VERSION 3.10)
project(tape_sort)

set(CMAKE_CXX_STANDARD 17)

find_package (Threads REQUIRED)

find_package(jsoncpp CONFIG REQUIRED)
include_directories(include)

add_executable(tape_sort src/tape_sort.cpp src/Tape.cpp src/ConfigParser.cpp src/TapeSorter.cpp)
target_link_libraries(tape_sort PRIVATE jsoncpp_lib  ${CMAKE_THREAD_LIBS_INIT})


add_executable(tape_recorder utils/tape_recorder.cpp src/Tape.cpp src/ConfigParser.cpp)
target_link_libraries(tape_recorder PRIVATE jsoncpp_lib)

add_executable(tape_reader utils/tape_reader.cpp src/Tape.cpp src/ConfigParser.cpp)
target_link_libraries(tape_reader PRIVATE jsoncpp_lib)


enable_testing()

add_executable(sort_test tests/sort_test.cpp src/Tape.cpp src/TapeSorter.cpp)
target_link_libraries(sort_test PRIVATE ${CMAKE_THREAD_LIBS_INIT})


add_test(NAME SortTest COMMAND sort_test)