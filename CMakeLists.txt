cmake_minimum_required(VERSION 3.0)
project(psychic_dangerzone)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

find_package(SFML COMPONENTS window graphics system)
find_package(Threads)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(${SFML_INCLUDE_DIR})

message(${SFML_LIBRARIES})
add_executable(psychic_dangerzone main.cpp)
target_link_libraries(psychic_dangerzone ${SFML_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})