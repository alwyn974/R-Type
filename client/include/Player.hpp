/*
** EPITECH PROJECT, 2023
** Player.hpp
** File description:
** Player.hpp
*/

#ifndef URANUS_PLAYER_HPP
#define URANUS_PLAYER_HPP

#include "uranus/engine/Engine.hpp"
#include "Damaging.hpp"

class Player : public engine::Base, public Damaging {
public:
    explicit Player(const std::string &uniqueName, std::shared_ptr<engine::Texture> &texture, const std::string &bulletTextureName, std::uint32_t networkId = 0, const sf::Vector2f &pos = {0, 0});

    void move(size_t entity, const engine::Event event);

    void shoot();

    void colliding(const size_t &entity, const size_t &entityCollidingWith);

    void enableDoubleBullet();

    void getDamage(size_t entity, int damage) override;

private:
    float _delta;
    engine::Clock _clockCooldown;
    std::string _bulletTextureName;
    bool _networked;
    bool _doubleBullet;
    std::uint32_t _networkId;
};

#endif // URANUS_PLAYER_HPP
