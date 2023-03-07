/*
** EPITECH PROJECT, 2023
** C2SPrepareShoot.hpp
** File description:
** C2SPrepareShoot.hpp
*/

#ifndef R_TYPE_C2SPLAYERPREPARESHOOT_HPP
#define R_TYPE_C2SPLAYERPREPARESHOOT_HPP

#include <saturnity/Saturnity.hpp>

namespace rtype::network::packet {
    class C2SPrepareShoot : public sa::AbstractPacket {
    public:
        float x, y;

        C2SPrepareShoot() : sa::AbstractPacket(sa::AbstractPacket::EnumPacketType::UDP) {
            this->x = 0;
            this->y = 0;
        };

        C2SPrepareShoot(float x, float y) : sa::AbstractPacket(sa::AbstractPacket::EnumPacketType::UDP) {
            this->x = x;
            this->y = y;
        };

        void toBytes(sa::ByteBuffer &byteBuffer) override {
            byteBuffer.writeFloat(x);
            byteBuffer.writeFloat(y);
        }

        void fromBytes(sa::ByteBuffer &byteBuffer) override {
            x = byteBuffer.readFloat();
            y = byteBuffer.readFloat();
        }
    };
} // namespace rtype::network::packet

#endif // R_TYPE_C2SPLAYERPREPARESHOOT_HPP
