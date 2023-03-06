/*
** EPITECH PROJECT, 2023
** Network.cpp
** File description:
** Network.cpp
*/

#include "network/NetworkManager.hpp"
#include "Bullet.hpp"
#include "Player.hpp"


using namespace rtype::network; // NOLINT

namespace rtype::client::network {
    std::shared_ptr<NetworkManager> NetworkManager::networkManager = nullptr;

    std::shared_ptr<NetworkManager> &NetworkManager::getInstance()
    {
        if (networkManager == nullptr)
            networkManager = std::shared_ptr<NetworkManager>(new NetworkManager());
        return networkManager;
    }

    void NetworkManager::init()
    {
        this->_logger = spdlog::stdout_color_mt("NetworkManager");
        this->_tcpPacketRegistry = std::make_shared<sa::PacketRegistry>();
        this->_udpPacketRegistry = std::make_shared<sa::PacketRegistry>();

        this->_tcpClient = sa::TCPClient::create(this->_tcpPacketRegistry);
        this->_udpClient = sa::UDPClient::create(this->_udpPacketRegistry);

        try {
            this->_tcpClient->init();
        } catch (std::exception &e) {
            this->_logger->error("Failed to init TCP client: {}", e.what());
            throw std::runtime_error("Failed to init TCP client: " + std::string(e.what()));
        }
        try {
            this->_udpClient->init();
        } catch (std::exception &e) {
            this->_logger->error("Failed to init UDP client: {}", e.what());
            throw std::runtime_error("Failed to init UDP client: " + std::string(e.what()));
        }

        this->registerTcpCallback();
        this->registerUdpCallback();

        this->registerTcpPackets();
        this->registerUdpPackets();
    }

    void NetworkManager::connectTcpClient(const std::string &host, std::uint16_t port)
    {
        this->_tcpClient->connect(host, port);
    }

    void NetworkManager::connectUdpClient(const std::string &host, std::uint16_t port)
    {
        this->_udpClient->connect(host, port);
    }

    void NetworkManager::runTcpClient()
    {
        this->_tcpClient->asyncRun();
    }

    void NetworkManager::runUdpClient()
    {
        this->_udpClient->asyncRun();
    }

    void NetworkManager::stopTcpClient()
    {
        this->_tcpClient->stop();
    }

    void NetworkManager::stopUdpClient()
    {
        this->_udpClient->stop();
    }

    void NetworkManager::send(sa::AbstractPacket &packet)
    {
        if (packet.isTCP())
            this->_tcpClient->send(packet);
        else if (packet.isUDP())
            this->_udpClient->send(packet);
        else
            this->_logger->error("Packet is not TCP or UDP");
    }

    void NetworkManager::send(const std::shared_ptr<sa::AbstractPacket> &packet)
    {
        this->send(*packet);
    }

    void NetworkManager::send(const std::unique_ptr<sa::AbstractPacket> &packet)
    {
        this->send(*packet);
    }

    void NetworkManager::registerUdpCallback()
    {
        this->_udpClient->onClientConnected = [&](ConnectionToServerPtr &server) {
            this->_logger->info("UDP Connected to server");
        };
        this->_udpClient->onClientDisconnected = [&](ConnectionToServerPtr &server, bool forced) {
            this->_logger->info("UDP Disconnected from server!");
        };
        this->_udpClient->onClientDataReceived = [&](ConnectionToServerPtr &server, std::uint16_t packetId, std::uint16_t packetSize, sa::ByteBuffer &buffer) {
            spdlog::info("Received data from server!");
        };
        this->_udpClient->onClientDataSent = [&](ConnectionToServerPtr &server, sa::ByteBuffer &buffer) {
//            spdlog::info("Data sent to server! Bytes: {}", buffer.size());
        };
    }

    void NetworkManager::registerTcpCallback()
    {
        this->_tcpClient->onClientConnected = [&](ConnectionToServerPtr &server) {
            this->_logger->info("TCP Connected to server, sending handshake");
            this->send(std::make_shared<packet::C2SPlayerHandshake>(this->imGuiUsername));
        };
        this->_tcpClient->onClientDisconnected = [&](ConnectionToServerPtr &server, bool forced) {
            this->_logger->info("TCP Disconnected from server!");
        };
        this->_tcpClient->onClientDataReceived = [&](ConnectionToServerPtr &server, std::uint16_t packetId, std::uint16_t packetSize, sa::ByteBuffer &buffer) {
//            spdlog::info("Received data from server!");
        };
        this->_tcpClient->onClientDataSent = [&](ConnectionToServerPtr &server, sa::ByteBuffer &buffer) {
//            spdlog::info("Data sent to server! Bytes: {}", buffer.size());
        };
    }

    void NetworkManager::registerUdpPackets()
    {
        static std::uint16_t id = 1;
        // register server -> client packets
        this->_udpPacketRegistry->registerPacket<packet::S2CEntityMove>(id++);
        this->_udpPacketRegistry->registerPacket<packet::S2CEntitySpawn>(id++);
        this->_udpPacketRegistry->registerPacket<packet::S2CPlayerMove>(id++);
        this->_udpPacketRegistry->registerPacket<packet::S2CRemoveEntity>(id++);
        this->_udpPacketRegistry->registerPacket<packet::S2CRemovePlayer>(id++);
        this->_udpPacketRegistry->registerPacket<packet::S2CSpawnBullet>(id++);
        this->_udpPacketRegistry->registerPacket<packet::S2CSpawnPlayer>(id++);
        // register client -> server packets
        this->_udpPacketRegistry->registerPacket<packet::C2SClientConnected>(id++);
        this->_udpPacketRegistry->registerPacket<packet::C2SPrepareShoot>(id++);
        this->_udpPacketRegistry->registerPacket<packet::C2SPlayerShoot>(id++);
        this->_udpPacketRegistry->registerPacket<packet::C2SKillEntity>(id++);
        this->_udpPacketRegistry->registerPacket<packet::C2SKillPlayer>(id++);

        this->handleUdpPackets();
    }

