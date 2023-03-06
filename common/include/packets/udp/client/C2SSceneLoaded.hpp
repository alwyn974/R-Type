/*
** EPITECH PROJECT, 2023
** C2SSceneLoaded.hpp
** File description:
** C2SSceneLoaded.hpp
*/

#ifndef R_TYPE_C2SSCENELOADED_HPP
#define R_TYPE_C2SSCENELOADED_HPP

#include <saturnity/Saturnity.hpp>

namespace rtype::network::packet {
    class C2SSceneLoaded : public sa::AbstractPacket {
    public:
        std::string sceneName;

        C2SSceneLoaded() : sa::AbstractPacket(sa::AbstractPacket::EnumPacketType::UDP) {}
        C2SSceneLoaded(const std::string &sceneName) : sa::AbstractPacket(sa::AbstractPacket::EnumPacketType::UDP)
        {
            this->sceneName = sceneName;
        }

        void toBytes(sa::ByteBuffer &byteBuffer) override
        {
            byteBuffer.writeString(sceneName);
        }

        void fromBytes(sa::ByteBuffer &byteBuffer) override
        {
            sceneName = byteBuffer.readString();
        }
    };
}

#endif //R_TYPE_C2SSCENELOADED_HPP
