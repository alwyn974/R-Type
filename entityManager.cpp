/*
** EPITECH PROJECT, 2023
** entityManager.cpp
** File description:
** entityManager.cpp
*/

#include "include/entityManager.hpp"

std::shared_ptr<EntityManager> EntityManager::_instance;

std::shared_ptr<EntityManager> &EntityManager::getInstance()
{
    if (!_instance)
        _instance = std::make_shared<EntityManager>();
    return _instance;
}

sf::IntRect get_animation_rect(int frame, int h_frame, int v_frame, sf::Vector2u size)
{

//    std::cout << "frame: " << frame << ", size: " << size.x << ", " <<size.y << std::endl;
    sf::Vector2i frame_size((int)size.x / h_frame, (int)size.y / v_frame);

    sf::Vector2i start{0, 0};
    for (int i = 0; i < frame; i++) {
        start.x += frame_size.x;
        if (start.x >= size.x) {
            start.x = 0;
            start.y += frame_size.y;
        }
    }
    sf::IntRect rect{start.x, start.y, frame_size.x, frame_size.y};
//    std::cout << "(" << rect.left << ", " << rect.top << ", " << rect.width << ", " << rect.height << ")" << std::endl;
    return rect;
}

void EntityManager::update(sf::RenderWindow &window)
{
    sf::Event event{};

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        for (input_list &list: this->_input_lists) {
            for (input &input_new: list.inputs) {
//                std::cout << input_new.key << std::endl;
                if (input_new.key == event.key.code) {
                    if (event.type == sf::Event::KeyPressed) {
                        input_new.flag = true;
                        input_new.once = true;
                    }
                    else if (event.type == sf::Event::KeyReleased) {
                        input_new.flag = false;
                        input_new.once = false;
                    }
                }
            }
        }
    }

    //update gravity component
    for (Entity &entity: this->_entities) {
        if ((unsigned int)(entity.get_id_gravity()) <= this->_gravities.size()) {

            if ((unsigned int) (entity.get_id_box()) <= this->_boxes.size()) {
                box2D box = this->_boxes.at(entity.get_id_box());
                box.y += this->_gravities.at(entity.get_id_gravity()).force;

                if ((unsigned int) (entity.get_id_position()) <= this->_positions.size()) {
                    this->move_and_collide(entity.get_id(), box);
//                    std::cout << "ici ça move" << std::endl;
                }

            } else if ((unsigned int) (entity.get_id_position()) <= this->_positions.size()) {
                position2D position{this->get_position(entity.get_id())};
                box2D box{(vector2D){0, 0}, position.x, position.y, 0, 0};
                box.y += this->_gravities.at(entity.get_id_gravity()).force;
                this->move_and_collide(entity.get_id(), box);
            }
        }
    }

    //update animation component
    for (Entity &entity: this->_entities) {
        if ((unsigned int) (entity.get_id_animation()) <= this->_animations.size()) {

            animation_list &animation_list_new = this->_animations.at(entity.get_id_animation());
//            std::cout << "h_frame: " << animation_list_new.v_frame << ", v_frame: " << animation_list_new.v_frame << std::endl;
            for (animation &animation_new: animation_list_new.list) {
                if (animation_new.is_playing) {
//                    std::cout << animation_new.name << ", is_playing: " << animation_new.is_playing << std::endl;
                    sprite2D &sprite = this->_sprites.at(entity.get_id_sprite());
//                    std::cout << "time: " << animation_new.clock.getElapsedTime().asSeconds() << ", length: " << animation_new.length << std::endl;
                    if (animation_new.clock.getElapsedTime().asSeconds() >= animation_new.length) {
//                        std::cout << "loop: " << animation_new.loop << std::endl;
                        if (animation_new.loop) {
                            animation_new.clock.restart();
//                            std::cout << "restart" << std::endl;
//                            std::cout << "time: " << animation_new.clock.getElapsedTime().asSeconds() << ", length: " << animation_new.length << std::endl;
                        }
                        else
                            animation_new.is_playing = false;
                    } else {
                        for (frame_data &frame: animation_new.frames) {

                            if (animation_new.clock.getElapsedTime().asSeconds() >= frame.frame_time) {
//                                std::cout << "time: " << animation_new.clock.getElapsedTime().asSeconds() << ", length: " << animation_new.length << std::endl;
                                sf::IntRect rect = get_animation_rect(frame.frame,
                                                                      animation_list_new.h_frame,
                                                                      animation_list_new.v_frame,
                                                                      sprite.texture.getSize());
//                                std::cout << "(" << rect.left << ", " << rect.top << ", " << rect.width << ", " << rect.height << ")" << std::endl;
                                sprite.sprite.setTextureRect(rect);
                            }
                        }
                    }
                }
            }
        }
    }

    this->_scene->update();

    for (input_list &list: this->_input_lists) {
        for (input &input_new: list.inputs) {
            if (input_new.once)
                input_new.once = false;
        }
    }
}

