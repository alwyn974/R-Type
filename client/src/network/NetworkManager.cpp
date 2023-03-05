/*
** EPITECH PROJECT, 2023
** Network.cpp
** File description:
** Network.cpp
*/

#include "network/NetworkManager.hpp"

using namespace rtype::network; // NOLINT

namespace rtype::client::network {
    std::shared_ptr<NetworkManager> NetworkManager::networkManager = nullptr;

    std::shared_ptr<NetworkManager> NetworkManager::getInstance()
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

    void NetworkManager::registerUdpPackets()
    {
        int id = 0;
        // register server -> client packets
        this->_udpPacketRegistry->registerPacket<packet::S2CEntitySpawn>(id++);
        this->_udpPacketRegistry->registerPacket<packet::S2CSpawnBullet>(id++);
        // register client -> server packets
        this->_udpPacketRegistry->registerPacket<packet::C2SPrepareShoot>(id++);
        this->_udpPacketRegistry->registerPacket<packet::C2SPlayerShoot>(id++);

        this->handleUdpPackets();
    }

    void NetworkManager::registerTcpPackets()
    {
        int id = 0;
        // register server -> client packets
        this->_tcpPacketRegistry->registerPacket<packet::S2CPlayerAuthentified>(id++);
        // register client -> server packets
        this->_tcpPacketRegistry->registerPacket<packet::C2SPlayerHandshake>(id++);

        this->handleTcpPackets();
    }

    void NetworkManager::handleUdpPackets()
    {
        this->_udpClient->registerHandler<packet::S2CSpawnBullet>([&](ConnectionToServerPtr &server, packet::S2CSpawnBullet &packet) {
            spdlog::info("Received S2CSpawnBullet packet");
            // spawn entity
        });
    }

    void NetworkManager::handleTcpPackets()
    {

    }
}
