/*
** EPITECH PROJECT, 2023
** Components.hpp
** File description:
** Components.hpp
*/

#ifndef URANUS_COMPONENTS_HPP
#define URANUS_COMPONENTS_HPP

#include "uranus/Core.hpp"
#include "uranus/engine/components/Clock.hpp"
#include "uranus/engine/components/Event.hpp"
#include "uranus/engine/components/Sprite.hpp"
#include "uranus/engine/manager/Manager.hpp"
#include <bitset>

/**
 * @brief Namespace containing all the base components
 */
namespace uranus::ecs::component {

    struct NetworkId {
        std::uint32_t uniqueId;
    };

    struct Name {
        std::string uniqueName;
    };

    struct Position {
        float x;
        float y;
    };

    struct Velocity {
        float x;
        float y;
    };

    struct Drawable {
        size_t zIndex = 0;
        bool visible = true;
    protected:
        explicit Drawable(size_t zIndex, bool visible) : zIndex(zIndex), visible(visible) {};
    };

    struct Sprite : public Drawable {
        std::shared_ptr<engine::Sprite> sprite;
        explicit Sprite(const std::shared_ptr<engine::Sprite> &sprite, size_t zIndex = 0, bool visible = true) : Drawable(zIndex, visible), sprite(sprite) {};
    };

    struct Shape : public Drawable {
        std::shared_ptr<sf::Shape> shape;
        explicit Shape(const std::shared_ptr<sf::Shape> &shape, size_t zIndex = 0, bool visible = true) : Drawable(zIndex, visible), shape(shape) {};
    };

    struct Collisionable {
        float x;
        float y;
        float width;
        float height;
        std::bitset<LAYER_MASK_SIZE> layer;
        std::bitset<LAYER_MASK_SIZE> mask;
        std::function<void(const size_t, const size_t)> callback;
    };

    struct InputKeyboard {
        std::function<void(const size_t, const engine::Event)> callback;
    };

    struct InputMouse {
        std::function<void(const size_t, const engine::Event)> callback;
    };

    struct Loop {
        std::function<void(const size_t, float delta)> update;
    };

    struct FrameData {
        float frameTime;
        int frame;
    };

    struct AnimationData {
        std::string name;
        bool loop;
        float length;
        engine::Clock clock;
        bool isPlaying;
        std::vector<component::FrameData> frames;
    };

    struct Animation {
        int hFrame;
        int vFrame;
        std::function<void(const size_t entity, const std::string &animationName)> callback;
        std::vector<component::AnimationData> animations;
    };

    struct Dead {
        bool isDead = true;
    };

} // namespace uranus::ecs::component

void deletePosition(size_t entity);
void deleteVelocity(size_t entity);
void deleteDrawable(size_t entity);
void deleteInputKeyboard(size_t entity);
void deleteInputMouse(size_t entity);
void deleteSpriteComponent(size_t entity);
void deleteCollisionable(size_t entity);
void deleteLoopComponent(size_t entity);
void deleteAnimationComponent(size_t entity);
void deleteNameComponent(size_t entity);
void deleteShapeComponent(size_t entity);
void deleteNetworkIdComponent(size_t entity);
void deleteDeadComponent(size_t entity);

#endif // URANUS_COMPONENTS_HPP
