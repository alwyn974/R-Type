/*
** EPITECH PROJECT, 2023
** C2SPlayerShoot.hpp
** File description:
** C2SPlayerShoot.hpp
*/

#ifndef R_TYPE_C2SPLAYERSHOOT_HPP
#define R_TYPE_C2SPLAYERSHOOT_HPP

#include <saturnity/Saturnity.hpp>

namespace rtype::network::packet {
    class C2SPlayerShoot : public sa::AbstractPacket {
    public:
        int x = 0, y = 0;

        C2SPlayerShoot() : sa::AbstractPacket(sa::AbstractPacket::EnumPacketType::UDP) {};

        void toBytes(sa::ByteBuffer &byteBuffer) override {
            byteBuffer.writeInt(x);
            byteBuffer.writeInt(y);
        }

        void fromBytes(sa::ByteBuffer &byteBuffer) override {
            x = byteBuffer.readInt();
            y = byteBuffer.readInt();
        }
    };
} // namespace rtype::network::packet

#endif // R_TYPE_C2SPLAYERSHOOT_HPP
