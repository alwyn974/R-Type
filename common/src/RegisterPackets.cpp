/*
** EPITECH PROJECT, 2023
** Dummy.cpp
** File description:
** Dummy.cpp
*/

#include "Packets.hpp"

namespace rtype::network::packet {
    void RegisterPacket::registerPackets(std::shared_ptr<sa::PacketRegistry> &udpRegistry, std::shared_ptr<sa::PacketRegistry> &tcpRegistry)
    {
        std::uint16_t udpId = 1;
        // register server -> client packets
        udpRegistry->registerPacket<packet::S2CClientConnected>(udpId++);
        udpRegistry->registerPacket<packet::S2CEntityMove>(udpId++);
        udpRegistry->registerPacket<packet::S2CEntitySpawn>(udpId++);
        udpRegistry->registerPacket<packet::S2CGameStarted>(udpId++);
        udpRegistry->registerPacket<packet::S2CPlayerMove>(udpId++);
        udpRegistry->registerPacket<packet::S2CRemoveEntity>(udpId++);
        udpRegistry->registerPacket<packet::S2CRemovePlayer>(udpId++);
        udpRegistry->registerPacket<packet::S2CSpawnBullet>(udpId++);
        udpRegistry->registerPacket<packet::S2CSpawnPlayer>(udpId++);
        udpRegistry->registerPacket<packet::S2CSyncPlayer>(udpId++);
        // register client -> server packets
        udpRegistry->registerPacket<packet::C2SClientConnect>(udpId++);
        udpRegistry->registerPacket<packet::C2SClientMove>(udpId++);
        udpRegistry->registerPacket<packet::C2SKillEntity>(udpId++);
        udpRegistry->registerPacket<packet::C2SKillPlayer>(udpId++);
        udpRegistry->registerPacket<packet::C2SPrepareShoot>(udpId++);
        udpRegistry->registerPacket<packet::C2SPlayerReady>(udpId++);
        udpRegistry->registerPacket<packet::C2SPlayerShoot>(udpId++);
        udpRegistry->registerPacket<packet::C2SSceneLoaded>(udpId++);

        std::uint16_t tcpId = 1;
        // register server -> client packets
        tcpRegistry->registerPacket<packet::S2CPlayerAuthentified>(tcpId++);
        tcpRegistry->registerPacket<packet::S2CPlayerScore>(tcpId++);
        // register client -> server packets
        tcpRegistry->registerPacket<packet::C2SClientDisconnecting>(tcpId++);
        tcpRegistry->registerPacket<packet::C2SPlayerHandshake>(tcpId++);
    }
}