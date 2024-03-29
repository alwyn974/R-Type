/*
** EPITECH PROJECT, 2023
** Enemy.hpp
** File description:
** Enemy.hpp
*/

#ifndef URANUS_ENEMY_HPP
#define URANUS_ENEMY_HPP

#include "uranus/engine/Engine.hpp"
#include "Damaging.hpp"

class Enemy : public engine::Base, public Damaging {
public:
    explicit Enemy(const std::string &uniqueName, uranus::ecs::component::Position pos, std::shared_ptr<engine::Texture> &texture);

    virtual void loop(size_t, float delta);

    void animationCallback(size_t entity, const std::string &animationName);

    virtual void colliding(const size_t &entity, const size_t &entityCollidingWith);

    void getDamage(size_t entity, int damage) override;

private:
};

#endif // URANUS_ENEMY_HPP
