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

        std::array<char, 128> imGuiHost = {'l', 'o', 'c', 'a', 'l', 'h', 'o', 's', 't'};
        std::array<char, 5> imGuiTcpPort = {'2', '4', '0', '9'};
        std::array<char, 5> imGuiUdpPort = {'2', '4', '1', '0'};
        std::string host;
        std::uint16_t tcpPort = 2409;
        std::uint16_t udpPort = 2410;

    private:
        NetworkManager() = default;
        static std::shared_ptr<NetworkManager> networkManager;
        std::shared_ptr<spdlog::logger> _logger;

        std::shared_ptr<sa::PacketRegistry> _udpPacketRegistry;
        std::shared_ptr<sa::PacketRegistry> _tcpPacketRegistry;

        std::shared_ptr<sa::TCPClient> _tcpClient;
        std::shared_ptr<sa::UDPClient> _udpClient;

        void registerUdpCallback();
        void registerTcpCallback();

        void registerUdpPackets();
        void registerTcpPackets();

        void handleUdpPackets();
        void handleTcpPackets();
    };
}

#endif //R_TYPE_NETWORKMANAGER_HPP
