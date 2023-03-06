/*
** EPITECH PROJECT, 2023
** S2CPlayerMove.hpp
** File description:
** S2CPlayerMove.hpp
*/

#include <saturnity/Saturnity.hpp>
#include "S2CEntityMove.hpp"

namespace rtype::network::packet {
    class S2CPlayerMove : public S2CEntityMove {
    public:
        S2CPlayerMove() : S2CEntityMove()
        {
        }

        S2CPlayerMove(int id, int entity_id, int x, int y) : S2CEntityMove(id, entity_id, x, y)
        {
        }

        void toBytes(sa::ByteBuffer &byteBuffer) override
        {
            S2CEntityMove::toBytes(byteBuffer);
        }

        void fromBytes(sa::ByteBuffer &byteBuffer) override
        {
            S2CEntityMove::fromBytes(byteBuffer);
        }
    };
}