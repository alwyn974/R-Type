/*
** EPITECH PROJECT, 2023
** entity.cpp
** File description:
** entity.cpp
*/

#include "include/entity.hpp"

Entity::Entity(const int &id)
{
    this->_id = id;
    this->_id_position = -1;
    this->_id_rotation = -1;
    this->_id_scale = -1;
    this->_id_scale = -1;
    this->_id_sprite = -1;
    this->_id_input_list = -1;
    this->_id_box = -1;
    this->_id_gravity = -1;
    this->_id_animation = -1;
}

const int &Entity::get_id() const
{
    return this->_id;
}

int Entity::get_id_position() const
{
    return _id_position;
}

void Entity::set_id_position(const int &id_position)
{
    this->_id_position = id_position;
}

int Entity::get_id_rotation() const
{
    return _id_rotation;
}

void Entity::set_id_rotation(const int &id_rotation)
{
    this->_id_rotation = id_rotation;
}

int Entity::get_id_scale() const
{
    return _id_scale;
}

void Entity::set_id_scale(const int &id_scale)
{
    this->_id_scale = id_scale;
}

int Entity::get_id_sprite() const
{
    return _id_sprite;
}

void Entity::set_id_sprite(const int &id_sprite)
{
    this->_id_sprite = id_sprite;
}

int Entity::get_id_input_list() const
{
    return this->_id_input_list;
}

void Entity::set_id_input_list(int id_input_list)
{
    this->_id_input_list = id_input_list;
}

int Entity::get_id_box() const
{
    return this->_id_box;
}

void Entity::set_id_box(const int &id_box)
{
    this->_id_box = id_box;
}

int Entity::get_id_gravity() const
{
    return this->_id_gravity;
}

void Entity::set_id_gravity(const int &id_gravity)
{
    this->_id_gravity = id_gravity;
}

int Entity::get_id_animation() const
{
    return this->_id_animation;
}

void Entity::set_id_animation(const int &id_animation)
{
    this->_id_animation = id_animation;
}
