/*
** EPITECH PROJECT, 2023
** Network.hpp
** File description:
** Network.hpp
*/

#ifndef R_TYPE_NETWORKMANAGER_HPP
#define R_TYPE_NETWORKMANAGER_HPP

#include "uranus/engine/Engine.hpp"
#include "Packets.hpp"
#include "Random.hpp"
#include <saturnity/Saturnity.hpp>

namespace rtype::client::network {
    class NetworkManager {
    public:
        static std::shared_ptr<NetworkManager> &getInstance();

        void init();

        void connectTcpClient(const std::string &host, std::uint16_t port);
        void connectUdpClient(const std::string &host, std::uint16_t port);

        void runTcpClient();
        void runUdpClient();

        void stopTcpClient();
        void stopUdpClient();

        void send(sa::AbstractPacket &packet);
        void send(const std::shared_ptr<sa::AbstractPacket> &packet);
        void send(const std::unique_ptr<sa::AbstractPacket> &packet);

        const std::shared_ptr<sa::TCPClient> &getTcpClient() const
        {
            return _tcpClient;
        }

        const std::shared_ptr<sa::UDPClient> &getUdpClient() const
        {
            return _udpClient;
        }

        std::string imGuiHost = "127.0.0.1";
        std::string imGuiTcpPort = "2409";
        std::string imGuiUdpPort = "2410";
        std::string imGuiUsername; // NOLINT
        bool imGuiReady;
        std::uint16_t tcpPort = 2409;
        std::uint16_t udpPort = 2410;

        std::uint32_t uid = 0;
    private:
        Random _random;

        NetworkManager()
        {
            imGuiUsername = "Player-" + std::to_string(_random.generate(0, 99999999));
//            this->imGuiHost.reserve(128);
//            this->imGuiTcpPort.reserve(128);
//            this->imGuiUdpPort.reserve(128);
//            this->imGuiUsername.reserve(128);
            this->imGuiReady = false;
        }

        static std::shared_ptr<NetworkManager> networkManager;
        std::shared_ptr<spdlog::logger> _logger;

        std::shared_ptr<sa::PacketRegistry> _udpPacketRegistry;
        std::shared_ptr<sa::PacketRegistry> _tcpPacketRegistry;

        std::shared_ptr<sa::TCPClient> _tcpClient;
        std::shared_ptr<sa::UDPClient> _udpClient;

        void registerUdpCallback();
        void registerTcpCallback();

        void registerUdpPacketHandlers();
        void registerTcpPacketHandlers();
    };
}

#endif //R_TYPE_NETWORKMANAGER_HPP
