/*
** EPITECH PROJECT, 2023
** S2CPlayerChargingBullet.hpp
** File description:
** S2CPlayerChargingBullet.hpp
*/

#ifndef R_TYPE_S2CPLAYERCHARGINGBULLET_HPP
#define R_TYPE_S2CPLAYERCHARGINGBULLET_HPP

#include <saturnity/Saturnity.hpp>

namespace rtype::network::packet {
    class S2CPlayerChargingBullet : public sa::AbstractPacket {
    public:
        std::uint32_t entityId;
        std::uint32_t playerId;
        float x, y;

        S2CPlayerChargingBullet() : sa::AbstractPacket(sa::AbstractPacket::EnumPacketType::UDP) {
            this->entityId = 0;
            this->playerId = 0;
            this->x = 0;
            this->y = 0;
        };

        S2CPlayerChargingBullet(std::uint32_t entityId, std::uint32_t playerId, float x, float y) : sa::AbstractPacket(sa::AbstractPacket::EnumPacketType::UDP) {
            this->entityId = entityId;
            this->playerId = playerId;
            this->x = x;
            this->y = y;
        };

        void toBytes(sa::ByteBuffer &byteBuffer) override {
            byteBuffer.writeUInt(entityId);
            byteBuffer.writeUInt(playerId);
            byteBuffer.writeFloat(x);
            byteBuffer.writeFloat(y);
        }

        void fromBytes(sa::ByteBuffer &byteBuffer) override {
            entityId = byteBuffer.readUInt();
            playerId = byteBuffer.readUInt();
            x = byteBuffer.readFloat();
            y = byteBuffer.readFloat();
        }
    };
} // namespace rtype::network::packet

#endif //R_TYPE_S2CPLAYERCHARGINGBULLET_HPP
