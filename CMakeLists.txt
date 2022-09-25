cmake_minimum_required(VERSION 3.20)

project(Factory_pattern VERSION 1.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)

#---------------------------
# Build the factory-library
#---------------------------
option(BUILD_SHARED "Build a shared version of the library" ON)

if(${BUILD_SHARED})
    add_library(factory SHARED
        dll_support.hpp
        singleton.hpp
        factory.hpp
        object.hpp
        object.cpp)
    if(MSVC)
        # FACTORY_DLL indicates that we're building a shared version (dll) of the library
        add_compile_definitions(FACTORY_DLL)
        # FACTORY_BUILD indicates that we need to export symbols using dllexport
        target_compile_definitions(factory PRIVATE FACTORY_BUILD)
    endif()
else()
    add_library(factory STATIC
        dll_support.hpp
        singleton.hpp
        factory.hpp
        object.hpp
        object.cpp)
endif()

target_include_directories(factory
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)

#---------------------------
# Build the main-executable
#---------------------------
add_executable(main main.cpp)
target_link_libraries(main factory)
