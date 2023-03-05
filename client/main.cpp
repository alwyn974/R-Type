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
    auto instance = rtype::client::network::NetworkManager::getInstance();
    instance->init();

    instance->connectTcpClient("localhost", 2409);
    instance->connectUdpClient("localhost", 2410);
    instance->runTcpClient();
    instance->runUdpClient();

    engine::system::gameInit();

    auto &sceneManager = engine::Manager::getSceneManager();
    sceneManager->addScene(std::make_shared<SceneMain>());
    sceneManager->addScene(std::make_shared<SceneGame>());
    sceneManager->addScene(std::make_shared<SceneStage1>());
    sceneManager->changeScene("Main");

    instance->send(std::make_shared<rtype::network::packet::C2SPlayerHandshake>("Alwyn"));
    instance->send(std::make_shared<rtype::network::packet::C2SPlayerShoot>());

    /* sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
     window.setFramerateLimit(60);*/

    /*  sf::Music music;
      spdlog::info("Music open: {}", music.openFromFile("assets/rtype/sounds/music-r-type.ogg"));
      //"C:\Users\alwyn\CLionProjects\R-Type\out\install\x64-Debug\bin\assets\rtype\sounds\music-r-type.ogg"
      music.setLoop(true);
      music.setVolume(50);
      music.play();*/
    /*
        while (window.isOpen()) {
            sf::Event event = {};
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            window.clear();
            window.display();
        }*/

    engine::system::gameLoop();

    instance->stopUdpClient();
    instance->stopTcpClient();

    /*auto &textureManager = engine::Manager::getTextureManager();
    textureManager.reset();
*/
    return 0;
}
