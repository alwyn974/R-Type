/*
** EPITECH PROJECT, 2023
** damaging.hpp
** File description:
** damaging.hpp
*/

#ifndef R_TYPE_DAMAGING_HPP
#define R_TYPE_DAMAGING_HPP

class Damaging {
public:
    virtual ~Damaging() = default;
    Damaging() = default;
    virtual void getDamage(size_t entity, int damage) = 0;
protected:
    int _health;
};

#endif //R_TYPE_DAMAGING_HPP