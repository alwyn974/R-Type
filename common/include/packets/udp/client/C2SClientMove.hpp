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
        int x, y;

        C2SClientMove() : sa::AbstractPacket(sa::AbstractPacket::EnumPacketType::UDP)
        {
            this->entityId = 0;
            this->x = 0;
            this->y = 0;
        };
        C2SClientMove(std::uint32_t entityId, int x, int y) : C2SClientMove()
        {
            this->entityId = entityId;
            this->x = x;
            this->y = y;
        }

        void toBytes(sa::ByteBuffer &byteBuffer) override
        {
            byteBuffer.writeUInt(entityId);
            byteBuffer.writeInt(x);
            byteBuffer.writeInt(y);
        }

        void fromBytes(sa::ByteBuffer &byteBuffer) override
        {
            entityId = byteBuffer.readUInt();
            x = byteBuffer.readInt();
            y = byteBuffer.readInt();
        }
    };
}

#endif //R_TYPE_C2SCLIENTMOVE_HPP
