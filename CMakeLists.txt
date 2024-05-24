cmake_minimum_required(VERSION 3.20)

project(Factory_pattern VERSION 1.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)

#---------------------------
# Build the factory-library
#---------------------------
option(BUILD_SHARED "Build a shared version of the library" ON)

if(${BUILD_SHARED})
    add_library(factory SHARED
        include/factory/dll_support.hpp
        include/factory/singleton.hpp
        include/factory/factory.hpp
        include/factory/object.hpp
        object.cpp)
    if(MSVC)
        # FACTORY_DLL indicates that we're building a shared version (dll) of the library
        add_compile_definitions(FACTORY_DLL)
        # FACTORY_BUILD indicates that we need to export symbols using dllexport
        target_compile_definitions(factory PRIVATE FACTORY_BUILD)
    endif()
else()
    add_library(factory STATIC
        include/factory/dll_support.hpp
        include/factory/singleton.hpp
        include/factory/factory.hpp
        include/factory/object.hpp
        object.cpp)
endif()

target_include_directories(factory
    PUBLIC 
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        include
)

#---------------------------
# Installation instructions
#---------------------------
include(GNUInstallDirs)

# Export the target
install(TARGETS factory
        EXPORT factoryTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# Install the headers (nice one liner format)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# Export the targets to a script
install(EXPORT factoryTargets
        FILE
            factoryTargets.cmake
        NAMESPACE
            factory::
        DESTINATION
            ${CMAKE_INSTALL_LIBDIR}/cmake/factory
)

# Add helper functions for creating config files that allow other projects to use this library
include(CMakePackageConfigHelpers)

# Create a configuration version file
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/factoryConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

# Create a configuration file
configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/factoryConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/factoryConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/factory
    PATH_VARS CMAKE_INSTALL_INCLUDEDIR CMAKE_INSTALL_LIBDIR
)

# Install the version- and configuration files
install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/factoryConfig.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/factoryConfigVersion.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/factory
)

#------------------------------
# Add an alias for the library
#------------------------------
# Add an alias so that library can be used inside the build tree, e.g. when testing
add_library(factory::factory ALIAS factory)

#---------------------------
# Build the main-executable
#---------------------------
add_executable(main main.cpp)
target_link_libraries(main factory::factory)
