/*
** EPITECH PROJECT, 2023
** components.hpp
** File description:
** components.hpp
*/

#ifndef ECS_FRAUDER_ENTITYMANAGER_HPP
#define ECS_FRAUDER_ENTITYMANAGER_HPP

#include "entity.hpp"
#include "scene.hpp"

class EntityManager {
public:
    EntityManager() = default;

    ~EntityManager() = default;

    void update(sf::RenderWindow &window);

    void draw(sf::RenderWindow &window);

    bool move_and_collide(const int &id, const box2D &box);

    bool is_colliding(const int &id, const box2D &box_reference);

    void change_scene(Scene &scene);

    void clear();

    int new_entity();

    void add_position(const int &id);

    void add_rotation(const int &id);

    void add_scale(const int &id);

    void add_sprite(const int &id);

    void add_sprite_copy(const int &id, const int &id_to_copy);

    void add_input_list(const int &id);

    void add_box(const int &id);

    void add_gravity(const int &id);

    void add_animation(const int &id);

    void set_animation(const int &id, const int h_frame, const int v_frame);

    void set_box(const int &id, box2D &box);

    void set_gravity(const int &id, float &gravity_force);

    void set_input(const int &id, const sf::Keyboard::Key &keycode);

    void set_sprite(const int &id, const std::string &filename);

    void set_position(const int &id, position2D &position);

    position2D &get_position(const int &id);

    bool is_key_pressed(const int &id, const sf::Keyboard::Key &keycode);

    bool is_key_just_pressed(const int &id, const sf::Keyboard::Key &keycode);

    void add_new_animation_to_list(const int &id, const std::string &name, bool loop, float length);

    void insert_animation_frame(const int &id, const std::string &name, float frame_time, int frame);

    void play_animation(const int &id, const std::string &name);

    std::vector<Entity> _entities;
    std::vector<position2D> _positions;
    std::vector<rotation2D> _rotations;
    std::vector<scale2D> _scales;
    std::vector<sprite2D> _sprites;
    std::vector<input_list> _input_lists;
    std::vector<box2D> _boxes;
    std::vector<gravity> _gravities;
    std::vector<animation_list> _animations;

    static std::shared_ptr<EntityManager> &getInstance();

private:
    static std::shared_ptr<EntityManager> _instance;

    Scene *_scene;


};


#endif //ECS_FRAUDER_ENTITYMANAGER_HPP