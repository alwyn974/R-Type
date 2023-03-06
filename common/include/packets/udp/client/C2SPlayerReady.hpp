/*
** EPITECH PROJECT, 2023
** C2SPlayerReady.hpp
** File description:
** C2SPlayerReady.hpp
*/

#ifndef R_TYPE_C2SPLAYERREADY_HPP
#define R_TYPE_C2SPLAYERREADY_HPP

#include <saturnity/Saturnity.hpp>

namespace rtype::network::packet {
    class C2SPlayerReady : public sa::AbstractPacket {
    public:
        bool ready = true;

        C2SPlayerReady() : sa::AbstractPacket(sa::AbstractPacket::EnumPacketType::UDP) {}

        void toBytes(sa::ByteBuffer &byteBuffer) override {
            byteBuffer.writeBoolean(ready);
        }

        void fromBytes(sa::ByteBuffer &byteBuffer) override {
            ready = byteBuffer.readBoolean();
        }
    };
}
#endif //R_TYPE_C2SPLAYERREADY_HPP
