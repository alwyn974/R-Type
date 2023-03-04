cmake_minimum_required(VERSION 3.17)
project(
        R-Type-Server
        VERSION 1.0.1.0
        DESCRIPTION "Server Part of the R-Type Project"
        HOMEPAGE_URL "https://github.com/alwyn974/R-Type"
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(BINARY_NAME "r-type_server")

add_executable(${BINARY_NAME} main.cpp

)

# Include all headers directories
target_include_directories(${BINARY_NAME}
        PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
        PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
        )

find_package(tomlplusplus 3.3.0 REQUIRED)
find_package(nlohmann_json 3.11.2 REQUIRED)

target_link_libraries(${BINARY_NAME}
        PUBLIC
            R-Type-Common
            tomlplusplus
            nlohmann_json
)

# Enable warnings, will not work on header only libraries
target_compile_options(${BINARY_NAME} PRIVATE
        $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>: -Wall -Wextra>
        $<$<CXX_COMPILER_ID:MSVC>: /W4>
)

# Set some properties
set_target_properties(${BINARY_NAME} PROPERTIES VERSION ${PROJECT_VERSION} SOVERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR})
set_target_properties(${BINARY_NAME} PROPERTIES DEBUG_POSTFIX "-debug")

# Set the startup project in Visual Studio
if (MSVC)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${BINARY_NAME})
    message(STATUS "Setting startup project to ${BINARY_NAME}")
endif (MSVC)

if (USE_CLANG_TIDY OR USE_CLANG_TIDY_WITH_ERRORS OR USE_CLANG_TIDY_WITH_FIX)
    find_program(CLANG_TIDY_EXE NAMES "clang-tidy-16")
    if (NOT CLANG_TIDY_EXE)
        message(WARNING "clang-tidy not found.")
    else ()
        message(STATUS "clang-tidy found: ${CLANG_TIDY_EXE}")
        if (USE_CLANG_TIDY_WITH_FIX)
            set(CLANG_TIDY_COMMMAND "${CLANG_TIDY_EXE}" "--fix" "--config-file=${CMAKE_CURRENT_SOURCE_DIR}/.clang-tidy")
        elseif (USE_CLANG_TIDY_WITH_ERRORS)
            set(CLANG_TIDY_COMMMAND "${CLANG_TIDY_EXE}" "--warnings-as-errors=*" "--config-file=${CMAKE_CURRENT_SOURCE_DIR}/.clang-tidy")
        else ()
            set(CLANG_TIDY_COMMMAND "${CLANG_TIDY_EXE}" "--config-file=${CMAKE_CURRENT_SOURCE_DIR}/.clang-tidy")
        endif ()
        set_target_properties(${BINARY_NAME} PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_COMMMAND}")
    endif ()
endif ()

