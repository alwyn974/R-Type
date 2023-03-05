/*
** EPITECH PROJECT, 2023
** S2CPlayerAuthentified.hpp
** File description:
** S2CPlayerAuthentified.hpp
*/

#ifndef R_TYPE_S2CPLAYERAUTHENTIFIED_HPP
#define R_TYPE_S2CPLAYERAUTHENTIFIED_HPP

#include <saturnity/Saturnity.hpp>
#include "external/uuidv4/uuidv4.hpp"

namespace rtype::network::packet {
    class S2CPlayerAuthentified : public sa::AbstractPacket {
    public:
        std::string name;
        UUIDv4::UUID uuid;

        S2CPlayerAuthentified() : sa::AbstractPacket(sa::AbstractPacket::EnumPacketType::TCP) {};

        explicit S2CPlayerAuthentified(const std::string &name, const UUIDv4::UUID &uuid) : S2CPlayerAuthentified()
        {
            this->name = name;
            this->uuid = uuid;
        };

        void toBytes(sa::ByteBuffer &byteBuffer) override
        {
            byteBuffer.writeString(name);
            byteBuffer.writeString(uuid.bytes());
        }

        void fromBytes(sa::ByteBuffer &byteBuffer) override
        {
            name = byteBuffer.readString();
            uuid = UUIDv4::UUID(byteBuffer.readString());
        }
    };
}
#endif //R_TYPE_S2CPLAYERAUTHENTIFIED_HPP
