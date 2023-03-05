/*
** EPITECH PROJECT, 2023
** S2CSpawnBullet.hpp
** File description:
** S2CSpawnBullet.hpp
*/

#ifndef R_TYPE_S2CSPAWNBULLET_HPP
#define R_TYPE_S2CSPAWNBULLET_HPP

#include <saturnity/Saturnity.hpp>
#include "S2CEntitySpawn.hpp"

namespace rtype::network::packet {
    class S2CSpawnBullet : public S2CEntitySpawn {
    public:
        S2CSpawnBullet() : S2CEntitySpawn() {}

        S2CSpawnBullet(std::uint32_t entityId, std::uint16_t x, std::uint16_t y) : S2CEntitySpawn(entityId, x, y) {};

        void toBytes(sa::ByteBuffer &byteBuffer) override
        {
            S2CEntitySpawn::toBytes(byteBuffer);
        }

        void fromBytes(sa::ByteBuffer &byteBuffer) override
        {
            S2CEntitySpawn::fromBytes(byteBuffer);
        }
    };
}

#endif //R_TYPE_S2CSPAWNBULLET_HPP
