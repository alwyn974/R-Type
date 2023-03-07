/*
** EPITECH PROJECT, 2023
** S2CPlayerShootBullet.hpp
** File description:
** S2CPlayerShootBullet.hpp
*/

#ifndef R_TYPE_S2CPLAYERSHOOTBULLET_HPP
#define R_TYPE_S2CPLAYERSHOOTBULLET_HPP

#include "S2CPlayerChargingBullet.hpp"

namespace rtype::network::packet {
    class S2CPlayerShootBullet : public S2CPlayerChargingBullet {
    public:
        S2CPlayerShootBullet() : S2CPlayerChargingBullet() {}
        S2CPlayerShootBullet(std::uint32_t entityId, std::uint32_t playerId, float x, float y) : S2CPlayerChargingBullet(entityId, playerId, x, y) {}

        void toBytes(sa::ByteBuffer &byteBuffer) override
        {
            S2CPlayerChargingBullet::toBytes(byteBuffer);
        }

        void fromBytes(sa::ByteBuffer &byteBuffer) override
        {
            S2CPlayerChargingBullet::fromBytes(byteBuffer);
        }
    };
}

#endif //R_TYPE_S2CPLAYERSHOOTBULLET_HPP
