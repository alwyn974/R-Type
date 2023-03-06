/*
** EPITECH PROJECT, 2023
** S2CEntityMove.hpp
** File description:
** S2CEntityMove.hpp
*/

#pragma once

#include <saturnity/Saturnity.hpp>

namespace rtype::network::packet {
    class S2CEntityMove : public sa::AbstractPacket {
    public:
        int id;
        int entity_id;
        int x;
        int y;

        explicit S2CEntityMove(int id, int entity_id, int x, int y) : sa::AbstractPacket(sa::AbstractPacket::UDP)
        {
            this->id = id;
            this->entity_id = entity_id;
            this->x = x;
            this->y = y;
        }

        S2CEntityMove() : sa::AbstractPacket(sa::AbstractPacket::UDP)
        {
        }

        void toBytes(sa::ByteBuffer &byteBuffer) override
        {
            byteBuffer.writeInt(this->id);
            byteBuffer.writeInt(this->entity_id);
            byteBuffer.writeInt(this->x);
            byteBuffer.writeInt(this->y);
        }

        void fromBytes(sa::ByteBuffer &byteBuffer) override
        {
            this->id = byteBuffer.readInt();
            this->entity_id = byteBuffer.readInt();
            this->x = byteBuffer.readInt();
            this->y = byteBuffer.readInt();
        }
    };
}