cmake_minimum_required (VERSION 3.12)

project (bomberman VERSION 1.0.1)

message(STATUS "")
message(STATUS "    == ${PROJECT_NAME} Project configuration ==")
message(STATUS "")

#------------------------------------------------------------------------------
# General settings

# Be nice to visual studio
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Be nice and export compile commands by default, this is handy for clang-tidy
# and for other tools.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# We can use include() and find_package() for our scripts in there
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/)
include(ConfigSafeGuards)

# Set C++17
set(CMAKE_CXX_STANDARD 17)

# Enable helpfull warnings and c++17 for all files
if(MSVC)
    add_compile_options(/std:c++17 /W4 /MT )
else()
    add_compile_options(-std=c++17 -Wall -Wextra -Wshadow -Wnon-virtual-dtor -Wunused -Wpedantic -pedantic-errors -Wconversion)
endif()

#------------------------------------------------------------------------------
# Project settings

# Source code
add_subdirectory(src)

# Wrap up of settings printed on build
message(STATUS "")
message(STATUS "    == Final overview for ${PROJECT_NAME} ==")
message(STATUS "Version:              ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")
message(STATUS "Install prefix:       ${CMAKE_INSTALL_PREFIX}")
message(STATUS "Compiler:             ${CMAKE_CXX_COMPILER}")
message(STATUS "Build Type:           ${CMAKE_BUILD_TYPE}")
