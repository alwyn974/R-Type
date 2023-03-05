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
#include "packets/udp/client/C2SClientConnected.hpp"
#include "packets/udp/client/C2SPlayerPrepareShoot.hpp"
#include "packets/udp/client/C2SPlayerShoot.hpp"
#include "packets/udp/client/C2SSkillEntity.hpp"
#include "packets/udp/client/C2SSkillPlayer.hpp"
#include "packets/udp/server/S2CClientDisconnect.hpp"
#include "packets/udp/server/S2CEntityMove.hpp"
#include "packets/udp/server/S2CEntitySpawn.hpp"
#include "packets/udp/server/S2CPlayerMove.hpp"
#include "packets/udp/server/S2CRemoveEntity.hpp"
#include "packets/udp/server/S2CRemovePlayer.hpp"
#include "packets/udp/server/S2CSpawnPlayer.hpp"
#include "packets/udp/server/S2CSpawnBullet.hpp"

#endif // R_TYPE_PACKETS_HPP
