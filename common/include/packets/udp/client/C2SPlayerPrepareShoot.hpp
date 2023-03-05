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
        C2SPrepareShoot() : sa::AbstractPacket(sa::AbstractPacket::EnumPacketType::UDP) {};

        void toBytes(sa::ByteBuffer &byteBuffer) override {}

        void fromBytes(sa::ByteBuffer &byteBuffer) override {}
    };
} // namespace rtype::network::packet

#endif // R_TYPE_C2SPLAYERPREPARESHOOT_HPP
