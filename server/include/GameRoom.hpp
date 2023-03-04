/*
** EPITECH PROJECT, 2023
** GameRoom.hpp
** File description:
** GameRoom.hpp
*/

#ifndef R_TYPE_GAMEROOM_HPP
#define R_TYPE_GAMEROOM_HPP

#include <saturnity/Saturnity.hpp>

namespace rtype::server {
    class GameRoom {
    public:
        explicit GameRoom(const std::string &host, std::uint16_t port, const std::string &id, const std::string &map);
    private:

    };
}

#endif //R_TYPE_GAMEROOM_HPP
