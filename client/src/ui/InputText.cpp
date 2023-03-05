/*
** EPITECH PROJECT, 2023
** InputText.cpp
** File description:
** InputText.cpp
*/

#include "ui/InputText.hpp"

ui::InputText::InputText(const std::string &uniqueName, uranus::ecs::component::Position pos, const std::function<void()> &callbackPressed) : Base(uniqueName)
{
//    this->_hover = false;
//    this->_focused = false;
//    this->_callbackPressed = callbackPressed;
//
//    this->_font.loadFromFile("assets/rtype/fonts/dodger3_1.ttf");
//    this->_text.setFont(this->_font);
//    this->_text.setCharacterSize(300);
//    this->_text.setFillColor(sf::Color::Red);
//
//    auto &r = engine::Manager::getRegistry();
//    uranus::ecs::Entity newEntity = r->entityFromIndex(this->_entityId);
//
//    r->addComponent(newEntity, uranus::ecs::component::Name {uniqueName});
//    r->addComponent(newEntity, uranus::ecs::component::Position {pos.x, pos.y});
//    r->addComponent(newEntity, uranus::ecs::component::InputKeyboard {[&](size_t entity, const engine::Event event) { this->handleKeyboard(entity, event); }});
//
//    std::array<bool, LAYER_SIZE> layer {true, false, false, false};
//    std::array<bool, MASK_SIZE> mask {false, false, false, false};
//    r->addComponent(
//        newEntity,
//        uranus::ecs::component::Collisionable {
//            0, 0, 100, 100, layer, mask, [&](const size_t &entity, const size_t &entityCollidingWith) { return; }});
//
//    r->addComponent(newEntity, uranus::ecs::component::Loop {[&](const size_t entity) { this->loop(entity); }});
//}
//
//void ui::InputText::loop(size_t entity)
//{
//    auto &r = engine::Manager::getRegistry();
//    auto &entityManager = engine::Manager::getEntityManager();
//    auto &textureManager = engine::Manager::getTextureManager();
//    auto &window = engine::Manager::getWindow();
//
//    auto &collision = r->getComponent<uranus::ecs::component::Collisionable>(entity);
//    auto &pos = r->getComponent<uranus::ecs::component::Position>(entity);
//
//    auto mousePosition {static_cast<sf::Vector2f>(sf::Mouse::getPosition(*window))};
//    const sf::FloatRect rect {collision->x + pos->x, collision->y + pos->y, collision->width, collision->height};
//
//    window->draw(this->_text);
//
//    if (rect.contains(mousePosition)) {
//        this->_hover = true;
//    } else if (this->_focused == false) {
//        this->_hover = false;
//    }

}

void ui::InputText::handleKeyboard(size_t entity, engine::Event event)
{
    auto &r = engine::Manager::getRegistry();
    auto &pos = r->getComponent<uranus::ecs::component::Position>(entity);

    this->_text.setPosition(pos->x, pos->y);

    if (event.mouseButton.button == sf::Mouse::Left && event.type == event.MouseButtonPressed) {
        if (this->_hover) {
            this->_focused = true;
            this->_callbackPressed();
        } else {
            this->_hover = false;
        };
    }

    std::string s = this->_text.getString();
    if (std::isdigit(event.text.unicode) || std::isalpha(event.text.unicode))
        this->_text.setString(s + char(event.text.unicode));
    spdlog::info("event :{}", event.text.unicode);
    s = this->_text.getString();
    std::cout << "_text " << s << std::endl;

//    if (event.text.unicode)




}
