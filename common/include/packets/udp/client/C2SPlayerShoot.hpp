/*
** EPITECH PROJECT, 2023
** C2SPlayerShoot.hpp
** File description:
** C2SPlayerShoot.hpp
*/

#ifndef R_TYPE_C2SPLAYERSHOOT_HPP
#define R_TYPE_C2SPLAYERSHOOT_HPP

#include <saturnity/Saturnity.hpp>

namespace rtype::network::packet {
    class C2SPlayerShoot : public sa::AbstractPacket {
    public:
        std::uint32_t entityId;
        int x = 0, y = 0;

        C2SPlayerShoot() : sa::AbstractPacket(sa::AbstractPacket::EnumPacketType::UDP) {
            this->entityId = 0;
            this->x = 0;
            this->y = 0;
        };
        C2SPlayerShoot(std::uint32_t entityId, int x, int y) : C2SPlayerShoot() {
            this->entityId = entityId;
            this->x = x;
            this->y = y;
        }

        void toBytes(sa::ByteBuffer &byteBuffer) override {
            byteBuffer.writeUInt(entityId);
            byteBuffer.writeInt(x);
            byteBuffer.writeInt(y);
        }

        void fromBytes(sa::ByteBuffer &byteBuffer) override {
            entityId = byteBuffer.readUInt();
            x = byteBuffer.readInt();
            y = byteBuffer.readInt();
        }
    };
} // namespace rtype::network::packet

#endif // R_TYPE_C2SPLAYERSHOOT_HPP
