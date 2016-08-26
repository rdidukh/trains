cmake_minimum_required(VERSION 2.8)

project(trains)

set(LIB_NAME ${PROJECT_NAME}_static)

file(GLOB_RECURSE sources source/*.cpp include/*.h)
list(REMOVE_ITEM sources "source/main.cpp")

add_library(${PROJECT_NAME} STATIC ${sources})
target_compile_options(${PROJECT_NAME} PUBLIC -std=c++11 -Wall -Werror)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_executable(trains.bin source/main.cpp)
target_link_libraries(trains.bin trains glut GL jsoncpp)
target_compile_options(trains.bin PUBLIC -std=c++11 -Wall -Werror)
target_include_directories(trains.bin PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_subdirectory(unittest)

