cmake_minimum_required(VERSION 3.17)
project(
        R-Type
        VERSION 1.0.1.0
        DESCRIPTION "R-Type is a 2D space shooter game"
        HOMEPAGE_URL "https://github.com/alwyn974/R-Type"
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)
# Make project-provided Find modules available
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

option(RTYPE_BUILD_TESTS "Build tests" OFF)
option(RTYPE_INSTALL "Install R-Type" ON)
option(RTYPE_CPACK "Create the installer" OFF)
option(USE_CLANG_TIDY "Use clang-tidy" OFF) # Used by the CI
option(USE_CLANG_TIDY_WITH_ERRORS "Use clang tidy but all warnings are errors" OFF) # Used by the CI
option(USE_CLANG_TIDY_WITH_FIX "Use clang-tidy with fix" OFF) # Used by the CI
option(BUILD_SHARED_LIBS "Build shared libraries" OFF) # Fix dll issues on Windows

add_subdirectory(common)
add_subdirectory(client)
add_subdirectory(server)
