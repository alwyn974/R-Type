cmake_minimum_required(VERSION 3.17)
project(
        R-Type-Client
        VERSION 1.0.1.0
        DESCRIPTION "Client Part of the R-Type Project"
        HOMEPAGE_URL "https://github.com/alwyn974/R-Type"
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(BINARY_NAME r-type_client)
# Make project-provided Find modules available
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

if(WIN32)
    set(${PROJECT_NAME}_ICON ${CMAKE_SOURCE_DIR}/assets/rtype/nsis/app.rc src/scene/SceneStage1.cpp include/scene/SceneStage1.hpp)
endif()

add_executable(${BINARY_NAME} main.cpp ${${PROJECT_NAME}_ICON}
        src/uranus/ecs/Components.cpp
        src/uranus/engine/Systems.cpp
        src/uranus/engine/Texture.cpp
        src/uranus/engine/Sprite.cpp
        src/uranus/engine/Manager.cpp
        src/uranus/engine/SceneManager.cpp
        src/uranus/engine/Scene.cpp
        src/uranus/engine/TextureManager.cpp
        src/uranus/engine/Base.cpp
        src/uranus/engine/EntityManager.cpp
        src/uranus/engine/RenderWindow.cpp
        src/uranus/engine/map/Map.cpp

        src/Player.cpp
        src/Enemy.cpp
        src/Bullet.cpp
        src/Explosion.cpp
        src/EnemyShooter.cpp
        src/BulletEnenmy.cpp
        src/bonus/Bonus.cpp
        src/bonus/DoubleBullet.cpp
        src/ui/Button.cpp
        src/scene/SceneGame.cpp
        src/scene/SceneStage1.cpp
        src/scene/SceneMain.cpp
        )
# Include all headers directories
target_include_directories(${BINARY_NAME}
        PRIVATE
            "${CMAKE_CURRENT_SOURCE_DIR}/src"
        PUBLIC
            "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>"
            "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

#find_package(Uranus REQUIRED)
#find_package(spdlog 1.11.1 REQUIRED)
#find_package(Saturnity 1.0.1.7 REQUIRED)
find_package(SFML 2.6 REQUIRED COMPONENTS graphics window system audio)
find_package(nlohmann_json 3.11.2 REQUIRED)
find_package(sol2 3.3.0 REQUIRED)
find_package(ImGui-SFML 2.5 REQUIRED)

target_link_libraries(${BINARY_NAME}
        PUBLIC
            R-Type-Common
            sfml-graphics sfml-audio sfml-system sfml-window
            nlohmann_json
            sol2
            ImGui-SFML
#            Uranus
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

if (RTYPE_INSTALL OR RTYPE_CPACK)
    # Specify the files to be installed
    message(STATUS "Installing ${BINARY_NAME}")
    get_target_property(${BINARY_NAME}_deps ${BINARY_NAME} INTERFACE_LINK_LIBRARIES)

    install(TARGETS ${BINARY_NAME} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT runtime)
    install(DIRECTORY "${CMAKE_SOURCE_DIR}/assets/rtype/" DESTINATION "${CMAKE_INSTALL_BINDIR}/assets/rtype/" COMPONENT runtime)
endif ()

#if (RTYPE_CPACK)
#    include(${CMAKE_SOURCE_DIR}/cmake/CPackConfig.cmake)
#endif ()
