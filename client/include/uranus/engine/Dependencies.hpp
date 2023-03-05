/*
** EPITECH PROJECT, 2023
** Dependencies.hpp
** File description:
** Dependencies.hpp
*/

#ifndef URANUS_DEPENDENCIES_HPP
#define URANUS_DEPENDENCIES_HPP

#include <iostream>
#include "uranus/ecs/Registry.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace uranus::ecs {
    enum LayerMask {
        PLAYER = 0,
        PLAYER_BULLET,
        ENEMY,
        ENEMY_BULLET,
        BONUS,
        BUTTON,
        LAYER_MASK_SIZE // Always at the end
    };
}

#endif // URANUS_DEPENDENCIES_HPP
