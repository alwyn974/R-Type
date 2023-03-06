/*
** EPITECH PROJECT, 2023
** S2CPlayerAuthentified.hpp
** File description:
** S2CPlayerAuthentified.hpp
*/

#ifndef R_TYPE_S2CPLAYERAUTHENTIFIED_HPP
#define R_TYPE_S2CPLAYERAUTHENTIFIED_HPP

#include <saturnity/Saturnity.hpp>

namespace rtype::network::packet {
    class S2CPlayerAuthentified : public sa::AbstractPacket {
    public:
        std::string name;
        std::uint32_t uid;

        S2CPlayerAuthentified() : sa::AbstractPacket(sa::AbstractPacket::EnumPacketType::TCP) {};

        explicit S2CPlayerAuthentified(const std::string &name, std::uint32_t uid) : S2CPlayerAuthentified()
        {
            this->name = name;
            this->uid = uid;
        };

        void toBytes(sa::ByteBuffer &byteBuffer) override
        {
            byteBuffer.writeString(name);
            byteBuffer.writeUInt(uid);
        }

        void fromBytes(sa::ByteBuffer &byteBuffer) override
        {
            name = byteBuffer.readString();
            uid = byteBuffer.readUInt();
        }
    };
}
#endif //R_TYPE_S2CPLAYERAUTHENTIFIED_HPP
