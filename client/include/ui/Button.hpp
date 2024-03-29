/*
** EPITECH PROJECT, 2023
** Button.hpp
** File description:
** Button.hpp
*/

#ifndef URANUS_BUTTON_HPP
#define URANUS_BUTTON_HPP

#include "uranus/engine/Engine.hpp"

namespace ui {

    class Button : public engine::Base {
    public:
        Button(const std::string &uniqueName, uranus::ecs::component::Position pos, std::shared_ptr<engine::Texture> &texture,
               const std::function<void()> &callbackPressed, size_t zIndex = 0, bool visible = true);

        void loop(size_t entity, float delta);

        void handleKeyboard(size_t entity, engine::Event event);

    private:
        std::function<void()> _callbackPressed;
        engine::Clock _clockPressed;
        bool _hover;
        bool _pressed;
    };

} // namespace ui

#endif // URANUS_BUTTON_HPP
