/*
** EPITECH PROJECT, 2023
** newScene.hpp
** File description:
** newScene.hpp
*/

#ifndef ECS_FRAUDER_NEWSCENE_HPP
#define ECS_FRAUDER_NEWSCENE_HPP

#include "entityManager.hpp"

class NewScene: public Scene {
public:
    NewScene() = default;
    ~NewScene() = default;

    void update() override;

    void init() override;


    sf::View view;

private:
};

#endif //ECS_FRAUDER_NEWSCENE_HPP
