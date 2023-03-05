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
        this->_tcpPacketRegistry = std::make_shared<sa::PacketRegistry>();
        this->_udpPacketRegistry = std::make_shared<sa::PacketRegistry>();
        this->_tcpServer = sa::TCPServer::create(this->_tcpPacketRegistry, this->_host, this->_tcpPort);
        this->_udpServer = sa::UDPServer::create(this->_udpPacketRegistry, this->_host, this->_udpPort);

        this->registerTcpCallbacks();
        this->registerUdpCallbacks();

        try {
            this->_tcpServer->init();
        } catch (std::exception &e) {
            throw std::runtime_error("Failed to init TCP server: " + std::string(e.what()));
        }
        try {
            this->_udpServer->init();
        } catch (std::exception &e) {
            throw std::runtime_error("Failed to init UDP server: " + std::string(e.what()));
        }

        this->registerTcpPackets();
        this->registerUdpPackets();

        while (true);
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

    void GameServer::registerTcpCallbacks()
    {
        this->_tcpServer->onServerDataReceived = [&](ConnectionToClientPtr &client, std::uint16_t packetId, std::uint16_t packetSize, sa::ByteBuffer &buffer) {
//            this->_logger->info("Received packet from client ({}): {} ({} bytes)", client->getId(), packetId, packetSize);
        };
        this->_tcpServer->onServerDataSent = [&](ConnectionToClientPtr &client, sa::ByteBuffer &buffer) {
//            this->_logger->info("Sent packet to client ({}): ({} bytes)", client->getId(), buffer.size());
        };
        this->_tcpServer->onClientConnect = [&](ConnectionToClientPtr &client) {
            this->_logger->info("Client try to connect");
            return true; //TODO: implement limits
        };
        this->_tcpServer->onClientConnected = [&](ConnectionToClientPtr &client) {
            this->_logger->info("Client connected id: {}", client->getId());
        };
        this->_tcpServer->onClientDisconnected = [&](ConnectionToClientPtr &client) {
            this->_logger->info("Client disconnected id: {}", client->getId());
        };
    }

    void GameServer::registerUdpCallbacks()
    {
        this->_udpServer->onServerDataReceived = [&](ConnectionToClientPtr &client, std::uint16_t packetId, std::uint16_t packetSize, sa::ByteBuffer &buffer) {
//            this->_logger->info("Received packet from client ({}): {} ({} bytes)", client->getId(), packetId, packetSize);
        };
        this->_udpServer->onServerDataSent = [&](ConnectionToClientPtr &client, sa::ByteBuffer &buffer) {
//            this->_logger->info("Sent packet to client ({}): ({} bytes)", client->getId(), buffer.size());
        };
        this->_udpServer->onClientConnect = [&](ConnectionToClientPtr &client) {
            this->_logger->info("Client try to connect");
            return true; //TODO: implement limits
        };
        this->_udpServer->onClientConnected = [&](ConnectionToClientPtr &client) {
            this->_logger->info("Client connected id: {}", client->getId());
        };
        this->_udpServer->onClientDisconnected = [&](ConnectionToClientPtr &client) {
            this->_logger->info("Client disconnected id: {}", client->getId());
        };
    }

    void GameServer::registerUdpPackets()
    {

    }

    void GameServer::registerTcpPackets()
    {

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

