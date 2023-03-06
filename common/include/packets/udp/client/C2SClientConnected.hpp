/*
** EPITECH PROJECT, 2023
** C2SClientConnected.hpp
** File description:
** C2SClientConnected.hpp
*/

#ifndef R_TYPE_C2SCLIENTCONNECTED_HPP
#define R_TYPE_C2SCLIENTCONNECTED_HPP

#include <saturnity/Saturnity.hpp>

namespace rtype::network::packet {
    class C2SClientConnected : public sa::AbstractPacket {
    public:
        std::uint32_t uid;

        C2SClientConnected() : sa::AbstractPacket(sa::AbstractPacket::EnumPacketType::UDP) {};

        explicit C2SClientConnected(std::uint32_t uid) : C2SClientConnected()
        {
            this->uid = uid;
        };

        void toBytes(sa::ByteBuffer &byteBuffer) override
        {
            byteBuffer.writeUInt(uid);
        }

        void fromBytes(sa::ByteBuffer &byteBuffer) override
        {
            uid = byteBuffer.readUInt();
        }
    };
}

#endif //R_TYPE_C2SCLIENTCONNECTED_HPP
