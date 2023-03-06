/*
** EPITECH PROJECT, 2023
** S2CGameStarted.hpp
** File description:
** S2CGameStarted.hpp
*/

#ifndef R_TYPE_S2CGAMESTARTED_HPP
#define R_TYPE_S2CGAMESTARTED_HPP

#include <saturnity/Saturnity.hpp>

namespace rtype::network::packet {
    class S2CGameStarted : public sa::AbstractPacket {
    public:
        bool started = true;

        S2CGameStarted() : sa::AbstractPacket(sa::AbstractPacket::EnumPacketType::UDP) {}

        void toBytes(sa::ByteBuffer &buffer) override
        {
            buffer.writeBoolean(started);
        }

        void fromBytes(sa::ByteBuffer &buffer) override
        {
            started = buffer.readBoolean();
        }

    };
}

#endif //R_TYPE_S2CGAMESTARTED_HPP
