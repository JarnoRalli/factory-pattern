cmake_minimum_required(VERSION 3.12)

project(Factory_pattern VERSION 1.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)

if(MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

add_library(my_library SHARED
    singleton.hpp
    factory.hpp
    object.hpp
    object.cpp)

target_include_directories(my_library
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

add_executable(main main.cpp)

target_link_libraries(main my_library)