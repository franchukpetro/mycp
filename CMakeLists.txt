cmake_minimum_required(VERSION 3.10)
project(mycp)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost COMPONENTS system filesystem program_options REQUIRED)

include_directories(${Boost_INCLUDE_DIR})

add_executable(mycp mycp.cpp utils.cpp utils.h)

target_link_libraries(mycp
        ${Boost_LIBRARIES}
        )