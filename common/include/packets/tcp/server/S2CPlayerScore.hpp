/*
** EPITECH PROJECT, 2023
** S2CPlayerScore.hpp
** File description:
** S2CPlayerScore.hpp
*/

#pragma once

#include <saturnity/Saturnity.hpp>

namespace rtype::network::packet {
    class S2CPlayerScore : public sa::AbstractPacket {
    public:
        std::uint32_t uid;
        int score;
        bool win;

        explicit S2CPlayerScore(std::uint32_t uid, int score, bool win) : sa::AbstractPacket(sa::AbstractPacket::UDP)
        {
            this->uid = uid;
            this->score = score;
            this->win = win;
        }

        S2CPlayerScore() : sa::AbstractPacket(sa::AbstractPacket::UDP)
        {
        }

        void toBytes(sa::ByteBuffer &byteBuffer) override
        {
            byteBuffer.writeUInt(uid);
            byteBuffer.writeInt(score);
            byteBuffer.writeBoolean(win);
        }

        void fromBytes(sa::ByteBuffer &byteBuffer) override
        {
            uid = byteBuffer.readUInt();
            score = byteBuffer.readInt();
            win = byteBuffer.readBoolean();
        }
    };
}