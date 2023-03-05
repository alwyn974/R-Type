/*
** EPITECH PROJECT, 2023
** S2CEntitySpawn.hpp
** File description:
** S2CEntitySpawn.hpp
*/

#ifndef R_TYPE_S2CENTITYSPAWN_HPP
#define R_TYPE_S2CENTITYSPAWN_HPP

#include <saturnity/Saturnity.hpp>

namespace rtype::network::packet {
    struct S2CEntitySpawn : public sa::AbstractPacket {
        std::uint16_t entityId = -1;
        std::uint16_t x = 0, y = 0;

        S2CEntitySpawn() : sa::AbstractPacket(sa::AbstractPacket::EnumPacketType::UDP) {};

        void toBytes(sa::ByteBuffer &byteBuffer) override
        {
            byteBuffer.writeUShort(entityId);
            byteBuffer.writeUShort(x);
            byteBuffer.writeUShort(y);
        }

        void fromBytes(sa::ByteBuffer &byteBuffer) override
        {
            entityId = byteBuffer.readUShort();
            x = byteBuffer.readUShort();
            y = byteBuffer.readUShort();
        }
    };
} // namespace rtype::network::packet

#endif // R_TYPE_S2CENTITYSPAWN_HPP
