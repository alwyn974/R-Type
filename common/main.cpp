/*
** EPITECH PROJECT, 2023
** main.cpp
** File description:
** main.cpp
*/

#include <iostream>
#include "packets/PlayerHandshake.hpp"

int main(int ac, char **av)
{
    sa::PacketRegistry registry;
    registry.registerPacket<rtype::network::packet::PlayerHandshake>(0x1);
    auto packet = std::make_shared<rtype::network::packet::PlayerHandshake>("Hiii");

    spdlog::info("Has packet: {}", registry.hasPacket(0x1));
    spdlog::info("Has packet: {}", registry.hasPacket<rtype::network::packet::PlayerHandshake>());
    return (0);
}