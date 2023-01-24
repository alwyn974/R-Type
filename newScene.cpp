/*
** EPITECH PROJECT, 2023
** newScene.cpp
** File description:
** newScene.cpp
*/

#include "include/newScene.hpp"
#include "include/entityManager.hpp"

void NewScene::init()
{
    auto &manager = EntityManager::getInstance();

    position2D position{200, 200};

    position2D pos{0, 0};

    int id = manager->new_entity();
    manager->add_sprite(id);
    manager->set_sprite(id, "assets/mario.png");
    manager->add_position(id);
    manager->set_position(id, position);

    manager->add_box(id);
    box2D box{(vector2D){35, 75}, 0, 0, 55, 105};
    manager->set_box(id, box);
    float gravity_player = 6.0f;
    manager->add_gravity(id);
    manager->set_gravity(id, gravity_player);

    manager->add_input_list(id);
    manager->set_input(id, sf::Keyboard::Right);
    manager->set_input(id, sf::Keyboard::Left);
    manager->set_input(id, sf::Keyboard::Up);
    manager->set_input(id, sf::Keyboard::Down);

    manager->add_animation(id);
    manager->set_animation(id, 13, 2);
    manager->add_new_animation_to_list(id, "idle", true, 0.1f);
    manager->insert_animation_frame(id, "idle", 0.0, 0);

    manager->add_new_animation_to_list(id, "run", true, 0.4f);
    manager->insert_animation_frame(id, "run", 0.0, 1);
    manager->insert_animation_frame(id, "run", 0.1, 2);
    manager->insert_animation_frame(id, "run", 0.2, 3);
    manager->insert_animation_frame(id, "run", 0.3, 4);

    manager->add_new_animation_to_list(id, "jump", false, 0.2f);
    manager->insert_animation_frame(id, "jump", 0.0, 2);

    pos.x = 0;
    pos.y = 400;
    int floor = manager->new_entity();
    manager->add_sprite(floor);
    manager->set_sprite(floor, "assets/icon.png");
    manager->add_position(floor);
    manager->set_position(floor, pos);
    manager->add_box(floor);
    box2D box_3{(vector2D){0, 0}, pos.x, pos.y, 64, 64};
    manager->set_box(floor, box_3);
    pos.x = 64;
    for (int i = 0; i < 10; i++) {
        id = manager->new_entity();
        manager->add_sprite_copy(id, floor);
        manager->add_position(id);
        manager->add_box(id);
//        manager->add_gravity(id);
        manager->set_position(id, pos);
        box2D box_2{(vector2D){0, 0}, pos.x, pos.y, 64, 64};
        manager->set_box(id, box_2);
        pos.x += 64;
        if (pos.x > 800) {
            pos.x = 0;
            pos.y += 64;
        }
        if (pos.y > 600)
            pos.y = 0;
    }

    pos.x = 300;
    pos.y = 220;
    for (int i = 0; i < 1; i++) {
        id = manager->new_entity();
        manager->add_sprite_copy(id, floor);
        manager->add_position(id);
        manager->add_box(id);
        //        manager->add_gravity(id);
        manager->set_position(id, pos);
        box2D box_2{(vector2D){0, 0}, pos.x, pos.y, 64, 64};
        manager->set_box(id, box_2);
        pos.x += 64;
        if (pos.x > 800) {
            pos.x = 0;
            pos.y += 64;
        }
        if (pos.y > 600)
            pos.y = 0;
    }

    this->view.setSize(800, 600);
    this->view.setViewport((sf::FloatRect){1, 1, 1, 1});
}



void NewScene::update()
{
    auto &manager = EntityManager::getInstance();

    position2D position{manager->get_position(0)};

    if (manager->is_key_pressed(0, sf::Keyboard::Key::Right)) {
        manager->play_animation(0, "run");
        position.x += 5;
    }
    else if (manager->is_key_pressed(0, sf::Keyboard::Key::Left)) {
        manager->play_animation(0, "run");
        position.x -= 5;
    }
    else {
        manager->play_animation(0, "idle");
    }

    if (manager->is_key_just_pressed(0, sf::Keyboard::Key::Up)) {
        manager->play_animation(0, "jump");
        position.y -= 225;
    }

    box2D box = manager->_boxes.at(manager->_entities.at(0).get_id_box());
    box.x = position.x + box.offset.x;
    box.y = position.y + box.offset.y;
    manager->move_and_collide(0, box);
}


