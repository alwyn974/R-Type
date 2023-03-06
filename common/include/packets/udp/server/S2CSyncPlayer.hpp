/*
** EPITECH PROJECT, 2023
** S2CSyncPlayer.hpp
** File description:
** S2CSyncPlayer.hpp
*/

#ifndef R_TYPE_S2CSYNCPLAYER_HPP
#define R_TYPE_S2CSYNCPLAYER_HPP

#include <saturnity/Saturnity.hpp>

namespace rtype::network::packet {
    class S2CSyncPlayer : public sa::AbstractPacket {
    public:
        std::uint32_t entityId = 0;
        std::uint16_t x = 0, y = 0;

        S2CSyncPlayer() : sa::AbstractPacket(sa::AbstractPacket::EnumPacketType::UDP) {};
        explicit S2CSyncPlayer(std::uint32_t entityId, std::uint16_t x, std::uint16_t y) : S2CSyncPlayer()
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
}

#endif //R_TYPE_S2CSYNCPLAYER_HPP
