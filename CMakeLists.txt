cmake_minimum_required(VERSION 3.22)
project(ecs_frauder)

set(CMAKE_CXX_STANDARD 14)

add_executable(ecs_frauder main.cpp include/basics.hpp include/entityManager.hpp include/entity.hpp entityManager.cpp entity.cpp include/scene.hpp include/newScene.hpp newScene.cpp)

target_link_libraries(${PROJECT_NAME} -lsfml-window -lsfml-graphics -lsfml-system -lsfml-audio)