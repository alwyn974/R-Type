/*
** EPITECH PROJECT, 2023
** S2CRemoveEntity.hpp
** File description:
** S2CRemoveEntity.hpp
*/

#pragma once

#include <saturnity/Saturnity.hpp>

namespace rtype::network::packet {
    class S2CRemoveEntity : public sa::AbstractPacket {
    public:
        std::uint32_t entityId = 0;
        std::uint16_t x = 0, y = 0;

        S2CRemoveEntity() : sa::AbstractPacket(sa::AbstractPacket::EnumPacketType::UDP) {};
        explicit S2CRemoveEntity(std::uint32_t entityId) : S2CRemoveEntity()
        {
            this->entityId = entityId;
        };

        void toBytes(sa::ByteBuffer &byteBuffer) override
        {
            byteBuffer.writeUInt(entityId);
        }

        void fromBytes(sa::ByteBuffer &byteBuffer) override
        {
            entityId = byteBuffer.readUInt();
        }
    };
} // namespace rtype::network::packet
