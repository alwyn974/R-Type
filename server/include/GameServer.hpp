/*
** EPITECH PROJECT, 2023
** GameServer.hpp
** File description:
** GameServer.hpp
*/

#ifndef R_TYPE_GAMESERVER_HPP
#define R_TYPE_GAMESERVER_HPP

#include "game/Game.hpp"
#include <Packets.hpp>
#include <saturnity/Saturnity.hpp>

namespace rtype::server {
    using namespace rtype::network; // NOLINT

    class GameServer {
    public:
        explicit GameServer(const std::string &host, std::uint16_t tcpPort, std::uint16_t udpPort, int maxPlayers);

        void init();
        void start();
        void stop();

        const std::shared_ptr<sa::TCPServer> &getTcpServer() const { return _tcpServer; }
        const std::shared_ptr<sa::UDPServer> &getUdpServer() const { return _udpServer; }
        const std::shared_ptr<spdlog::logger> &getLogger() const { return _logger; }

        void setTcpServer(const std::shared_ptr<sa::TCPServer> &tcpServer) { _tcpServer = tcpServer; }
        void setUdpServer(const std::shared_ptr<sa::UDPServer> &udpServer) { _udpServer = udpServer; }
        void setLogger(const std::shared_ptr<spdlog::logger> &logger) { _logger = logger; }

    private:
        std::shared_ptr<sa::PacketRegistry> _udpPacketRegistry;
        std::shared_ptr<sa::PacketRegistry> _tcpPacketRegistry;
        std::shared_ptr<sa::TCPServer> _tcpServer;
        std::shared_ptr<sa::UDPServer> _udpServer;
        std::shared_ptr<spdlog::logger> _logger;
        std::string _host;
        std::uint16_t _tcpPort;
        std::uint16_t _udpPort;

        int _playerCount;
        int _maxPlayers;
        std::unordered_map<UUIDv4::UUID, game::Player> _players;

        void registerTcpCallbacks();
        void registerUdpCallbacks();

        void registerTcpPackets();
        void registerUdpPackets();

        void onTcpClientConnected(ConnectionToClientPtr &client);
        void onTcpClientDisconnected(ConnectionToClientPtr &client);

        void onUdpClientConnected(ConnectionToClientPtr &client);
        void onUdpClientDisconnected(ConnectionToClientPtr &client);

        //
        // TCP
        //

        void onPlayerHandshake(ConnectionToClientPtr &client, packet::C2SPlayerHandshake &packet);

        //
        // UDP
        //

        void onClientConnected(ConnectionToClientPtr &client, packet::C2SClientConnected &packet);

    };
} // namespace rtype::server

#endif // R_TYPE_GAMESERVER_HPP
