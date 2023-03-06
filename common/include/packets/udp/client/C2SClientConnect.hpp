/*
** EPITECH PROJECT, 2023
** C2SClientConnected.hpp
** File description:
** C2SClientConnected.hpp
*/

#ifndef R_TYPE_C2SCLIENTCONNECT_HPP
#define R_TYPE_C2SCLIENTCONNECT_HPP

#include <saturnity/Saturnity.hpp>

namespace rtype::network::packet {
    class C2SClientConnect : public sa::AbstractPacket {
    public:
        std::uint32_t uid;
        std::string name;

        C2SClientConnect() : sa::AbstractPacket(sa::AbstractPacket::EnumPacketType::UDP) {};

        explicit C2SClientConnect(std::uint32_t uid, const std::string &name) : C2SClientConnect()
        {
            this->uid = uid;
            this->name = name;
        };

        void toBytes(sa::ByteBuffer &byteBuffer) override
        {
            byteBuffer.writeUInt(uid);
            byteBuffer.writeString(name);
        }

        void fromBytes(sa::ByteBuffer &byteBuffer) override
        {
            uid = byteBuffer.readUInt();
            name = byteBuffer.readString();
        }
    };
}

#endif //R_TYPE_C2SCLIENTCONNECT_HPP
