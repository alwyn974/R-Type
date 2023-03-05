/*
** EPITECH PROJECT, 2023
** InputText.hpp
** File description:
** InputText.hpp
*/

#ifndef R_TYPE_INPUTTEXT_HPP
#define R_TYPE_INPUTTEXT_HPP

#include "uranus/engine/Engine.hpp"
#include "uranus/engine/components/Text.hpp"

namespace ui {
    class InputText : public engine::Base {
    public:
        InputText(const std::string &uniqueName, uranus::ecs::component::Position pos,
                  const std::function<void()> &callbackPressed);

        void loop(size_t entity);

        void handleKeyboard(size_t entity, engine::Event event);

    private:
        bool _hover;
        bool _focused;
        sf::Font _font;
        engine::Text _text;
        std::function<void()> _callbackPressed;
    };
}

#endif //R_TYPE_INPUTTEXT_HPP
