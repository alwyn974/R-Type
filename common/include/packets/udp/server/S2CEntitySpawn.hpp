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
    class S2CEntitySpawn : public sa::AbstractPacket {
    public:
        std::uint32_t entityId = 0;
        std::uint16_t x = 0, y = 0;

        S2CEntitySpawn() : sa::AbstractPacket(sa::AbstractPacket::EnumPacketType::UDP) {};
        explicit S2CEntitySpawn(std::uint32_t entityId, std::uint16_t x, std::uint16_t y) : S2CEntitySpawn()
        {
            this->entityId = entityId;
            this->x = x;
            this->y = y;
        };

        void toBytes(sa::ByteBuffer &byteBuffer) override
        {
            byteBuffer.writeUInt(entityId);
            byteBuffer.writeUShort(x);
            byteBuffer.writeUShort(y);
        }

        void fromBytes(sa::ByteBuffer &byteBuffer) override
        {
            entityId = byteBuffer.readUInt();
            x = byteBuffer.readUShort();
            y = byteBuffer.readUShort();
        }
    };
} // namespace rtype::network::packet

#endif // R_TYPE_S2CENTITYSPAWN_HPP