    void NetworkManager::registerTcpPackets()
    {
        static std::uint16_t id = 1;
        // register server -> client packets
        this->_tcpPacketRegistry->registerPacket<packet::S2CPlayerAuthentified>(id++);
        this->_tcpPacketRegistry->registerPacket<packet::S2CPlayerScore>(id++);
        // register client -> server packets
        this->_tcpPacketRegistry->registerPacket<packet::C2SClientDisconnecting>(id++);
        this->_tcpPacketRegistry->registerPacket<packet::C2SPlayerHandshake>(id++);

        this->handleTcpPackets();
    }

    void NetworkManager::handleUdpPackets()
    {
        static auto &textureManager = engine::Manager::getTextureManager();
        static auto &entityManager = engine::Manager::getEntityManager();

        this->_udpClient->registerHandler<packet::S2CEntityMove>([&](ConnectionToServerPtr &server, packet::S2CEntityMove &packet) {
            this->_logger->info("Received S2CEntityMove packet");
            //TODO: move entity
        });
        this->_udpClient->registerHandler<packet::S2CEntitySpawn>([&](ConnectionToServerPtr &server, packet::S2CEntitySpawn &packet) {
            this->_logger->info("Received S2CEntitySpawn packet");
            //TODO: spawn entity
        });
        this->_udpClient->registerHandler<packet::S2CPlayerMove>([&](ConnectionToServerPtr &server, packet::S2CPlayerMove &packet) {
            this->_logger->info("Received S2CPlayerMove packet");
            //TODO: move player
        });
        this->_udpClient->registerHandler<packet::S2CRemoveEntity>([&](ConnectionToServerPtr &server, packet::S2CRemoveEntity &packet) {
            this->_logger->info("Received S2CRemoveEntity packet");
            // TODO: remove entity
        });
        this->_udpClient->registerHandler<packet::S2CRemovePlayer>([&](ConnectionToServerPtr &server, packet::S2CRemovePlayer &packet) {
            this->_logger->info("Received S2CRemovePlayer packet");
            //TODO: remove player, maybe useless
        });
        this->_udpClient->registerHandler<packet::S2CSpawnBullet>([&](ConnectionToServerPtr &server, packet::S2CSpawnBullet &packet) {
            this->_logger->info("Received S2CSpawnBullet packet");
            //TODO: spawn bullet
        });
        this->_udpClient->registerHandler<packet::S2CSpawnPlayer>([&](ConnectionToServerPtr &server, packet::S2CSpawnPlayer &packet) {
            this->_logger->info("Received S2CSpawnPlayer packet");
            const sf::Vector2f pos = {static_cast<float>(packet.x), static_cast<float>(packet.y)};
            auto player = std::make_shared<Player>("player", textureManager->getTextureByName("ship"), "bullet", pos, true);
            entityManager->addPrefab(player);
            //TODO: a player
        });

        /*this->_udpClient->registerHandler<packet::C2SClientConnected>([&](ConnectionToServerPtr &server, packet::C2SClientConnected &packet) {
            //TODO: a player
        });
        this->_udpClient->registerHandler<packet::C2SPlayerShoot>([&](ConnectionToServerPtr &server, packet::C2SPlayerShoot &packet) {
            //TODO: spawn bullet
            const sf::Vector2f pos = { static_cast<float>(packet.x), static_cast<float>(packet.y) };
            auto bullet = std::make_shared<Bullet>("bullet", uranus::ecs::component::Position { pos.x, pos.y }, textureManager->getTextureByName("bullet"));
            entityManager->addPrefab(bullet);
        });
        this->_udpClient->registerHandler<packet::C2SKillEntity>([&](ConnectionToServerPtr &server, packet::C2SKillEntity &packet) {
            //TODO: kill entity
        });
        this->_udpClient->registerHandler<packet::C2SKillPlayer>([&](ConnectionToServerPtr &server, packet::C2SKillPlayer &packet) {
            //TODO: kill player
        });
        this->_udpClient->registerHandler<packet::S2CEntityMove>([&](ConnectionToServerPtr &server, packet::S2CEntityMove &packet) {
           //TODO: move entity
        });
        this->_udpClient->registerHandler<packet::S2CPlayerMove>([&](ConnectionToServerPtr &server, packet::S2CPlayerMove &packet) {
            //TODO: move player
        });*/
    }

    void NetworkManager::handleTcpPackets()
    {
        this->_tcpClient->registerHandler<packet::S2CPlayerAuthentified>([&](ConnectionToServerPtr &server, packet::S2CPlayerAuthentified &packet) {
            spdlog::info("Received S2CPlayerAuthentified packet {} {}", packet.name, packet.uid);
            try {
                this->_udpClient->connect(this->imGuiHost, this->udpPort);
                this->runUdpClient();
            } catch(std::exception &e) {
                this->_logger->error("Failed to connect UDP client: {}", e.what());
                return;
            }
            this->_udpClient->send(std::make_shared<packet::C2SClientConnected>(packet.uid));
        });
        this->_tcpClient->registerHandler<packet::S2CPlayerScore>([&](ConnectionToServerPtr &server, packet::S2CPlayerScore &packet) {
            spdlog::info("Received S2CPlayerScore packet {} {}", packet.uid, packet.score);
        });
    }
}
