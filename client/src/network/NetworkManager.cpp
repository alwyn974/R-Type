/*
** EPITECH PROJECT, 2023
** Network.cpp
** File description:
** Network.cpp
*/

#include "network/NetworkManager.hpp"
#include "Bullet.hpp"
#include "Player.hpp"
#include "scene/SceneStage1.hpp"
//#include "uranus/ecs/Components.hpp"

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

        packet::RegisterPacket::registerPackets(this->_udpPacketRegistry, this->_tcpPacketRegistry);
        this->registerUdpPacketHandlers();
        this->registerTcpPacketHandlers();
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
//            this->_logger->info("UDP Received data from server!");
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

    void NetworkManager::registerUdpPacketHandlers()
    {
        static auto &sceneManager = engine::Manager::getSceneManager();
        static auto &textureManager = engine::Manager::getTextureManager();
        static auto &entityManager = engine::Manager::getEntityManager();
        static auto &r = engine::Manager::getRegistry();

        this->_udpClient->registerHandler<packet::S2CClientConnected>([&](ConnectionToServerPtr &server, packet::S2CClientConnected &packet) {
            this->_logger->info("Received S2CClientConnected packet");
            this->uid = packet.uid;
        });
        this->_udpClient->registerHandler<packet::S2CEntityMove>([&](ConnectionToServerPtr &server, packet::S2CEntityMove &packet) {
            this->_logger->info("Received S2CEntityMove packet");
            //TODO: move entity
        });
        this->_udpClient->registerHandler<packet::S2CEntitySpawn>([&](ConnectionToServerPtr &server, packet::S2CEntitySpawn &packet) {
            this->_logger->info("Received S2CEntitySpawn packet");
            //TODO: spawn entity
        });
        this->_udpClient->registerHandler<packet::S2CGameStarted>([&](ConnectionToServerPtr &server, packet::S2CGameStarted &packet) {
            this->_logger->info("Received S2CGameStarted packet");
            try {
                auto scene = std::dynamic_pointer_cast<SceneStage1>(sceneManager->getActualScene());
                scene->wave(uranus::ecs::component::Position{0, 0});
            } catch (const std::exception &) {
                this->_logger->error("Received S2CGameStarted packet for unknown entity");
                return;
            }
        });
        this->_udpClient->registerHandler<packet::S2CPlayerChargingBullet>([&](ConnectionToServerPtr &server, packet::S2CPlayerChargingBullet &packet) {
            this->_logger->info("Received S2CPlayerChargingBullet packet {} from {}", packet.entityId, packet.playerId);
            auto bullet = std::make_shared<Bullet>("bullet", uranus::ecs::component::Position {packet.x, packet.y},
                textureManager->getTextureByName("bullet"), packet.entityId, true /*packet.playerId == this->uid*/);
            bullet->setCanMove(true);
            entityManager->addPrefab(bullet);
        });
        this->_udpClient->registerHandler<packet::S2CPlayerMove>([&](ConnectionToServerPtr &server, packet::S2CPlayerMove &packet) {
//            this->_logger->info("Received S2CPlayerMove packet {}", packet.entityId);
            try {
                auto base = entityManager->getPrefabByNetworkId(packet.entityId);
//                auto &vel = r->getComponent<uranus::ecs::component::Position>(base->getEntityId());
                auto &vel = r->getComponent<uranus::ecs::component::Velocity>(base->getEntityId());
                vel->x = packet.velX;
                vel->y  = packet.velY;
            } catch (const std::exception &) {
                this->_logger->error("Received S2CPlayerMove packet for unknown entity {}", packet.entityId);
                return;
            }
        });
        this->_udpClient->registerHandler<packet::S2CPlayerShootBullet>([&](ConnectionToServerPtr &server, packet::S2CPlayerShootBullet &packet) {
            this->_logger->info("Received S2CPlayerShootBullet packet {} from {}", packet.entityId, packet.playerId);
            /*try {
                auto base = entityManager->getPrefabByNetworkId(packet.entityId);
                auto bullet = std::dynamic_pointer_cast<Bullet>(base);
                bullet->setCanMove(true);
            } catch (const std::exception &) {
                this->_logger->error("Received S2CPlayerShootBullet packet for unknown entity");
                return;
            }*/
        });
        this->_udpClient->registerHandler<packet::S2CRemoveEntity>([&](ConnectionToServerPtr &server, packet::S2CRemoveEntity &packet) {
            this->_logger->info("Received S2CRemoveEntity packet");
            // TODO: remove entity
        });
        this->_udpClient->registerHandler<packet::S2CRemovePlayer>([&](ConnectionToServerPtr &server, packet::S2CRemovePlayer &packet) {
            this->_logger->info("Received S2CRemovePlayer packet");
            try {
                entityManager->removeByNetworkId(packet.entityId);
            } catch (const std::exception &) {
                this->_logger->error("Received S2CRemovePlayer packet for unknown entity");
                return;
            }
            //TODO: remove player, maybe useless
        });
        this->_udpClient->registerHandler<packet::S2CSpawnBullet>([&](ConnectionToServerPtr &server, packet::S2CSpawnBullet &packet) {
            this->_logger->info("Received S2CSpawnBullet packet");
            //TODO: spawn bullet
        });
        this->_udpClient->registerHandler<packet::S2CSpawnPlayer>([&](ConnectionToServerPtr &server, packet::S2CSpawnPlayer &packet) {
            this->_logger->info("Received S2CSpawnPlayer packet - name: {} id: {} x: {} y: {}", packet.name, packet.entityId, packet.x, packet.y);
            const sf::Vector2f pos = {static_cast<float>(packet.x), static_cast<float>(packet.y)};
            auto player = std::make_shared<Player>(packet.name, textureManager->getTextureByName("ship"), "bullet", packet.entityId, pos);
            entityManager->addPrefab(player);
        });
        this->_udpClient->registerHandler<packet::S2CSyncPlayer>([&](ConnectionToServerPtr &server, packet::S2CSyncPlayer &packet) {
            this->_logger->info("Received S2CSyncPlayer packet ({}) {} {}", packet.entityId, packet.x, packet.y);
            try {
                auto base = entityManager->getPrefabByNetworkId(packet.entityId);
                auto &pos = r->getComponent<uranus::ecs::component::Position>(base->getEntityId());
                pos->x = packet.x;
                pos->y  = packet.y;
            } catch (const std::exception &) {
                this->_logger->error("Received S2CSyncPlayer packet for unknown entity");
                return;
            }
        });
    }

    void NetworkManager::registerTcpPacketHandlers()
    {
        this->_tcpClient->registerHandler<packet::S2CPlayerAuthentified>([&](ConnectionToServerPtr &server, packet::S2CPlayerAuthentified &packet) {
            this->_logger->info("Received S2CPlayerAuthentified packet {} {}", packet.name, packet.uid);
            try {
                this->_udpClient->connect(this->imGuiHost, this->udpPort);
                this->runUdpClient();
            } catch(std::exception &e) {
                this->_logger->error("Failed to connect UDP client: {}", e.what());
                return;
            }
            this->_udpClient->send(std::make_shared<packet::C2SClientConnect>(packet.uid, packet.name));
        });
        this->_tcpClient->registerHandler<packet::S2CPlayerScore>([&](ConnectionToServerPtr &server, packet::S2CPlayerScore &packet) {
            this->_logger->info("Received S2CPlayerScore packet {} {}", packet.uid, packet.score);
        });
    }
}
