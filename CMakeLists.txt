cmake_minimum_required(VERSION 2.8)

project(trains)

file(GLOB_RECURSE sources source/*.cpp include/*.h)

add_executable(${PROJECT_NAME} ${sources})

target_link_libraries(${PROJECT_NAME} glut GL)

target_compile_options(${PROJECT_NAME} PUBLIC -std=c++11 -Wall -Werror)

target_include_directories(${PROJECT_NAME} PUBLIC 
    ./include
)

