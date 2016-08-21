cmake_minimum_required(VERSION 2.8)

project(unittest)

file(GLOB_RECURSE SOURCE *.cpp)

add_executable(${PROJECT_NAME} ${SOURCE})
target_compile_options(${PROJECT_NAME} PUBLIC -std=c++11 -Wall -Werror)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include .)
target_link_libraries(${PROJECT_NAME} trains)
