//TODO add header

#include <saturnity/Saturnity.hpp>
#include "external/uuidv4/uuidv4.hpp"
#include "C2SkillEntity.hpp"

class KillEntityPacket : public C2SkillEntity {
public:

    explicit KillEntityPacket(int id, int entity_id) : C2SkillEntity(entity_id) {}
    KillEntityPacket() : C2SkillEntity() {}

    void toBytes(sa::ByteBuffer &byteBuffer) override {
        C2SkillEntity::toBytes(byteBuffer);
    }

    void fromBytes(sa::ByteBuffer &byteBuffer) override {
        C2SkillEntity::fromBytes(byteBuffer);
    }
};