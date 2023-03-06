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
        float velX;
        float velY;

        explicit S2CEntityMove(std::uint32_t entityId, float velX, float velY) : sa::AbstractPacket(sa::AbstractPacket::UDP)
        {
            this->entityId = entityId;
            this->velX = velX;
            this->velY = velY;
        }

        S2CEntityMove() : sa::AbstractPacket(sa::AbstractPacket::UDP)
        {
            this->entityId = 0;
            this->velX = 0;
            this->velY = 0;
        }

        void toBytes(sa::ByteBuffer &byteBuffer) override
        {
            byteBuffer.writeUInt(this->entityId);
            byteBuffer.writeFloat(this->velX);
            byteBuffer.writeFloat(this->velY);
        }

        void fromBytes(sa::ByteBuffer &byteBuffer) override
        {
            this->entityId = byteBuffer.readUInt();
            this->velX = byteBuffer.readFloat();
            this->velY = byteBuffer.readFloat();
        }
    };
}