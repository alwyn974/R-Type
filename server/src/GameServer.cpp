/*
** EPITECH PROJECT, 2023
** GameServer.cpp
** File description:
** GameServer.cpp
*/

#include "GameServer.hpp"

namespace rtype::server {

    GameServer::GameServer(const std::string &host, std::uint16_t tcpPort, std::uint16_t udpPort)
    {
        this->_logger = spdlog::stdout_color_mt("GameServer");
        this->_host = host;
        this->_tcpPort = tcpPort;
        this->_udpPort = udpPort;
    }

    void GameServer::init()
    {
        this->_tcpServer = sa::TCPServer::create(this->_packetRegistry, this->_host, this->_tcpPort);
        this->_udpServer = sa::UDPServer::create(this->_packetRegistry, this->_host, this->_udpPort);

        this->_tcpServer->init();
        this->_udpServer->init();
    }

    void GameServer::start()
    {
        this->_tcpServer->asyncRun();
        this->_udpServer->asyncRun();
    }

    void GameServer::stop()
    {
        this->_tcpServer->stop();
        this->_udpServer->stop();
    }

    const std::shared_ptr<sa::TCPServer> &GameServer::getTcpServer() const
    {
        return _tcpServer;
    }

    const std::shared_ptr<sa::UDPServer> &GameServer::getUdpServer() const
    {
        return _udpServer;
    }

    const std::shared_ptr<spdlog::logger> &GameServer::getLogger() const
    {
        return _logger;
    }

    void GameServer::setTcpServer(const std::shared_ptr<sa::TCPServer> &tcpServer)
    {
        _tcpServer = tcpServer;
    }

    void GameServer::setUdpServer(const std::shared_ptr<sa::UDPServer> &udpServer)
    {
        _udpServer = udpServer;
    }

    void GameServer::setLogger(const std::shared_ptr<spdlog::logger> &logger)
    {
        _logger = logger;
    }
}

