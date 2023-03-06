/*
** EPITECH PROJECT, 2023
** Player.hpp
** File description:
** Player.hpp
*/

#ifndef R_TYPE_PLAYER_HPP
#define R_TYPE_PLAYER_HPP

#include <string>

namespace rtype::server::game {
    class Player {
    public:
        explicit Player(int tcpId, int udpId, const std::string &name);

        int getTcpId() const;
        int getUdpId() const;
        int getScore() const;
        int getLife() const;
        int getX() const;
        int getY() const;
        int getWidth() const;
        int getHeight() const;
        const std::string &getName() const;
        bool isSceneLoaded() const;
        bool isReady() const;

        Player &setTcpId(int tcpId);
        Player &setUdpId(int udpId);
        Player &setScore(int score);
        Player &setLife(int life);
        Player &setX(int x);
        Player &setY(int y);
        Player &setWidth(int width);
        Player &setHeight(int height);
        Player &setName(const std::string &name);
        Player &setSceneLoaded(bool sceneLoaded);
        Player &setReady(bool ready);

    private:
        int _tcpId;
        int _udpId;
        int _score;
        int _life;
        int _x;
        int _y;
        int _width;
        int _height;
        std::string _name;
        bool _sceneLoaded;
        bool _ready;
    };
} // namespace rtype::server::game

#endif // R_TYPE_PLAYER_HPP
