/*
** EPITECH PROJECT, 2023
** C2SClientDisconnect.hpp
** File description:
** C2SClientDisconnect.hpp
*/

#ifndef R_TYPE_S2CCLIENTDISCONNECTED_HPP
#define R_TYPE_S2CCLIENTDISCONNECTED_HPP

#include <saturnity/Saturnity.hpp>
#include "external/uuidv4/uuidv4.hpp"

namespace rtype::network::packet {
    class C2SClientDisconnecting : public sa::AbstractPacket {
    public:
        C2SClientDisconnecting() : sa::AbstractPacket(sa::AbstractPacket::EnumPacketType::TCP) {};

        void toBytes(sa::ByteBuffer &byteBuffer) override {}

        void fromBytes(sa::ByteBuffer &byteBuffer) override {}
    };
}

#endif //R_TYPE_S2CCLIENTDISCONNECTED_HPP
