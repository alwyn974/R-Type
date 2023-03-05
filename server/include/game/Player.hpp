/*
** EPITECH PROJECT, 2023
** Player.hpp
** File description:
** Player.hpp
*/

#ifndef R_TYPE_PLAYER_HPP
#define R_TYPE_PLAYER_HPP

namespace rtype::server::game {
    class Player {
    public:
        explicit Player(int tcpId, int udpId);

        int getTcpId() const;
        int getUdpId() const;
        int getScore() const;
        int getLife() const;
        int getX() const;
        int getY() const;
        int getWidth() const;
        int getHeight() const;

        Player &setTcpId(int tcpId);
        Player &setUdpId(int udpId);
        Player &setScore(int score);
        Player &setLife(int life);
        Player &setX(int x);
        Player &setY(int y);
        Player &setWidth(int width);
        Player &setHeight(int height);

    private:
        int _tcpId;
        int _udpId;
        int _score;
        int _life;
        int _x;
        int _y;
        int _width;
        int _height;
    };
} // namespace rtype::server::game

#endif // R_TYPE_PLAYER_HPP
