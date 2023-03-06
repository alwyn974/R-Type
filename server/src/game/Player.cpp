/*
** EPITECH PROJECT, 2023
** Player.cpp
** File description:
** Player.cpp
*/

#include "game/Player.hpp"

namespace rtype::server::game {

    Player::Player(int tcpId, int udpId, const std::string &name)
    {
        this->_tcpId = tcpId;
        this->_udpId = udpId;
        this->_score = 0;
        this->_life = 0;
        this->_x = 0;
        this->_y = 0;
        this->_width = 0;
        this->_height = 0;
        this->_name = name;
        this->_sceneLoaded = false;
        this->_ready = false;
    }

    int Player::getTcpId() const
    {
        return this->_tcpId;
    }

    int Player::getUdpId() const
    {
        return this->_udpId;
    }

    int Player::getScore() const
    {
        return this->_score;
    }

    int Player::getLife() const
    {
        return this->_life;
    }

    int Player::getX() const
    {
        return this->_x;
    }

    int Player::getY() const
    {
        return this->_y;
    }

    int Player::getWidth() const
    {
        return this->_width;
    }

    int Player::getHeight() const
    {
        return this->_height;
    }

    const std::string &Player::getName() const
    {
        return this->_name;
    }

    bool Player::isSceneLoaded() const
    {
        return _sceneLoaded;
    }

    bool Player::isReady() const
    {
        return this->_ready;
    }

    Player &Player::setTcpId(int tcpId)
    {
        this->_tcpId = tcpId;
        return *this;
    }

    Player &Player::setUdpId(int udpId)
    {
        this->_udpId = udpId;
        return *this;
    }

    Player &Player::setScore(int score)
    {
        this->_score = score;
        return *this;
    }

    Player &Player::setLife(int life)
    {
        this->_life = life;
        return *this;
    }

    Player &Player::setX(int x)
    {
        this->_x = x;
        return *this;
    }

    Player &Player::setY(int y)
    {
        this->_y = y;
        return *this;
    }

    Player &Player::setWidth(int width)
    {
        this->_width = width;
        return *this;
    }

    Player &Player::setHeight(int height)
    {
        this->_height = height;
        return *this;
    }

    Player &Player::setName(const std::string &name)
    {
        this->_name = name;
        return *this;
    }

    Player &Player::setSceneLoaded(bool sceneLoaded)
    {
        this->_sceneLoaded = sceneLoaded;
        return *this;
    }

    Player &Player::setReady(bool ready)
    {
        this->_ready = ready;
        return *this;
    }
}
