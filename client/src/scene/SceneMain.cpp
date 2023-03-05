/*
** EPITECH PROJECT, 2023
** SceneMain.cpp
** File description:
** SceneMain.cpp
*/

#include "scene/SceneMain.hpp"
#include "ui/Button.hpp"
#include "network/NetworkManager.hpp"

SceneMain::SceneMain() : Scene("Main") {}

void pressedPlay()
{
    auto &networkManager = rtype::client::network::NetworkManager::getInstance();
    try {
        networkManager->tcpPort = std::stoi(networkManager->imGuiTcpPort);
        networkManager->udpPort = std::stoi(networkManager->imGuiUdpPort);
        if (networkManager->imGuiHost.empty())
            throw std::runtime_error("Invalid host");
        if (networkManager->tcpPort < 0 || networkManager->tcpPort > 65535)
            throw std::runtime_error("Invalid TCP port");
        if (networkManager->udpPort < 0 || networkManager->udpPort > 65535)
            throw std::runtime_error("Invalid UDP port");

        networkManager->connectTcpClient(networkManager->imGuiHost, networkManager->tcpPort);
        networkManager->runTcpClient();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    auto &sceneManager = engine::Manager::getSceneManager();
    sceneManager->changeScene("Stage1");
}

void pressedQuit()
{
    auto &window = engine::Manager::getWindow();
    window->close();
}

void SceneMain::init()
{
    auto &entityManager = engine::Manager::getEntityManager();
    auto &textureManager = engine::Manager::getTextureManager();

    auto &r = engine::Manager::getRegistry();

    textureManager->addTexture("assets/rtype/textures/entity/ship.png", "ship");
    textureManager->addTexture("assets/rtype/textures/entity/enemy.png", "enemy");
    textureManager->addTexture("assets/rtype/textures/entity/enemy2.png", "enemyShooter");
    textureManager->addTexture("assets/rtype/textures/entity/bullet3.png", "bullet");
    textureManager->addTexture("assets/rtype/textures/entity/bulletEnemy.png", "bulletEnemy");
    textureManager->addTexture("assets/rtype/textures/effects/explosion.png", "explosion");
    textureManager->addTexture("assets/rtype/textures/effects/bonusDouble.png", "bonusDoubleBullet");
    textureManager->addTexture("assets/rtype/textures/gui/button/button.png", "button");
    textureManager->addTexture("assets/rtype/textures/gui/button/buttonPlay.png", "buttonPlay");
    textureManager->addTexture("assets/rtype/textures/gui/button/buttonQuit.png", "buttonQuit");
    textureManager->addTexture("assets/rtype/textures/logo/logo2.png", "logo");
    textureManager->addTexture("assets/rtype/textures/background/background2.png", "background");

    const uranus::ecs::Entity background = r->spawnEntity();
    r->addComponent(background, uranus::ecs::component::Position {0, 0});
    auto rectangle = std::make_shared<engine::RectangleShape>();
    rectangle->setSize({WIN_WIDTH, WIN_HEIGHT});
    const std::shared_ptr<sf::Texture> texture = textureManager->getTextureByName("background");
    rectangle->setTexture(texture.get());
    r->addComponent(background, uranus::ecs::component::RectangleShape {rectangle});

    auto centerPos = [&](const sf::Vector2f &pos, std::shared_ptr<engine::Texture> &texture) {
        return uranus::ecs::component::Position {(pos.x + (float) WIN_WIDTH - (float) texture->getSize().x / 3) / 2, pos.y + ((float) WIN_HEIGHT - (float) texture->getSize().y) / 2}; // NOLINT
    };

    auto &buttonPlayTexture = textureManager->getTextureByName("buttonPlay");
    auto buttonPlay =
        std::make_shared<ui::Button>("buttonPlay", centerPos({0, 0}, buttonPlayTexture), buttonPlayTexture, pressedPlay);
    entityManager->addPrefab(buttonPlay);

    auto &buttonQuitTexture = textureManager->getTextureByName("buttonQuit");
    auto buttonQuit =
        std::make_shared<ui::Button>("buttonQuit", centerPos({0, 75}, buttonQuitTexture), buttonQuitTexture, pressedQuit);
    entityManager->addPrefab(buttonQuit);

    const uranus::ecs::Entity newEntity = r->spawnEntity();
    auto logoTexture = textureManager->getTextureByName("logo");
    r->addComponent(newEntity, uranus::ecs::component::Position {((float) WIN_WIDTH - (float) logoTexture->getSize().x) / 2, 20}); // NOLINT
    r->addComponent(newEntity, uranus::ecs::component::Sprite {  std::make_shared<engine::Sprite>(logoTexture) });
}
