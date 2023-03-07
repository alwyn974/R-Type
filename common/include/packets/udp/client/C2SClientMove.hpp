/*
** EPITECH PROJECT, 2023
** C2SClientMove.hpp
** File description:
** C2SClientMove.hpp
*/

#ifndef R_TYPE_C2SCLIENTMOVE_HPP
#define R_TYPE_C2SCLIENTMOVE_HPP

#include <saturnity/Saturnity.hpp>

namespace rtype::network::packet {
    class C2SClientMove : public sa::AbstractPacket {
    public:
        std::uint32_t entityId;
        float velX, velY;

        C2SClientMove() : sa::AbstractPacket(sa::AbstractPacket::EnumPacketType::UDP)
        {
            this->entityId = 0;
            this->velX = 0;
            this->velY = 0;
        };
        C2SClientMove(std::uint32_t entityId, float x, float y) : C2SClientMove()
        {
            this->entityId = entityId;
            this->velX = x;
            this->velY = y;
        }

        void toBytes(sa::ByteBuffer &byteBuffer) override
        {
            byteBuffer.writeUInt(entityId);
            byteBuffer.writeInt(velX);
            byteBuffer.writeInt(velY);
        }

        void fromBytes(sa::ByteBuffer &byteBuffer) override
        {
            entityId = byteBuffer.readUInt();
            velX = byteBuffer.readInt();
            velY = byteBuffer.readInt();
        }
    };
}

#endif //R_TYPE_C2SCLIENTMOVE_HPP
