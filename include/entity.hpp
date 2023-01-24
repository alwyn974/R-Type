/*
** EPITECH PROJECT, 2023
** entity.hpp
** File description:
** entity.hpp
*/

#ifndef ECS_FRAUDER_ENTITY_HPP
#define ECS_FRAUDER_ENTITY_HPP

#include "basics.hpp"
#include <SFML/Graphics.hpp>

typedef struct {
    float x;
    float y;
} vector2D;

typedef vector2D position2D;

typedef struct {
    float degrees;
} rotation2D;

typedef struct {
    vector2D scale;
} scale2D;

typedef struct {
    sf::Texture texture;
    sf::Sprite sprite;
} sprite2D;

typedef struct {
    float frame_time;
    int frame;
} frame_data;

typedef struct {
    std::string name;
    bool loop;
    float length;
    bool is_playing;
    sf::Clock clock;
    std::vector<frame_data> frames;
} animation;

typedef struct {
    int h_frame;
    int v_frame;
    std::vector<animation> list;
} animation_list;

typedef struct {
    vector2D offset;
    float x;
    float y;
    float width;
    float height;
} box2D;

typedef struct {
    float force;
} gravity;

typedef struct {
    sf::Keyboard::Key key;
    bool flag;
    bool once;
} input;

typedef struct {
    std::vector<input> inputs;
} input_list;

class Entity {
public:
    explicit Entity(const int &id);

    ~Entity() = default;

    const int &get_id() const;

    int get_id_position() const;

    void set_id_position(const int &id_position);

    int get_id_rotation() const;

    void set_id_rotation(const int &id_rotation);

    int get_id_scale() const;

    void set_id_scale(const int &id_scale);

    int get_id_sprite() const;

    void set_id_sprite(const int &id_sprite);

    int get_id_input_list() const;

    void set_id_input_list(int id_input_list);

    int get_id_box() const;

    void set_id_box(const int &id_box);

    int get_id_gravity() const;

    void set_id_gravity(const int &id_gravity);

    int get_id_animation() const;

    void set_id_animation(const int &id_animation);

private:
    int _id;
    int _id_position;
    int _id_rotation;
    int _id_scale;
    int _id_sprite;
    int _id_input_list;
    int _id_box;
    int _id_gravity;
    int _id_animation;
};

#endif //ECS_FRAUDER_ENTITY_HPP
