/*
** EPITECH PROJECT, 2023
** GameServer.cpp
** File description:
** GameServer.cpp
*/

#include "GameServer.hpp"


namespace rtype::server {

    GameServer::GameServer(const std::string &host, std::uint16_t tcpPort, std::uint16_t udpPort, int maxPlayers)
    {
        this->_logger = spdlog::stdout_color_mt("GameServer");
        this->_host = host;
        this->_tcpPort = tcpPort;
        this->_udpPort = udpPort;
        this->_maxPlayers = maxPlayers;
        this->_playerCount = 0;
    }

    void GameServer::init()
    {
        this->_logger->info("Initializing GameServer...");
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
    }

    void GameServer::start()
    {
        this->_tcpServer->start();
        this->_udpServer->start();
        this->_tcpServer->asyncRun();
        this->_udpServer->asyncRun();
        this->_logger->info("GameServer started");
        int id = 0;

        UUIDv4::UUIDGenerator<std::mt19937> generator;

        while (true) {
            this->_udpServer->broadcast(std::make_shared<packet::S2CSpawnBullet>(id++, 100, 100));
        }
    }

    void GameServer::stop()
    {
        this->_tcpServer->stop();
        this->_udpServer->stop();
    }

    void GameServer::registerTcpCallbacks()
    {
        this->_tcpServer->onServerDataReceived = [&](ConnectionToClientPtr &client, std::uint16_t packetId, std::uint16_t packetSize, sa::ByteBuffer &buffer) {
            (void) client;
            (void) packetId;
            (void) packetSize;
            (void) buffer;
            spdlog::info("Received packet from client ({}): {} ({} bytes)", client->getId(), packetId, packetSize);
        };
        this->_tcpServer->onServerDataSent = [&](ConnectionToClientPtr &client, sa::ByteBuffer &buffer) {
            (void) client;
            (void) buffer;
            spdlog::info("Sent packet to client ({}): ({} bytes)", client->getId(), buffer.size());
        };
        this->_tcpServer->onClientConnect = [&](ConnectionToClientPtr &client) {
            spdlog::info("Client try to connect {}:{}", client->getIp(), client->getPort());
            return this->_playerCount + 1 <= this->_maxPlayers;
        };
        this->_tcpServer->onClientConnected = [&](ConnectionToClientPtr &client) { this->onTcpClientConnected(client); };
        this->_tcpServer->onClientDisconnected = [&](ConnectionToClientPtr &client) { this->onTcpClientDisconnected(client); };
    }

    void GameServer::registerUdpCallbacks()
    {
        this->_udpServer->onServerDataReceived = [&](ConnectionToClientPtr &client, std::uint16_t packetId, std::uint16_t packetSize, sa::ByteBuffer &buffer) {
            (void) client;
            (void) packetId;
            (void) packetSize;
            (void) buffer;
            spdlog::info("Received packet from client ({}): {} ({} bytes)", client->getId(), packetId, packetSize);
        };
        this->_udpServer->onServerDataSent = [&](ConnectionToClientPtr &client, sa::ByteBuffer &buffer) {
            (void) client;
            (void) buffer;
            spdlog::info("Sent packet to client ({}): ({} bytes)", client->getId(), buffer.size());
        };
        this->_udpServer->onClientConnect = [&](ConnectionToClientPtr &client) {
            spdlog::info("Client try to connect {}:{}", client->getIp(), client->getPort());
            return this->_playerCount + 1 <= this->_maxPlayers;
        };
        this->_udpServer->onClientConnected = [&](ConnectionToClientPtr &client) { this->onUdpClientConnected(client); };
        this->_udpServer->onClientDisconnected = [&](ConnectionToClientPtr &client) { this->onUdpClientDisconnected(client); };
    }

    void GameServer::registerTcpPackets() {
        int id = 0;
        // register server -> client packets
        this->_tcpPacketRegistry->registerPacket<packet::S2CPlayerAuthentified>(id++);
        // register client -> server packets
        this->_tcpPacketRegistry->registerPacket<packet::C2SPlayerHandshake>(id++);

        this->_tcpServer->registerHandler<packet::C2SPlayerHandshake>([&](auto &client, auto &packet){ this->onPlayerHandshake(client, packet); });
    }

    void GameServer::registerUdpPackets()
    {
        int id = 0;
        // register server -> client packets
        this->_udpPacketRegistry->registerPacket<packet::S2CEntitySpawn>(id++);
        this->_udpPacketRegistry->registerPacket<packet::S2CSpawnBullet>(id++);
        // register client -> server packets
        this->_udpPacketRegistry->registerPacket<packet::C2SPrepareShoot>(id++);
        this->_udpPacketRegistry->registerPacket<packet::C2SPlayerShoot>(id++);
    }

    void GameServer::onTcpClientConnected(ConnectionToClientPtr &client)
    {
        this->_logger->info("Client connected id: {}", client->getId());
    }

    void GameServer::onTcpClientDisconnected(ConnectionToClientPtr &client)
    {
        this->_logger->info("Client disconnected id: {}", client->getId());
    }

    void GameServer::onUdpClientConnected(ConnectionToClientPtr &client)
    {
        this->_logger->info("Client connected id: {}", client->getId());
    }

    void GameServer::onUdpClientDisconnected(ConnectionToClientPtr &client)
    {
        this->_logger->info("Client disconnected id: {}", client->getId());
    }

    //
    // TCP C2S Packets
    //

    void GameServer::onPlayerHandshake(ConnectionToClientPtr &client, packet::C2SPlayerHandshake &packet)
    {
        this->_logger->info("Player {} handshake", packet.name);
        //client->send(std::make_shared<packet::S2CPlayerAuthentified>(packet.playerName));
    }

    //
    // UDP C2S Packets
    //


} // namespace rtype::server
