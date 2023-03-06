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
        C2SPlayerReady() : sa::AbstractPacket(sa::AbstractPacket::UDP) {}

        void toBytes(sa::ByteBuffer &byteBuffer) override {}

        void fromBytes(sa::ByteBuffer &byteBuffer) override {}
    };
}
#endif //R_TYPE_C2SPLAYERREADY_HPP
