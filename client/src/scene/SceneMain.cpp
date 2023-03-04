/*
** EPITECH PROJECT, 2023
** SceneMain.cpp
** File description:
** SceneMain.cpp
*/

#include "scene/SceneMain.hpp"
#include "bonus/DoubleBullet.hpp"
#include "Enemy.hpp"
#include "EnemyShooter.hpp"
#include "Player.hpp"
#include "ui/Button.hpp"

SceneMain::SceneMain() : Scene("Main") {}

void pressedPlay()
{
    auto &sceneManager = engine::Manager::getSceneManager();
    sceneManager->changeScene("Game");
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

    uranus::ecs::Entity newEntity2 = r->spawnEntity();
    r->addComponent(newEntity2, uranus::ecs::component::Name {"background"});
    r->addComponent(newEntity2, uranus::ecs::component::Position {0, 0});
    r->addComponent(newEntity2, uranus::ecs::component::Sprite {std::make_shared<engine::Sprite>(textureManager->getTextureByName("background"))});

    auto buttonPlay =
        std::make_shared<ui::Button>("buttonPlay", uranus::ecs::component::Position {300, 300}, textureManager->getTextureByName("buttonPlay"), pressedPlay);
    entityManager->addPrefab(buttonPlay);

    auto buttonQuit =
        std::make_shared<ui::Button>("buttonQuit", uranus::ecs::component::Position {300, 380}, textureManager->getTextureByName("buttonQuit"), pressedQuit);
    entityManager->addPrefab(buttonQuit);

    uranus::ecs::Entity newEntity = r->spawnEntity();
    r->addComponent(newEntity, uranus::ecs::component::Name {"logo"});
    r->addComponent(newEntity, uranus::ecs::component::Position {220, 50});
    r->addComponent(newEntity, uranus::ecs::component::Sprite {std::make_shared<engine::Sprite>(textureManager->getTextureByName("logo"))});
}
