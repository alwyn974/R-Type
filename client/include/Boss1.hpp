/*
** EPITECH PROJECT, 2023
** Boss1.hpp
** File description:
** Boss1.hpp
*/

#ifndef R_TYPE_BOSS1_HPP
#define R_TYPE_BOSS1_HPP

#include "Enemy.hpp"

class Boss : public Enemy {
public:
    explicit Boss(const std::string &uniqueName, uranus::ecs::component::Position pos, std::shared_ptr<engine::Texture> &texture);

    void loop(size_t entity, float delta);

    void colliding(const size_t &entity, const size_t &entityCollidingWith);

    void animationCallback(size_t entity, const std::string &animationName);

};

#endif //R_TYPE_BOSS1_HPP
