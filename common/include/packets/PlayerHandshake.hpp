/*
** EPITECH PROJECT, 2023
** PlayerHandshake.hpp
** File description:
** PlayerHandshake.hpp
*/

#ifndef R_TYPE_PLAYERHANDSHAKE_HPP
#define R_TYPE_PLAYERHANDSHAKE_HPP

#include <saturnity/Saturnity.hpp>

namespace rtype::network::packet {
    struct PlayerHandshake : public sa::AbstractPacket {
        std::string name;

        PlayerHandshake() : sa::AbstractPacket(sa::AbstractPacket::EnumPacketType::TCP) {};

        explicit PlayerHandshake(const std::string &name) : sa::AbstractPacket(sa::AbstractPacket::EnumPacketType::TCP), name(name) {}

        void toBytes(sa::ByteBuffer &byteBuffer) override
        {
            byteBuffer.writeString(name);
        }

        void fromBytes(sa::ByteBuffer &byteBuffer) override
        {
            name = byteBuffer.readString();
        }
    };
}

#endif // R_TYPE_PLAYERHANDSHAKE_HPP