bool EntityManager::move_and_collide(const int &id, const box2D &box)
{
    if (!this->is_colliding(id, box)) {
//        std::cout << "move" << std::endl;
        position2D position{box.x - box.offset.x, box.y - box.offset.y};
        this->set_position(id, position);
        return true;
    }
    return false;
}

bool EntityManager::is_colliding(const int &id, const box2D &box_reference)
{
    int index = 0;
    for (box2D &box: this->_boxes) {
        if (index != id and !(box.x >= box_reference.x + box_reference.width ||
                             box.x + box.width <= box_reference.x ||
                             box.y >= box_reference.y + box_reference.height ||
                             box.y + box.height <= box_reference.y))
            return true;
        index++;
    }
    return false;
}

void EntityManager::draw(sf::RenderWindow &window)
{
    window.clear();

    for (Entity &entity : this->_entities) {
        if ((unsigned int)(entity.get_id_sprite()) < this->_sprites.size()) {
            sprite2D &sprite = this->_sprites.at(entity.get_id_sprite());
            if ((unsigned int)(entity.get_id_position()) < this->_positions.size()) {
                position2D &position = this->get_position(entity.get_id());
                sprite.sprite.setPosition(position.x, position.y);
            }
//            std::cout << sprite.texture.getNativeHandle() << ", " << sprite.sprite.getTexture()->getNativeHandle() << std::endl;
//            if (entity.get_id_sprite() == 0)
            sprite.sprite.setTexture(sprite.texture);
            if (sprite.sprite.getTexture() == nullptr) {
                sprite.sprite.setTexture(sprite.texture);
                printf("hello\n");
            }
            window.draw(sprite.sprite);
//            printf("%p, %p, %d\n", &sprite.texture, sprite.sprite.getTexture(), entity.get_id_sprite());

        }
        if ((unsigned int)(entity.get_id_box()) < this->_boxes.size()) {
            box2D &box = this->_boxes.at(entity.get_id_box());
            sf::Vector2f size(box.width, box.height);
            sf::RectangleShape rect(size);
            rect.setFillColor(sf::Color::Transparent);
            rect.setOutlineColor(sf::Color::Red);
            rect.setOutlineThickness(1);
            rect.setPosition(box.x, box.y);
            window.draw(rect);
        }
    }

    window.display();
}

void EntityManager::change_scene(Scene &scene)
{
    this->_scene = &scene;
    this->_scene->init();
}

int EntityManager::new_entity()
{
//    std::cout << this->_sprites.size() << std::endl;
    static int id = 0;
    this->_entities.emplace_back(id);
    return id++;
}

void EntityManager::add_position(const int &id)
{
    Entity &entity = this->_entities.at(id);
    entity.set_id_position((int)this->_positions.size());
    position2D position{0, 0};
    this->_positions.push_back(position);
}

void EntityManager::add_rotation(const int &id)
{
    Entity &entity = this->_entities.at(id);
    entity.set_id_rotation((int)this->_rotations.size());
    rotation2D rotation{0};
    this->_rotations.push_back(rotation);
}

void EntityManager::add_scale(const int &id)
{
    Entity &entity = this->_entities.at(id);
    entity.set_id_scale((int)this->_scales.size());
    scale2D scale{1, 1};
    this->_scales.push_back(scale);
}

void EntityManager::add_sprite(const int &id)
{
    Entity &entity = this->_entities.at(id);
    entity.set_id_sprite((int)this->_sprites.size());
    this->_sprites.push_back({});
}

void EntityManager::add_sprite_copy(const int &id, const int &id_to_copy)
{
    Entity &entity = this->_entities.at(id);
    Entity &entity_to_copy = this->_entities.at(id_to_copy);
    entity.set_id_sprite(entity_to_copy.get_id_sprite());
}

void EntityManager::add_input_list(const int &id)
{
    Entity &entity = this->_entities.at(id);
    entity.set_id_input_list((int)this->_input_lists.size());
    input_list list;
    this->_input_lists.push_back(list);
}

void EntityManager::add_box(const int &id)
{
    Entity &entity = this->_entities.at(id);
    entity.set_id_box((int)this->_boxes.size());
    box2D box{0, 0, 0, 0};
    this->_boxes.push_back(box);
}

