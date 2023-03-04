/*
** EPITECH PROJECT, 2023
** main.cpp
** File description:
** main.cpp
*/

#include "scene/SceneGame.hpp"
#include "scene/SceneMain.hpp"

#include <uranus/Uranus.hpp>

int main()
{
//    engine::system::gameInit();

//    auto &sceneManager = engine::Manager::getSceneManager();
//    sceneManager->addScene(std::make_shared<SceneMain>());
//    sceneManager->addScene(std::make_shared<SceneGame>());
//    sceneManager->changeScene("Main");

    sf::Music music;
    music.openFromFile("assets/rtype/sounds/music.ogg");
    music.setLoop(true);
    music.play();

//    engine::system::gameLoop();
    return 0;
}
