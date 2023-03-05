/*
** EPITECH PROJECT, 2023
** S2CPlayerScore.hpp
** File description:
** S2CPlayerScore.hpp
*/

#pragma once

#include <saturnity/Saturnity.hpp>
#include "external/uuidv4/uuidv4.hpp"

namespace rtype::network::packet {
    class S2CPlayerScore : public sa::AbstractPacket {
    public:
        UUIDv4::UUID uuid;
        int score;
        bool win;

        explicit S2CPlayerScore(UUIDv4::UUID uuid, int score, bool win) : sa::AbstractPacket(sa::AbstractPacket::UDP)
        {
            this->uuid = uuid;
            this->score = score;
            this->win = win;
        }

        S2CPlayerScore() : sa::AbstractPacket(sa::AbstractPacket::UDP)
        {
        }

        void toBytes(sa::ByteBuffer &byteBuffer) override
        {
            byteBuffer.writeString(uuid.bytes());
            byteBuffer.writeInt(score);
            byteBuffer.writeInt(win);
        }

        void fromBytes(sa::ByteBuffer &byteBuffer) override
        {
            uuid = UUIDv4::UUID(byteBuffer.readString());
            score = byteBuffer.readInt();
            win = byteBuffer.readInt();
        }
    };
}