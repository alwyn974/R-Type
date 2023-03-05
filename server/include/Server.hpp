/*
** EPITECH PROJECT, 2023
** Server.hpp
** File description:
** Server.hpp
*/

#ifndef R_TYPE_SERVER_HPP
#define R_TYPE_SERVER_HPP

#include "GameServer.hpp"

struct Args {
    std::string host;
    std::uint16_t tcpPort;
    std::uint16_t udpPort;
    int maxPlayers;
};

#endif // R_TYPE_SERVER_HPP
