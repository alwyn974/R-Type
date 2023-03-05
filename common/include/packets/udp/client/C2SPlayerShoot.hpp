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
    struct C2SPlayerShoot : public sa::AbstractPacket {
        C2SPlayerShoot() : sa::AbstractPacket(sa::AbstractPacket::EnumPacketType::UDP) {};

        void toBytes(sa::ByteBuffer &byteBuffer) override {}

        void fromBytes(sa::ByteBuffer &byteBuffer) override {}
    };
} // namespace rtype::network::packet

#endif // R_TYPE_C2SPLAYERSHOOT_HPP
