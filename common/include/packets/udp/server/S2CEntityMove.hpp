/*
** EPITECH PROJECT, 2023
** S2CEntityMove.hpp
** File description:
** S2CEntityMove.hpp
*/

#pragma once

#include <saturnity/Saturnity.hpp>

namespace rtype::network::packet {
    class S2CEntityMove : public sa::AbstractPacket {
    public:
        std::uint32_t entityId;
        float x;
        float y;

        explicit S2CEntityMove(std::uint32_t entityId, float x, float y) : sa::AbstractPacket(sa::AbstractPacket::UDP)
        {
            this->entityId = entityId;
            this->x = x;
            this->y = y;
        }

        S2CEntityMove() : sa::AbstractPacket(sa::AbstractPacket::UDP)
        {
            this->entityId = 0;
            this->x = 0;
            this->y = 0;
        }

        void toBytes(sa::ByteBuffer &byteBuffer) override
        {
            byteBuffer.writeUInt(this->entityId);
            byteBuffer.writeFloat(this->x);
            byteBuffer.writeFloat(this->y);
        }

        void fromBytes(sa::ByteBuffer &byteBuffer) override
        {
            this->entityId = byteBuffer.readUInt();
            this->x = byteBuffer.readFloat();
            this->y = byteBuffer.readFloat();
        }
    };
}