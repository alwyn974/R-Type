/*
** EPITECH PROJECT, 2023
** C2SPlayerHandshake.hpp
** File description:
** C2SPlayerHandshake.hpp
*/

#ifndef R_TYPE_C2SPLAYERHANDSHAKE_HPP
#define R_TYPE_C2SPLAYERHANDSHAKE_HPP

#include <saturnity/Saturnity.hpp>

namespace rtype::network::packet {
    class C2SPlayerHandshake : public sa::AbstractPacket {
    public:
        std::string name;

        C2SPlayerHandshake() : sa::AbstractPacket(sa::AbstractPacket::EnumPacketType::TCP) {};

        explicit C2SPlayerHandshake(const std::string &name) : C2SPlayerHandshake() { this->name = name; }

        void toBytes(sa::ByteBuffer &byteBuffer) override { byteBuffer.writeString(name); }

        void fromBytes(sa::ByteBuffer &byteBuffer) override { name = byteBuffer.readString(); }
    };
} // namespace rtype::network::packet

#endif // R_TYPE_C2SPLAYERHANDSHAKE_HPP
