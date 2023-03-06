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
        this->_globalId = 0;
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

        packet::RegisterPacket::registerPackets(this->_udpPacketRegistry, this->_tcpPacketRegistry);
        this->registerTcpPacketHandlers();
        this->registerUdpPacketHandlers();
    }

    void GameServer::start()
    {
        this->_tcpServer->start();
        this->_udpServer->start();
        this->_tcpServer->asyncRun();
        this->_udpServer->asyncRun();
        this->_logger->info("GameServer started");

        auto start = std::chrono::high_resolution_clock::now();
        while (true) {
            auto now = std::chrono::high_resolution_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count();
            if (elapsed >= 1000) {
                this->sync();
                start = std::chrono::high_resolution_clock::now();
            }
        }
    }

    void GameServer::sync()
    {
        for (const auto &[uid, player]: this->_players)
            this->_udpServer->broadcast(std::make_shared<packet::S2CSyncPlayer>(uid, player->getX(), player->getY()));
    }

    void GameServer::stop()
    {
        this->_tcpServer->stop();
        this->_udpServer->stop();
    }

    void GameServer::registerTcpCallbacks()
    {
        this->_tcpServer->onServerDataReceived = [&](ConnectionToClientPtr &client, std::uint16_t packetId, std::uint16_t packetSize, sa::ByteBuffer &buffer) {
            this->_logger->info("TCP Received packet from client ({}): {} ({} bytes)", client->getId(), packetId, packetSize);
        };
        this->_tcpServer->onServerDataSent = [&](ConnectionToClientPtr &client, sa::ByteBuffer &buffer) {
            this->_logger->info("TCP Sent packet to client ({}): ({} bytes)", client->getId(), buffer.size());
        };
        this->_tcpServer->onClientConnect = [&](ConnectionToClientPtr &client) {
            this->_logger->info("TCP Client try to connect {}:{}", client->getIp(), client->getPort());
            return this->_playerCount + 1 <= this->_maxPlayers;
        };
        this->_tcpServer->onClientConnected = [&](ConnectionToClientPtr &client) { this->onTcpClientConnected(client); };
        this->_tcpServer->onClientDisconnected = [&](ConnectionToClientPtr &client) { this->onTcpClientDisconnected(client); };
    }

    void GameServer::registerUdpCallbacks()
    {
        this->_udpServer->onServerDataReceived = [&](ConnectionToClientPtr &client, std::uint16_t packetId, std::uint16_t packetSize, sa::ByteBuffer &buffer) {
            this->_logger->info("UDP Received packet from client ({}): {} ({} bytes)", client->getId(), packetId, packetSize);
        };
        this->_udpServer->onServerDataSent = [&](ConnectionToClientPtr &client, sa::ByteBuffer &buffer) {
            this->_logger->info("UDP Sent packet to client ({}): ({} bytes)", client->getId(), buffer.size());
        };
        this->_udpServer->onClientConnect = [&](ConnectionToClientPtr &client) {
            this->_logger->info("UDP Client try to connect {}:{}", client->getIp(), client->getPort());
            return this->_playerCount + 1 <= this->_maxPlayers;
        };
        this->_udpServer->onClientConnected = [&](ConnectionToClientPtr &client) { this->onUdpClientConnected(client); };
        this->_udpServer->onClientDisconnected = [&](ConnectionToClientPtr &client) { this->onUdpClientDisconnected(client); };
    }

    void GameServer::registerTcpPacketHandlers() {
        this->_tcpServer->registerHandler<packet::C2SClientDisconnecting>([&](auto &client, auto &packet){ this->onClientDisconnecting(client, packet); });
        this->_tcpServer->registerHandler<packet::C2SPlayerHandshake>([&](auto &client, auto &packet){ this->onPlayerHandshake(client, packet); });
    }

    void GameServer::registerUdpPacketHandlers()
    {
        this->_udpServer->registerHandler<packet::C2SClientConnect>([&](auto &client, auto &packet){ this->onClientConnected(client, packet); });
        this->_udpServer->registerHandler<packet::C2SClientMove>([&](auto &client, packet::C2SClientMove &packet) {
            if (!this->_players.contains(packet.entityId))
                return this->_logger->warn("Received C2SClientMove from unknown player ({}).", packet.entityId);
            for (auto &[uid, player]: this->_players) {
                if (player->getUdpId() == client->getId()) {
                    player->setX(player->getX() + packet.velX);
                    player->setY(player->getY() + packet.velY);
//                    player->setX(packet.velX);
//                    player->setY(packet.velY);
                    break;
                }
            }
            this->_udpServer->broadcast(std::make_shared<packet::S2CPlayerMove>(packet.entityId, packet.velX, packet.velY), client->getId());
        });
        this->_udpServer->registerHandler<packet::C2SPrepareShoot>([&](auto &client, auto &packet){
        });
        this->_udpServer->registerHandler<packet::C2SPlayerReady>([&](auto &client, packet::C2SPlayerReady &packet) {
            for (const auto &[uid, player]: this->_players) {
                if (player->getUdpId() == client->getId()) {
                    player->setReady(true);
                    this->_logger->info("Player {} is ready. ({})", player->getName(), uid);
                    break;
                }
            }
            if (std::all_of(_players.begin(), _players.end(), [&](const auto &player) {
                return player.second->isReady();
            })) {
                this->_udpServer->broadcast(std::make_shared<packet::S2CGameStarted>());
            }
        });
        this->_udpServer->registerHandler<packet::C2SPlayerShoot>([&](auto &client, auto &packet){
        });
        this->_udpServer->registerHandler<packet::C2SKillEntity>([&](auto &client, auto &packet){
        });
        this->_udpServer->registerHandler<packet::C2SKillPlayer>([&](auto &client, auto &packet){
        });
        this->_udpServer->registerHandler<packet::C2SSceneLoaded>([&](auto &client, packet::C2SSceneLoaded &packet) {
            this->_logger->info("Received C2SSceneLoaded from client ({}) - {}.", client->getId(), packet.sceneName);
            for (const auto &[uid, player]: this->_players) {
                if (player->getUdpId() != client->getId())
                    client->send(std::make_shared<packet::S2CSpawnPlayer>(player->getName(), uid, player->getX(), player->getY()));
                else
                    player->setSceneLoaded(true);
            }
        });
    }

    void GameServer::onTcpClientConnected(ConnectionToClientPtr &client)
    {
        this->_logger->info("Client connected id: {}", client->getId());
    }

    void GameServer::onTcpClientDisconnected(ConnectionToClientPtr &client)
    {
        this->_logger->info("Client disconnected id: {}", client->getId());
        for (const auto &[uid, player]: this->_players) {
            if (player->getTcpId() == client->getId()) {
                this->_players.erase(uid);
                break;
            }
        }
    }

    void GameServer::onUdpClientConnected(ConnectionToClientPtr &client)
    {
        this->_logger->info("Client connected id: {}", client->getId());
    }

    void GameServer::onUdpClientDisconnected(ConnectionToClientPtr &client)
    {
        this->_logger->info("Client disconnected id: {}", client->getId());
        for (const auto &[uid, player]: this->_players) {
            if (player->getUdpId() == client->getId()) {
                this->_players.erase(uid);
                break;
            }
        }
    }

    //
    // TCP C2S Packets
    //

    void GameServer::onPlayerHandshake(ConnectionToClientPtr &client, packet::C2SPlayerHandshake &packet)
    {
        this->_logger->info("Player {} handshake", packet.name);
        auto player = std::make_shared<game::Player>(client->getId(), -1, packet.name);
        player->setName(packet.name);
        const std::uint32_t uid = ++this->_globalId;
        this->_players[uid] = player;
        client->send(std::make_shared<packet::S2CPlayerAuthentified>(packet.name, uid));
    }

    void GameServer::onClientDisconnecting(ConnectionToClientPtr &client, packet::C2SClientDisconnecting &packet)
    {
        (void) packet;
        this->_logger->info("Client {} disconnecting", client->getId());
        for (const auto &[uid, player]: this->_players) {
            if (player->getTcpId() == client->getId()) {
                this->_players.erase(uid);
                break;
            }
        }
        this->_tcpServer->disconnect(client->getId());
    }

    //
    // UDP C2S Packets
    //

    void GameServer::onClientConnected(ConnectionToClientPtr &client, packet::C2SClientConnect &packet)
    {
        this->_logger->info("Client {} connected with UDP at {}", packet.uid, client->getId());
        if (!this->_players.contains(packet.uid))
            return this->_logger->warn("Client {} is not registered", packet.uid);
        this->_players[packet.uid]->setUdpId(client->getId());
        this->_udpServer->broadcast(std::make_shared<packet::S2CSpawnPlayer>(packet.name, packet.uid, 0, 0), client->getId());
        client->send(std::make_shared<packet::S2CClientConnected>(packet.uid));
    }

} // namespace rtype::server
