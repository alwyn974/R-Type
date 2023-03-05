//TODO add header

#include <saturnity/Saturnity.hpp>
#include "external/uuidv4/uuidv4.hpp"
#include "S2CEntitymove.hpp"

class S2CPlayerMove : public S2CEntityMove {
public:
    S2CPlayerMove() : S2CEntityMove() {}
    S2CPlayerMove(int id, int entity_id, int x, int y) : S2CEntityMove(id, entity_id, x, y) {}

    void toBytes(sa::ByteBuffer &byteBuffer) override {
        S2CEntityMove::toBytes(byteBuffer);
    }

    void fromBytes(sa::ByteBuffer &byteBuffer) override {
        S2CEntityMove::fromBytes(byteBuffer);
    }
};