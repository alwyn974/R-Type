/*
** EPITECH PROJECT, 2023
** S2CConnected.hpp
** File description:
** S2CConnected.hpp
*/

#ifndef R_TYPE_S2CCLIENTCONNECTED_HPP
#define R_TYPE_S2CCLIENTCONNECTED_HPP

#include <saturnity/Saturnity.hpp>

namespace rtype::network::packet {
    /**
     * @brief Response to C2SClientConnect packet.
     */
    class S2CClientConnected : public sa::AbstractPacket {
    public:
        std::uint32_t uid;

        S2CClientConnected() : sa::AbstractPacket(sa::AbstractPacket::EnumPacketType::UDP) { this->uid = 0; };

        explicit S2CClientConnected(int uid) : S2CClientConnected() { this->uid = uid; }

        void toBytes(sa::ByteBuffer &byteBuffer) override {
            byteBuffer.writeUInt(uid);
        }

        void fromBytes(sa::ByteBuffer &byteBuffer) override {
            uid = byteBuffer.readUInt();
        }
    };
}

#endif //R_TYPE_S2CCLIENTCONNECTED_HPP
