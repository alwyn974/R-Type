//TODO add header

#include <saturnity/Saturnity.hpp>
#include "external/uuidv4/uuidv4.hpp"

class ScorePacket : public sa::AbstractPacket {
public:
    UUIDv4::UUID uuid;
    int score;
    bool win;

    explicit ScorePacket(UUIDv4::UUID uuid, int score, bool win) : sa::AbstractPacket(sa::AbstractPacket::UDP) {
        this->uuid = uuid;
        this->score = score;
        this->win = win;
    }
    ScorePacket() : sa::AbstractPacket(sa::AbstractPacket::UDP) {
    }

    void toBytes(sa::ByteBuffer &byteBuffer) override {
        byteBuffer.writeString(uuid.bytes());
        byteBuffer.writeInt(score);
        byteBuffer.writeInt(win);
    }

    void fromBytes(sa::ByteBuffer &byteBuffer) override {
        uuid = UUIDv4::UUID(byteBuffer.readString());
        score = byteBuffer.readInt();
        win = byteBuffer.readInt();
    }
};
