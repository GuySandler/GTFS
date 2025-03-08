cmake_minimum_required(VERSION 3.10)
project(GTFS)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(FTXUI)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE ftxui::screen ftxui::dom ftxui::component)