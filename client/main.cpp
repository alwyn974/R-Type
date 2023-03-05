/*
** EPITECH PROJECT, 2023
** main.cpp
** File description:
** main.cpp
*/

#include "scene/SceneGame.hpp"
#include "scene/SceneMain.hpp"
#include "scene/SceneStage1.hpp"
#include "network/NetworkManager.hpp"
#include <uranus/Uranus.hpp>

int main()
{
    auto &instance = rtype::client::network::NetworkManager::getInstance();
    instance->init();

    engine::system::gameInit();

    auto &sceneManager = engine::Manager::getSceneManager();
    sceneManager->addScene(std::make_shared<SceneMain>());
    sceneManager->addScene(std::make_shared<SceneGame>());
    sceneManager->addScene(std::make_shared<SceneStage1>());
    sceneManager->changeScene("Main");

    /*  sf::Music music;
      spdlog::info("Music open: {}", music.openFromFile("assets/rtype/sounds/music-r-type.ogg"));
      //"C:\Users\alwyn\CLionProjects\R-Type\out\install\x64-Debug\bin\assets\rtype\sounds\music-r-type.ogg"
      music.setLoop(true);
      music.setVolume(50);
      music.play();*/

    engine::system::gameLoop();

    instance->stopUdpClient();
    instance->stopTcpClient();
    return 0;
}
