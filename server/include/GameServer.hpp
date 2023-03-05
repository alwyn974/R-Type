/*
** EPITECH PROJECT, 2023
** GameServer.hpp
** File description:
** GameServer.hpp
*/

#ifndef R_TYPE_GAMESERVER_HPP
#define R_TYPE_GAMESERVER_HPP

#include <saturnity/Saturnity.hpp>
#include "Packets.hpp"

namespace rtype::server {
    class GameServer {
    public:
        GameServer(const std::string &host, std::uint16_t tcpPort, std::uint16_t udpPort);

        void init();
        void start();
        void stop();

        const std::shared_ptr<spdlog::logger> &getLogger() const;
        const std::shared_ptr<sa::TCPServer> &getTcpServer() const;
        const std::shared_ptr<sa::UDPServer> &getUdpServer() const;

        void setTcpServer(const std::shared_ptr<sa::TCPServer> &tcpServer);
        void setUdpServer(const std::shared_ptr<sa::UDPServer> &udpServer);
        void setLogger(const std::shared_ptr<spdlog::logger> &logger);

    private:
        std::shared_ptr<sa::PacketRegistry> _udpPacketRegistry;
        std::shared_ptr<sa::PacketRegistry> _tcpPacketRegistry;
        std::shared_ptr<sa::TCPServer> _tcpServer;
        std::shared_ptr<sa::UDPServer> _udpServer;
        std::shared_ptr<spdlog::logger> _logger;
        std::string _host;
        std::uint16_t _tcpPort;
        std::uint16_t _udpPort;

        void registerTcpCallbacks();
        void registerUdpCallbacks();

        void registerUdpPackets();
        void registerTcpPackets();
    };
}

#endif //R_TYPE_GAMESERVER_HPP
