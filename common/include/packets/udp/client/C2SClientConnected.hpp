/*
** EPITECH PROJECT, 2023
** C2SClientConnected.hpp
** File description:
** C2SClientConnected.hpp
*/

#ifndef R_TYPE_C2SCLIENTCONNECTED_HPP
#define R_TYPE_C2SCLIENTCONNECTED_HPP

#include <saturnity/Saturnity.hpp>
#include "external/uuidv4/uuidv4.hpp"

namespace rtype::network::packet {
    class C2SClientConnected : public sa::AbstractPacket {
    public:
        UUIDv4::UUID uuid;

        C2SClientConnected() : sa::AbstractPacket(sa::AbstractPacket::EnumPacketType::UDP) {};

        explicit C2SClientConnected(const UUIDv4::UUID &uuid) : C2SClientConnected()
        {
            this->uuid = uuid;
        };

        void toBytes(sa::ByteBuffer &byteBuffer) override
        {
            byteBuffer.writeString(uuid.bytes());
        }

        void fromBytes(sa::ByteBuffer &byteBuffer) override
        {
            uuid = UUIDv4::UUID(byteBuffer.readString());
        }
    };
}

#endif //R_TYPE_C2SCLIENTCONNECTED_HPP
