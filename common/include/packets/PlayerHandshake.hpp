/*
** EPITECH PROJECT, 2023
** PlayerHandshake.hpp
** File description:
** PlayerHandshake.hpp
*/

#ifndef R_TYPE_PLAYERHANDSHAKE_HPP
#define R_TYPE_PLAYERHANDSHAKE_HPP

#include <saturnity/Saturnity.hpp>

namespace rtype::network::packet {
    struct PlayerHandshake {
        std::string name;
    };
}

#endif // R_TYPE_PLAYERHANDSHAKE_HPP