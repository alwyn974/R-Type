/*
** EPITECH PROJECT, 2023
** RenderWindow.cpp
** File description:
** RenderWindow.cpp
*/

#include "uranus/engine/components/RenderWindow.hpp"

engine::RenderWindow::RenderWindow(sf::VideoMode mode, const std::string &title) : sf::RenderWindow(mode, title, sf::Style::Close) {}
