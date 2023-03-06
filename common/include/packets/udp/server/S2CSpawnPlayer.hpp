/*
** EPITECH PROJECT, 2023
** S2CSpawnPlayer.hpp
** File description:
** S2CSpawnPlayer.hpp
*/

#pragma once

#include <saturnity/Saturnity.hpp>
#include "S2CEntitySpawn.hpp"

namespace rtype::network::packet {
    class S2CSpawnPlayer : public S2CEntitySpawn {
    public:
        std::string name;
        S2CSpawnPlayer() : S2CEntitySpawn() {}
        S2CSpawnPlayer(const std::string &name, std::uint32_t entityId, std::uint16_t x, std::uint16_t y) : S2CEntitySpawn(entityId, x, y)
        {
            this->name = name;
        };

        void toBytes(sa::ByteBuffer &byteBuffer) override
        {
            S2CEntitySpawn::toBytes(byteBuffer);
            byteBuffer.writeString(name);
        }

        void fromBytes(sa::ByteBuffer &byteBuffer) override
        {
            S2CEntitySpawn::fromBytes(byteBuffer);
            name = byteBuffer.readString();
        }
    };
}
