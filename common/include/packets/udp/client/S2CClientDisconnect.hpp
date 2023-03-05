//TODO add header

#ifndef R_TYPE_C2SCLIENTDISCONNECTED_HPP
#define R_TYPE_C2SCLIENTDISCONNECTED_HPP

#include <saturnity/Saturnity.hpp>
#include "external/uuidv4/uuidv4.hpp"

namespace rtype::network::packet {
    class C2SClientDisconnected : public sa::AbstractPacket {
    public:
        UUIDv4::UUID uuid;

        C2SClientDisconnected() : sa::AbstractPacket(sa::AbstractPacket::EnumPacketType::UDP) {};

        explicit C2SClientDisconnected(const UUIDv4::UUID &uuid) : C2SClientDisconnected()
        {
            this->uuid = uuid;
        };

        void toBytes(sa::ByteBuffer &byteBuffer) override
        {
            byteBuffer.writeString(uuid.bytes());
        }

        void fromBytes(sa::ByteBuffer &byteBuffer) override
        {
            uuid = UUIDv4::UUID(byteBuffer.readString());
        }
    };
}

#endif //R_TYPE_C2SCLIENTDISCONNECTED_HPP
