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
#include "network/NetworkManager.hpp"

SceneStage1::SceneStage1() : Scene("Stage1") {}

void SceneStage1::addEnemy(uranus::ecs::component::Position pos)
{
    auto &entityManager = engine::Manager::getEntityManager();
    auto &textureManager = engine::Manager::getTextureManager();
    auto enemy = std::make_shared<Enemy>("enemy", pos, textureManager->getTextureByName("enemy"));
    addPrefab(enemy);
}

void SceneStage1::addEnemyShooter(uranus::ecs::component::Position pos)
{
    auto &entityManager = engine::Manager::getEntityManager();
    auto &textureManager = engine::Manager::getTextureManager();
    auto enemy = std::make_shared<EnemyShooter>("enemy", pos, textureManager->getTextureByName("enemyShooter"));
    addPrefab(enemy);
}

void SceneStage1::wave(uranus::ecs::component::Position startOffset)
{
    addEnemy(uranus::ecs::component::Position{startOffset.x + 800, startOffset.y + 100});
    addEnemy(uranus::ecs::component::Position{startOffset.x + 800, startOffset.y + 200});
    addEnemy(uranus::ecs::component::Position{startOffset.x + 800, startOffset.y + 300});
    addEnemy(uranus::ecs::component::Position{startOffset.x + 800, startOffset.y + 400});
    addEnemy(uranus::ecs::component::Position{startOffset.x + 800, startOffset.y + 500});
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    addEnemy(uranus::ecs::component::Position{startOffset.x + 900, startOffset.y + 100});
    addEnemy(uranus::ecs::component::Position{startOffset.x + 900, startOffset.y + 200});
    addEnemy(uranus::ecs::component::Position{startOffset.x + 900, startOffset.y + 300});
    addEnemy(uranus::ecs::component::Position{startOffset.x + 900, startOffset.y + 400});
    addEnemy(uranus::ecs::component::Position{startOffset.x + 900, startOffset.y + 500});
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    addEnemy(uranus::ecs::component::Position{startOffset.x + 1000, startOffset.y + 100});
    addEnemy(uranus::ecs::component::Position{startOffset.x + 1000, startOffset.y + 200});
    addEnemy(uranus::ecs::component::Position{startOffset.x + 1000, startOffset.y + 300});
    addEnemy(uranus::ecs::component::Position{startOffset.x + 1000, startOffset.y + 400});
    addEnemy(uranus::ecs::component::Position{startOffset.x + 1000, startOffset.y + 500});
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    addEnemyShooter(uranus::ecs::component::Position{startOffset.x + 1400, startOffset.y + 0});
    addEnemyShooter(uranus::ecs::component::Position{startOffset.x + 1400, startOffset.y + 300});
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

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
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

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
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

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

void pressedLeave()
{
    std::cout << "Leroyyyy Jen Leaves" << std::endl;
}

void SceneStage1::init()
{
    static auto &textureManager = engine::Manager::getTextureManager();
    static auto &networkManager = rtype::client::network::NetworkManager::getInstance();

    textureManager->addTexture("assets/rtype/textures/background/planets.png", "planets");
    textureManager->addTexture("assets/rtype/textures/background/stars.png", "stars");
    std::vector<std::string> names = {"stars", "planets"};
    auto parallax = std::make_shared<Parallax>("parallax", names);
    addPrefab(parallax);

    auto player = std::make_shared<Player>("player", textureManager->getTextureByName("ship"), "bullet");
    addPrefab(player);

    networkManager->send(std::make_shared<rtype::network::packet::C2SSceneLoaded>(this->getName()));
//    textureManager->addTexture("assets/rtype/textures/entity/dobkeratops.png", "boss");
//    auto boss = std::make_shared<Boss>("boss", uranus::ecs::component::Position{300, 200}, textureManager->getTextureByName("boss"));
//    addPrefab(boss);

    //Pause menu
    auto &r = engine::Manager::getRegistry();
    const uranus::ecs::Entity &pauseMenu = r->spawnEntity();
    const sf::Vector2f pauseMenuSize(300, 300);
    r->addComponent(pauseMenu, uranus::ecs::component::Position{(WIN_WIDTH - pauseMenuSize.x) / 2 , (WIN_HEIGHT - pauseMenuSize.y) / 2});
    auto pauseBackground = std::make_shared<engine::RectangleShape>();
    pauseBackground->setSize(pauseMenuSize);
    pauseBackground->setFillColor(sf::Color::Blue);
    r->addComponent(pauseMenu, uranus::ecs::component::Shape(pauseBackground, 3, false));
    r->addComponent(pauseMenu, uranus::ecs::component::InputKeyboard({
         [](const size_t id, const engine::Event event) {
            auto &r = engine::Manager::getRegistry();
            if (event.type == sf::Event::EventType::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                for (auto [idx, shape] : uranus::ecs::View<uranus::ecs::component::Shape>(*r)) {
                    if (shape.zIndex > 2)
                        shape.visible = !shape.visible;
                }
                for (auto [idx, sprite] : uranus::ecs::View<uranus::ecs::component::Sprite>(*r)) {
                    if (sprite.zIndex > 2)
                        sprite.visible = !sprite.visible;
                }
            }
         }
    }));
    auto centerPos = [&](const sf::Vector2f &pos, std::shared_ptr<engine::Texture> &texture) {
        return uranus::ecs::component::Position {(pos.x + (float) WIN_WIDTH - (float) texture->getSize().x / 3) / 2, pos.y + ((float) WIN_HEIGHT - (float) texture->getSize().y) / 2}; // NOLINT
    };
    auto &buttonLeaveTexture = textureManager->getTextureByName("buttonQuit");
    auto buttonLeave = std::make_shared<ui::Button>("buttonLeave", centerPos({0, 0}, buttonLeaveTexture), buttonLeaveTexture, pressedLeave, 4, false);
    this->addPrefab(buttonLeave);
}
