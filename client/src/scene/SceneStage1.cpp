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
#include "Boss1.hpp"

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
    auto enemy = std::make_shared<EnemyShooter>("enemy", pos, textureManager->getTextureByName("enemyShooter"));
    entityManager->addPrefab(enemy);
}

void wave(uranus::ecs::component::Position startOffset)
{
    addEnemy(uranus::ecs::component::Position{startOffset.x + 800, startOffset.y + 100});
    addEnemy(uranus::ecs::component::Position{startOffset.x + 800, startOffset.y + 200});
    addEnemy(uranus::ecs::component::Position{startOffset.x + 800, startOffset.y + 300});
    addEnemy(uranus::ecs::component::Position{startOffset.x + 800, startOffset.y + 400});
    addEnemy(uranus::ecs::component::Position{startOffset.x + 800, startOffset.y + 500});

    addEnemy(uranus::ecs::component::Position{startOffset.x + 900, startOffset.y + 100});
    addEnemy(uranus::ecs::component::Position{startOffset.x + 900, startOffset.y + 200});
    addEnemy(uranus::ecs::component::Position{startOffset.x + 900, startOffset.y + 300});
    addEnemy(uranus::ecs::component::Position{startOffset.x + 900, startOffset.y + 400});
    addEnemy(uranus::ecs::component::Position{startOffset.x + 900, startOffset.y + 500});

    addEnemy(uranus::ecs::component::Position{startOffset.x + 1000, startOffset.y + 100});
    addEnemy(uranus::ecs::component::Position{startOffset.x + 1000, startOffset.y + 200});
    addEnemy(uranus::ecs::component::Position{startOffset.x + 1000, startOffset.y + 300});
    addEnemy(uranus::ecs::component::Position{startOffset.x + 1000, startOffset.y + 400});
    addEnemy(uranus::ecs::component::Position{startOffset.x + 1000, startOffset.y + 500});

    addEnemyShooter(uranus::ecs::component::Position{startOffset.x + 1400, startOffset.y + 0});
    addEnemyShooter(uranus::ecs::component::Position{startOffset.x + 1400, startOffset.y + 300});

    addEnemy(uranus::ecs::component::Position{startOffset.x + 1600, startOffset.y + 050});
    addEnemy(uranus::ecs::component::Position{startOffset.x + 1600, startOffset.y + 100});
    addEnemy(uranus::ecs::component::Position{startOffset.x + 1600, startOffset.y + 150});
    addEnemy(uranus::ecs::component::Position{startOffset.x + 1600, startOffset.y + 200});
    addEnemy(uranus::ecs::component::Position{startOffset.x + 1600, startOffset.y + 250});
    addEnemy(uranus::ecs::component::Position{startOffset.x + 1600, startOffset.y + 300});
    addEnemy(uranus::ecs::component::Position{startOffset.x + 1600, startOffset.y + 350});
    addEnemy(uranus::ecs::component::Position{startOffset.x + 1600, startOffset.y + 400});
    addEnemy(uranus::ecs::component::Position{startOffset.x + 1600, startOffset.y + 450});
    addEnemy(uranus::ecs::component::Position{startOffset.x + 1600, startOffset.y + 500});
    addEnemy(uranus::ecs::component::Position{startOffset.x + 1600, startOffset.y + 550});
    addEnemy(uranus::ecs::component::Position{startOffset.x + 1600, startOffset.y + 600});
    addEnemy(uranus::ecs::component::Position{startOffset.x + 1600, startOffset.y + 650});

    addEnemy(uranus::ecs::component::Position{startOffset.x + 1700, startOffset.y + 050});
    addEnemy(uranus::ecs::component::Position{startOffset.x + 1700, startOffset.y + 100});
    addEnemy(uranus::ecs::component::Position{startOffset.x + 1700, startOffset.y + 150});
    addEnemy(uranus::ecs::component::Position{startOffset.x + 1700, startOffset.y + 200});
    addEnemy(uranus::ecs::component::Position{startOffset.x + 1700, startOffset.y + 250});
    addEnemy(uranus::ecs::component::Position{startOffset.x + 1700, startOffset.y + 300});
    addEnemy(uranus::ecs::component::Position{startOffset.x + 1700, startOffset.y + 350});
    addEnemy(uranus::ecs::component::Position{startOffset.x + 1700, startOffset.y + 400});
    addEnemy(uranus::ecs::component::Position{startOffset.x + 1700, startOffset.y + 450});
    addEnemy(uranus::ecs::component::Position{startOffset.x + 1700, startOffset.y + 500});
    addEnemy(uranus::ecs::component::Position{startOffset.x + 1700, startOffset.y + 550});
    addEnemy(uranus::ecs::component::Position{startOffset.x + 1700, startOffset.y + 600});
    addEnemy(uranus::ecs::component::Position{startOffset.x + 1700, startOffset.y + 650});

    addEnemy(uranus::ecs::component::Position{startOffset.x + 1800, startOffset.y + 050});
    addEnemy(uranus::ecs::component::Position{startOffset.x + 1800, startOffset.y + 100});
    addEnemy(uranus::ecs::component::Position{startOffset.x + 1800, startOffset.y + 150});
    addEnemy(uranus::ecs::component::Position{startOffset.x + 1800, startOffset.y + 200});
    addEnemy(uranus::ecs::component::Position{startOffset.x + 1800, startOffset.y + 250});
    addEnemy(uranus::ecs::component::Position{startOffset.x + 1800, startOffset.y + 300});
    addEnemy(uranus::ecs::component::Position{startOffset.x + 1800, startOffset.y + 350});
    addEnemy(uranus::ecs::component::Position{startOffset.x + 1800, startOffset.y + 400});
    addEnemy(uranus::ecs::component::Position{startOffset.x + 1800, startOffset.y + 450});
    addEnemy(uranus::ecs::component::Position{startOffset.x + 1800, startOffset.y + 500});
    addEnemy(uranus::ecs::component::Position{startOffset.x + 1800, startOffset.y + 550});
    addEnemy(uranus::ecs::component::Position{startOffset.x + 1800, startOffset.y + 600});
    addEnemy(uranus::ecs::component::Position{startOffset.x + 1800, startOffset.y + 650});
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

    textureManager->addTexture("assets/rtype/textures/entity/dobkeratops.png", "boss");
    auto boss = std::make_shared<Boss>("boss", uranus::ecs::component::Position{300, 200}, textureManager->getTextureByName("boss"));
    entityManager->addPrefab(boss);


    wave(uranus::ecs::component::Position{0, 0});
//    wave(uranus::ecs::component::Position{2000, 0});
}
