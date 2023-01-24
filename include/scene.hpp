/*
** EPITECH PROJECT, 2023
** scene.hpp
** File description:
** scene.hpp
*/

#ifndef ECS_FRAUDER_SCENE_HPP
#define ECS_FRAUDER_SCENE_HPP

class Scene {
public:
    Scene() = default;

    ~Scene() = default;

    virtual void init() = 0;

    virtual void update() = 0;
private:
};

#endif //ECS_FRAUDER_SCENE_HPP
