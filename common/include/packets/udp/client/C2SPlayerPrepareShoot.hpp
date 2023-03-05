/*
** EPITECH PROJECT, 2023
** C2SPrepareShoot.hpp
** File description:
** C2SPrepareShoot.hpp
*/

#ifndef R_TYPE_C2SPREPARESHOOT_HPP
#define R_TYPE_C2SPREPARESHOOT_HPP

#include <saturnity/Saturnity.hpp>

namespace rtype::network::packet {
    struct C2SPrepareShoot : public sa::AbstractPacket {
        C2SPrepareShoot() : sa::AbstractPacket(sa::AbstractPacket::EnumPacketType::TCP) {};

        void toBytes(sa::ByteBuffer &byteBuffer) override
        {
        }

        void fromBytes(sa::ByteBuffer &byteBuffer) override
        {
        }
    };
}

#endif //R_TYPE_C2SPREPARESHOOT_HPP
