
#ifndef R_TYPE_PARALLAXLAYER_HPP
#define R_TYPE_PARALLAXLAYER_HPP

#include "uranus/engine/Engine.hpp"

class ParallaxLayer : public engine::Base {
public:
    ParallaxLayer(std::string &name, std::shared_ptr<engine::Texture> &texture, float speed);

    void loop(size_t entity);

private:
    float _speed;
};

#endif //R_TYPE_PARALLAXLAYER_HPP
