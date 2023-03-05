/*
** EPITECH PROJECT, 2023
** main.cpp
** File description:
** main.cpp
*/

#include <iostream>
#include "packets/tcp/client/C2SPlayerHandshake.hpp"

int main(int ac, char **av)
{
    sa::PacketRegistry registry;
    registry.registerPacket<rtype::network::packet::C2SPlayerHandshake>(0x1);
    auto packet = std::make_shared<rtype::network::packet::C2SPlayerHandshake>("Hiii");

    spdlog::info("Has packet: {}", registry.hasPacket(0x1));
    spdlog::info("Has packet: {}", registry.hasPacket<rtype::network::packet::C2SPlayerHandshake>());
    return (0);
}