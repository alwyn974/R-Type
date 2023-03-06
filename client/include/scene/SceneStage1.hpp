/*
** EPITECH PROJECT, 2023
** SceneStage1.hpp
** File description:
** SceneStage1.hpp
*/

#ifndef R_TYPE_SCENESTAGE1_HPP
#define R_TYPE_SCENESTAGE1_HPP

#include "uranus/engine/Engine.hpp"

class SceneStage1 : public engine::Scene {
public:
    explicit SceneStage1();

    ~SceneStage1() override = default;

    void init() override;

    void addEnemy(uranus::ecs::component::Position pos);

    void addEnemyShooter(uranus::ecs::component::Position pos);

    void wave(uranus::ecs::component::Position startOffset);

private:
};


#endif //R_TYPE_SCENESTAGE1_HPP
