/*
** EPITECH PROJECT, 2023
** SceneStage1.cpp
** File description:
** SceneStage1.cpp
*/


#include "scene/SceneStage1.hpp"
#include "bonus/DoubleBullet.hpp"
#include "Enemy.hpp"
#include "EnemyShooter.hpp"
#include "Player.hpp"
#include "ui/Button.hpp"
#include "Parallax.hpp"

SceneStage1::SceneStage1() : Scene("Stage1") {}

void addEnemy(uranus::ecs::component::Position pos)
{
    auto &entityManager = engine::Manager::getEntityManager();
    auto &textureManager = engine::Manager::getTextureManager();
    auto enemy = std::make_shared<Enemy>("enemy", pos, textureManager->getTextureByName("enemy"));
    entityManager->addPrefab(enemy);
}

void addEnemyShooter(uranus::ecs::component::Position pos)
{
    auto &entityManager = engine::Manager::getEntityManager();
    auto &textureManager = engine::Manager::getTextureManager();
    auto enemy = std::make_shared<Enemy>("enemy", pos, textureManager->getTextureByName("enemyShooter"));
    entityManager->addPrefab(enemy);
}

void SceneStage1::init()
{
    auto &entityManager = engine::Manager::getEntityManager();
    auto &textureManager = engine::Manager::getTextureManager();

    textureManager->addTexture("assets/rtype/textures/background/planets.png", "planets");
    textureManager->addTexture("assets/rtype/textures/background/stars.png", "stars");
    std::vector<std::string> names;
    names.push_back("stars");
    names.push_back("planets");
    auto parallax = std::make_shared<Parallax>("parallax", names);
    entityManager->addPrefab(parallax);


    auto player = std::make_shared<Player>("player", textureManager->getTextureByName("ship"), "bullet");
    entityManager->addPrefab(player);


//    auto bonusDoubleBullet = std::make_shared<bonus::DoubleBullet>("bonusDoubleBullet", uranus::ecs::component::Position {200, 300});
//    entityManager->addPrefab(bonusDoubleBullet);

    addEnemy(uranus::ecs::component::Position{800, 100});
    addEnemy(uranus::ecs::component::Position{800, 200});
    addEnemy(uranus::ecs::component::Position{800, 300});
    addEnemy(uranus::ecs::component::Position{800, 400});

    addEnemy(uranus::ecs::component::Position{800, 100});
    addEnemy(uranus::ecs::component::Position{800, 200});
    addEnemy(uranus::ecs::component::Position{800, 300});
    addEnemy(uranus::ecs::component::Position{800, 400});

    addEnemy(uranus::ecs::component::Position{900, 100});
    addEnemy(uranus::ecs::component::Position{900, 200});
    addEnemy(uranus::ecs::component::Position{900, 300});
    addEnemy(uranus::ecs::component::Position{900, 400});

    addEnemy(uranus::ecs::component::Position{1000, 100});
    addEnemy(uranus::ecs::component::Position{1000, 200});
    addEnemy(uranus::ecs::component::Position{1000, 300});
    addEnemy(uranus::ecs::component::Position{1000, 400});

}
