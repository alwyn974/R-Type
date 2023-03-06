/*
** EPITECH PROJECT, 2023
** Packets.hpp
** File description:
** Packets.hpp
*/

#ifndef R_TYPE_PACKETS_HPP
#define R_TYPE_PACKETS_HPP

/**
 * @brief All packets used in the project
 * @file Packets.hpp
 */

#include "packets/tcp/client/C2SPlayerHandshake.hpp"
#include "packets/tcp/server/S2CPlayerAuthentified.hpp"
#include "packets/tcp/server/S2CPlayerScore.hpp"
#include "packets/udp/client/C2SClientConnect.hpp"
#include "packets/udp/client/C2SClientMove.hpp"
#include "packets/udp/client/C2SPlayerPrepareShoot.hpp"
#include "packets/udp/client/C2SPlayerReady.hpp"
#include "packets/udp/client/C2SPlayerShoot.hpp"
#include "packets/udp/client/C2SKillEntity.hpp"
#include "packets/udp/client/C2SKillPlayer.hpp"
#include "packets/udp/client/C2SSceneLoaded.hpp"
#include "packets/tcp/client/C2SClientDisconnecting.hpp"
#include "packets/udp/server/S2CClientConnected.hpp"
#include "packets/udp/server/S2CEntityMove.hpp"
#include "packets/udp/server/S2CEntitySpawn.hpp"
#include "packets/udp/server/S2CGameStarted.hpp"
#include "packets/udp/server/S2CPlayerMove.hpp"
#include "packets/udp/server/S2CRemoveEntity.hpp"
#include "packets/udp/server/S2CRemovePlayer.hpp"
#include "packets/udp/server/S2CSpawnBullet.hpp"
#include "packets/udp/server/S2CSpawnPlayer.hpp"
#include "packets/udp/server/S2CSyncPlayer.hpp"

namespace rtype::network::packet {
    class RegisterPacket {
    public:
        static void registerPackets(std::shared_ptr<sa::PacketRegistry> &udpRegistry, std::shared_ptr<sa::PacketRegistry> &tcpRegistry);
    };
}

#endif // R_TYPE_PACKETS_HPP
