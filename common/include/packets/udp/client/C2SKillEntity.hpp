/*
** EPITECH PROJECT, 2023
** C2SSkillEntity.hpp
** File description:
** C2SSkillEntity.hpp
*/

#pragma once

#include <saturnity/Saturnity.hpp>

namespace rtype::network::packet {
    class C2SKillEntity : public sa::AbstractPacket {
    public:
        int entityId;

        explicit C2SKillEntity(int entityId) : sa::AbstractPacket(sa::AbstractPacket::UDP)
        {
            this->entityId = entityId;
        }

        C2SKillEntity() : sa::AbstractPacket(sa::AbstractPacket::UDP)
        {
        }

        void toBytes(sa::ByteBuffer &byteBuffer) override
        {
            byteBuffer.writeInt(entityId);
        }

        void fromBytes(sa::ByteBuffer &byteBuffer) override
        {
            entityId = byteBuffer.readInt();
        }
    };
}