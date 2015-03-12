cmake_minimum_required(VERSION 3.0)
project(psychic_dangerzone)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

# Enable debug symbols by default
if(CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Bring in our dependencies
# Yes, threads too. Anything on Linux needs pthreads these days, basically
find_package(SFML COMPONENTS window graphics system)
find_package(Threads)

# Use C++11, because we're amazing
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
include_directories(${SFML_INCLUDE_DIR})

add_executable(psychic_dangerzone main.cpp)
target_link_libraries(psychic_dangerzone ${SFML_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})