//TODO add header

#include <saturnity/Saturnity.hpp>
#include "external/uuidv4/uuidv4.hpp"

class C2SkillEntity : public sa::AbstractPacket {
public:
    int entity_id;

    explicit C2SkillEntity(int entity_id) : sa::AbstractPacket(sa::AbstractPacket::UDP) {
        this->entity_id = entity_id;
    }

    C2SkillEntity() : sa::AbstractPacket(sa::AbstractPacket::UDP) {
    }

    void toBytes(sa::ByteBuffer &byteBuffer) override {
        byteBuffer.writeInt(entity_id);
    }

    void fromBytes(sa::ByteBuffer &byteBuffer) override {
        entity_id = byteBuffer.readInt();
    }
};