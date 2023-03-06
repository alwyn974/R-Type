/*
** EPITECH PROJECT, 2023
** S2CRemovePlayer.hpp
** File description:
** S2CRemovePlayer.hpp
*/

#ifndef R_TYPE_S2CSPAWNPLAYER_HPP
#define R_TYPE_S2CSPAWNPLAYER_HPP

#include <saturnity/Saturnity.hpp>
#include "S2CRemoveEntity.hpp"

namespace rtype::network::packet {
    class S2CRemovePlayer : public S2CRemoveEntity {
    public:
        S2CRemovePlayer() : S2CRemoveEntity() {}
        S2CRemovePlayer(std::uint32_t entityId) : S2CRemoveEntity(entityId) {};

        void toBytes(sa::ByteBuffer &byteBuffer) override
        {
            S2CRemoveEntity::toBytes(byteBuffer);
        }

        void fromBytes(sa::ByteBuffer &byteBuffer) override
        {
            S2CRemoveEntity::fromBytes(byteBuffer);
        }
    };
}

#endif //R_TYPE_S2CSPAWNPLAYER_HPP