void EntityManager::add_gravity(const int &id)
{
    Entity &entity = this->_entities.at(id);
    entity.set_id_gravity((int)this->_gravities.size());
    gravity gravity_new{1};
    this->_gravities.push_back(gravity_new);
}

void EntityManager::add_animation(const int &id)
{
    Entity &entity = this->_entities.at(id);
    entity.set_id_animation((int)this->_animations.size());
    std::vector<animation> animation;
    animation_list animation_new{1, 1, animation};
    this->_animations.push_back(animation_new);
}

void EntityManager::set_box(const int &id, box2D &box)
{
    Entity &entity = this->_entities.at(id);
    this->_boxes.at((entity.get_id_box())) = box;
}

void EntityManager::set_sprite(const int &id, const std::string &filename)
{
    Entity &entity = this->_entities.at(id);
    int sprite_id = entity.get_id_sprite();
    sprite2D &sprite_new = this->_sprites.at(sprite_id);
    std::cout << "load: " << sprite_new.texture.loadFromFile(filename) << std::endl;
    sprite_new.sprite.setTexture(sprite_new.texture);
    printf("%p, %p, %d\n", &sprite_new.texture, sprite_new.sprite.getTexture(), entity.get_id_sprite());
}

void EntityManager::set_position(const int &id, position2D &position)
{
    Entity &entity = this->_entities.at(id);
    this->_positions.at(entity.get_id_position()) = position;
    if ((unsigned int)(entity.get_id_box()) <= this->_boxes.size()) {
        box2D &box = this->_boxes.at(entity.get_id_box());
        box.x = position.x + box.offset.x;
        box.y = position.y + box.offset.y;
    }
}

bool EntityManager::is_key_pressed(const int &id, const sf::Keyboard::Key &keycode)
{
    Entity &entity = this->_entities.at(id);
    input_list &list = this->_input_lists.at(entity.get_id_input_list());
    for (input &input_new: list.inputs)
        if (input_new.key == keycode)
            return input_new.flag;
    return false;
}

bool EntityManager::is_key_just_pressed(const int &id, const sf::Keyboard::Key &keycode)
{
    Entity &entity = this->_entities.at(id);
    input_list &list = this->_input_lists.at(entity.get_id_input_list());
    for (input &input_new: list.inputs) {
        if (input_new.key == keycode) {
            if (input_new.once == 1)
                return true;
            else
                return false;
        }
    }
    return false;
}

void EntityManager::set_input(const int &id, const sf::Keyboard::Key &keycode)
{
    Entity &entity = this->_entities.at(id);
    input_list &list = this->_input_lists.at(entity.get_id_input_list());
    input input_new{keycode, false};
    list.inputs.push_back(input_new);
}

position2D &EntityManager::get_position(const int &id)
{
    return this->_positions.at(id);
}

void EntityManager::set_gravity(const int &id, float &gravity_force)
{
    Entity &entity = this->_entities.at(id);
    this->_gravities.at(entity.get_id_gravity()).force = gravity_force;
}

void EntityManager::set_animation(const int &id, const int h_frame, const int v_frame)
{
    Entity &entity = this->_entities.at(id);
    animation_list &animation_list_new = this->_animations.at(entity.get_id_animation());
    animation_list_new.h_frame = h_frame;
    animation_list_new.v_frame = v_frame;
}

void EntityManager::add_new_animation_to_list(const int &id, const std::string &name, bool loop, float length)
{
    Entity &entity = this->_entities.at(id);
    sf::Clock clock;
    std::vector<frame_data> frame_list;
    animation animation_new{name, loop, length, false, clock, frame_list};
    this->_animations.at(entity.get_id_animation()).list.push_back(animation_new);
}

void EntityManager::insert_animation_frame(const int &id, const std::string &name, float frame_time, int frame)
{
    Entity &entity = this->_entities.at(id);
    frame_data frame_new{frame_time, frame};
    for (animation &animation_new: this->_animations.at(entity.get_id_animation()).list) {
        if (animation_new.name == name) {
            animation_new.frames.push_back(frame_new);
            break;
        }
    }
}

void EntityManager::play_animation(const int &id, const std::string &name)
{
    Entity &entity = this->_entities.at(id);
    for (animation &animation_new: this->_animations.at(entity.get_id_animation()).list) {

        if (animation_new.name == name) {
            animation_new.is_playing = true;
//            std::cout << animation_new.name << std::endl;
        }
        else
            animation_new.is_playing = false;
    }
}

void EntityManager::clear()
{
    this->_entities.clear();
    this->_positions.clear();
    this->_animations.clear();
    this->_boxes.clear();
    this->_input_lists.clear();
    this->_gravities.clear();
    this->_sprites.clear();
}

