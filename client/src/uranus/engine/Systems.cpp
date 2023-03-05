//
// Created by nicol on 23/01/2023.
//

#include "uranus/engine/Systems.hpp"
#include "uranus/engine/components/Rect.hpp"

void engine::system::position()
{
    auto &r = engine::Manager::getRegistry();
    for (auto [idx, pos, vel] : uranus::ecs::View<uranus::ecs::component::Position, uranus::ecs::component::Velocity>(*r)) {
        pos.x += vel.x;
        pos.y += vel.y;
    }
}

void engine::system::draw()
{
    auto &window = engine::Manager::getWindow();
    auto &r = engine::Manager::getRegistry();
    for (auto [idx, pos, rectangle] : uranus::ecs::View<uranus::ecs::component::Position, uranus::ecs::component::RectangleShape>(*r)) {
        rectangle.shape->setPosition(pos.x, pos.y);
        window->draw(*rectangle.shape);
        //        spdlog::info("Drawing rectangle ({}) at ({}, {})", idx, pos.x, pos.y);
    }
    for (auto [idx, pos, drawable] : uranus::ecs::View<uranus::ecs::component::Position, uranus::ecs::component::Drawable>(*r)) {
        drawable.shape->setPosition(pos.x, pos.y);
        drawable.shape->setFillColor(drawable.color);
        window->draw(*drawable.shape);
        //        spdlog::info("Drawing drawable ({}) at ({}, {})", idx, pos.x, pos.y);
    }
    for (auto [idx, pos, sprite] : uranus::ecs::View<uranus::ecs::component::Position, uranus::ecs::component::Sprite>(*r)) {
        sprite.sprite->setPosition(pos.x, pos.y);
        window->draw(*sprite.sprite);
        //        spdlog::info("Drawing sprite ({}) at ({}, {})", idx, pos.x, pos.y);
    }
}

void engine::system::input(engine::Event event)
{
    auto &r = engine::Manager::getRegistry();
    for (auto [idx, inputKeyboard] : uranus::ecs::View<uranus::ecs::component::InputKeyboard>(*r))
        inputKeyboard.callback(idx, event);
    for (auto [idx, inputMouse] : uranus::ecs::View<uranus::ecs::component::InputMouse>(*r))
        inputMouse.callback(idx, event);
}

bool engine::system::isColliding(const sf::FloatRect &obj1, const sf::FloatRect &obj2)
{
    return obj1.left < obj2.left + obj2.width && obj1.left + obj1.width > obj2.left && obj1.top < obj2.top + obj2.height && obj1.top + obj1.height > obj2.top;
}

void engine::system::setLayer(size_t entity, const std::bitset<uranus::ecs::LAYER_MASK_SIZE> &layer)
{
    auto &r = engine::Manager::getRegistry();
    auto &collision = r->getComponent<uranus::ecs::component::Collisionable>(entity);
    collision->layer = layer;
}

void engine::system::setMask(size_t entity, const std::bitset<uranus::ecs::LAYER_MASK_SIZE> &mask)
{
    auto &r = engine::Manager::getRegistry();
    auto &collision = r->getComponent<uranus::ecs::component::Collisionable>(entity);
    collision->mask = mask;
}

//void engine::system::collision()
//{
//    auto &window = engine::Manager::getWindow();
//    auto &r = engine::Manager::getRegistry();
//    for (auto [entity1, pos1, collision1] : uranus::ecs::View<uranus::ecs::component::Position, uranus::ecs::component::Collisionable>(*r)) {
//        // start debug
//        sf::Vector2f size(collision1->width, collision1->height);
//        sf::RectangleShape rect(size);
//        rect.setFillColor(sf::Color::Transparent);
//        rect.setOutlineColor(sf::Color::White);
//        rect.setOutlineThickness(1);
//        rect.setPosition(pos1->x + collision1->x, pos1->y + collision1->y);
//        window->draw(rect);
//        // end debug
//
//        for (auto [entity2, pos2, collision2] : uranus::ecs::View<uranus::ecs::component::Position, uranus::ecs::component::Collisionable>(*r)) {
//            if (entity1 == entity2) continue;
//
//            for (unsigned long i = 0; i < collision1->mask.size(); i++) {
//                if (collision1->mask[i] && collision2->layer[i]) {
//                    const sf::FloatRect obj1 {collision1->x + pos1->x, collision1->y + pos1->y, collision1->width, collision1->height};
//                    const sf::FloatRect obj2 {collision2->x + pos2->x, collision2->y + pos2->y, collision2->width, collision2->height};
//                    if (isColliding(obj1, obj2)) collision1->callback(entity1, entity2);
//                    break;
//                }
//            }
//        }
//    }
//}

bool canCollide(const uranus::ecs::component::Collisionable& obj1, const uranus::ecs::component::Collisionable& obj2) {
    for (unsigned long i = 0; i < uranus::ecs::LAYER_MASK_SIZE; i++) {
        if (obj1.mask[i] && obj2.layer[i]) return true;
    }
    for (unsigned long i = 0; i < uranus::ecs::LAYER_MASK_SIZE; i++) {
        if (obj2.mask[i] && obj1.layer[i]) return true;
    }
    return false;
}

bool isColliding(const sf::FloatRect& obj1, const sf::FloatRect& obj2) {
    float dx = std::abs(obj1.left - obj2.left);
    float dy = std::abs(obj1.top - obj2.top);
    float w = (obj1.width + obj2.width) / 2.0f;
    float h = (obj1.height + obj2.height) / 2.0f;
    return dx < w && dy < h;
}

bool satCollision(const sf::FloatRect& obj1, const sf::FloatRect& obj2, const uranus::ecs::component::Position& pos1, const uranus::ecs::component::Position& pos2) {
    // Check x-axis overlap
    bool const x_overlap = isColliding(obj1, obj2);

    // Check y-axis overlap
    sf::FloatRect const rotated1 {pos1.x + obj1.top, pos1.y - obj1.left, obj1.height, obj1.width};
    sf::FloatRect const rotated2 {pos2.x + obj2.top, pos2.y - obj2.left, obj2.height, obj2.width};
    bool const y_overlap = isColliding(rotated1, rotated2);

    return x_overlap && y_overlap;
}


void engine::system::collision() {
    auto &r = engine::Manager::getRegistry();
    auto window = engine::Manager::getWindow();
    const int gridSize = 150; // size of grid cell
    std::unordered_map<int, std::vector<int>> grid; // hash table to store entities by grid cell

// populate the grid hash table with entities
    for (auto [entity, pos, collision] : uranus::ecs::View<uranus::ecs::component::Position, uranus::ecs::component::Collisionable>(*r)) {
        int const x = pos.x / gridSize;
        int const y = pos.y / gridSize;
        int const key = x * 1000 + y; // use x,y coordinates as hash key
        grid[key].push_back(entity);
    }

// loop over entities in each grid cell and check for collisions
    for (auto& [key, entities] : grid) {
        for (int i = 0; i < entities.size(); i++) {
            for (int j = i + 1; j < entities.size(); j++) {
                auto entity1 = entities[i];
                auto &pos1 = r->getComponent<uranus::ecs::component::Position>(entity1);
                auto &collision1 = r->getComponent<uranus::ecs::component::Collisionable>(entity1);
                if (r->getComponent<uranus::ecs::component::Dead>(entity1) != nullptr) return;
                auto entity2 = entities[j];
                if (entity1 == entity2) continue;
                if (r->getComponent<uranus::ecs::component::Dead>(entity2) != nullptr) return;
                auto &pos2 = r->getComponent<uranus::ecs::component::Position>(entity2);
                auto &collision2 = r->getComponent<uranus::ecs::component::Collisionable>(entity2);
                if (canCollide(*collision1, *collision2)) {
                    std::cout << "Checking collision between " << entity1 << " and " << entity2 << std::endl;
                    const sf::FloatRect obj1 {collision1->x + pos1->x, collision1->y + pos1->y, collision1->width, collision1->height};
                    const sf::FloatRect obj2 {collision2->x + pos2->x, collision2->y + pos2->y, collision2->width, collision2->height};
                    if (satCollision(obj1, obj2, *pos1, *pos2)) {
                        std::cout << "Collision between " << entity1 << " and " << entity2 << std::endl;
                        collision2->callback(entity1, entity2);
                    }
                }
            }
        }
    }
}

void engine::system::loop()
{
    auto &r = engine::Manager::getRegistry();
    for (auto [idx, loop] : uranus::ecs::View<uranus::ecs::component::Loop>(*r))
        loop.update(idx);
}

sf::IntRect get_animation_rect(int frame, int h_frame, int v_frame, sf::Vector2u size)
{
    sf::Vector2i frameSize(static_cast<int>(size.x) / h_frame, static_cast<int>(size.y) / v_frame);

    sf::Vector2i start {0, 0};
    for (int i = 0; i < frame; i++) {
        start.x += frameSize.x;
        if (start.x >= size.x) {
            start.x = 0;
            start.y += frameSize.y;
        }
    }
    sf::IntRect rect {start.x, start.y, frameSize.x, frameSize.y};
    return rect;
}

void engine::system::addNewAnimation(size_t entity, const std::string &name, bool loop, float length)
{
    engine::Clock clock;
    std::vector<uranus::ecs::component::FrameData> frameList;
    uranus::ecs::component::AnimationData animationData {name, loop, length, clock, false, frameList};
    auto &r = engine::Manager::getRegistry();
    auto &animation = r->getComponent<uranus::ecs::component::Animation>(entity);
    animation->animations.push_back(animationData);
}

void engine::system::insertAnimationFrame(size_t entity, const std::string &name, float frameTime, int frame)
{
    auto &r = engine::Manager::getRegistry();
    auto &animation = r->getComponent<uranus::ecs::component::Animation>(entity);
    uranus::ecs::component::FrameData frameData {frameTime, frame};
    for (uranus::ecs::component::AnimationData &animationData : animation->animations) {
        if (animationData.name == name) {
            animationData.frames.push_back(frameData);
            break;
        }
    }
}

void engine::system::playAnimation(size_t entity, const std::string &name)
{
    auto &r = engine::Manager::getRegistry();
    auto &animation = r->getComponent<uranus::ecs::component::Animation>(entity);

    for (uranus::ecs::component::AnimationData &animationData : animation->animations) {
        if (animationData.name == name) {
            animationData.isPlaying = true;
            auto &sprite = r->getComponent<uranus::ecs::component::Sprite>(entity);
            sprite->sprite->setTextureRect(
                get_animation_rect(animationData.frames.data()->frame, animation->hFrame, animation->vFrame, sprite->sprite->getTexture()->getSize()));
        } else
            animationData.isPlaying = false;
    }
}

void engine::system::stopAnimation(size_t entity)
{
    auto &r = engine::Manager::getRegistry();
    auto &animation = r->getComponent<uranus::ecs::component::Animation>(entity);

    for (uranus::ecs::component::AnimationData &animationData : animation->animations) {
        animationData.isPlaying = false;
    }
}

void engine::system::animation()
{
    auto &r = engine::Manager::getRegistry();
    for (auto [idx, sprite, animation] : uranus::ecs::View<uranus::ecs::component::Sprite, uranus::ecs::component::Animation>(*r)) {
        for (uranus::ecs::component::AnimationData &animationData : animation.animations) {
            if (!animationData.isPlaying) continue;
            if (animationData.clock.getElapsedTime().asSeconds() >= animationData.length) {
                animation.callback(idx, animationData.name);

                if (animationData.loop) {
                    animationData.clock.restart();
                } else
                    animationData.isPlaying = false;
            } else {
                for (uranus::ecs::component::FrameData &frame : animationData.frames) {
                    if (animationData.clock.getElapsedTime().asSeconds() >= frame.frameTime) {
                        sf::IntRect rect = get_animation_rect(frame.frame, animation.hFrame, animation.vFrame, sprite.sprite->getTexture()->getSize());
                        sprite.sprite->setTextureRect(rect);
                    }
                }
            }
        }
    }
}

void engine::system::removeDead()
{
    auto &r = engine::Manager::getRegistry();

    for (auto [idx, dead] : uranus::ecs::View<uranus::ecs::component::Dead>(*r)) {
        r->killEntity(idx);
    }
}

void engine::system::gameLoop()
{
    auto &window = engine::Manager::getWindow();
    auto &r = engine::Manager::getRegistry();
    auto &sceneManager = engine::Manager::getSceneManager();
    if (!ImGui::SFML::Init(*window)) spdlog::error("Failed to init ImGui-SFML");
    sf::Clock deltaClock;
    while (window->isOpen()) {
        engine::Event event;
        while (window->pollEvent(event)) {
            ImGui::SFML::ProcessEvent(*window, event);
            if (event.type == engine::Event::Closed) {
                close();
                return;
            }
            engine::system::input(event);
        }
        auto time = deltaClock.restart();
        ImGui::SFML::Update(*window, time); // Update ImGui

        window->clear();

        engine::system::loop();
        engine::system::position();
        engine::system::collision();
        engine::system::animation();
        engine::system::draw();

        drawImGui(window, r, time, deltaClock);

        window->display();
        engine::system::removeDead();

        sceneManager->switchScene();
    }
}

#include "network/NetworkManager.hpp"

void engine::system::drawImGui(std::shared_ptr<engine::RenderWindow> &window, std::shared_ptr<uranus::ecs::Registry> &registry, sf::Time &time, sf::Clock &clock)
{
    static bool set = false;
    static int fps = 60;
    static auto &networkManager = rtype::client::network::NetworkManager::getInstance();
    if (!set) {
        ImGui::SetWindowSize({350, 300});
        ImGui::SetWindowPos({0, 0});
        ImGui::SetWindowCollapsed(true);
        set = true;
    }
    auto timeDeltaMs = static_cast<float>(static_cast<double>(time.asMicroseconds()) / 1000.0);
    ImGui::TextWrapped("FPS: %.1f (Time delta: %.3f ms)", 1000.F / timeDeltaMs, timeDeltaMs); // NOLINT
    ImGui::TextWrapped("Entities: %d", registry->entitiesAliveCount()); // NOLINT
    ImGui::SliderInt("Max FPS", &fps, 10, 360, "%d"); // NOLINT
    window->setFramerateLimit(fps);
    ImGui::InputText("Server HOST", networkManager->imGuiHost.data(), networkManager->imGuiHost.capacity(), ImGuiInputTextFlags_CharsNoBlank);
    ImGui::InputText("Server TCP PORT", networkManager->imGuiTcpPort.data(), networkManager->imGuiTcpPort.capacity(), ImGuiInputTextFlags_CharsDecimal);
    ImGui::InputText("Server UDP PORT", networkManager->imGuiUdpPort.data(), networkManager->imGuiUdpPort.capacity(), ImGuiInputTextFlags_CharsDecimal);
    ImGui::InputText("Username", networkManager->imGuiUsername.data(), networkManager->imGuiUsername.capacity(), ImGuiInputTextFlags_CharsNoBlank);

    ImGui::SFML::Render(*window);
}

void engine::system::close()
{
    auto &window = engine::Manager::getWindow();
    auto &textureManager = engine::Manager::getTextureManager();
    for (auto &item: textureManager->getTextures()) item.reset();
    textureManager.reset();
    window->close();
}

void engine::system::gameInit()
{
    auto &window = engine::Manager::getWindow();
    auto &r = engine::Manager::getRegistry();
    window->setFramerateLimit(60);

    auto screenSize = sf::VideoMode::getDesktopMode();
    window->setPosition({static_cast<int>((screenSize.width - window->getSize().x) / 2), static_cast<int>((screenSize.height - window->getSize().y) / 2)});

    r->registerComponent<uranus::ecs::component::Position>(deletePosition);
    r->registerComponent<uranus::ecs::component::Velocity>(deleteVelocity);
    r->registerComponent<uranus::ecs::component::Drawable>(deleteDrawable);
    r->registerComponent<uranus::ecs::component::InputKeyboard>(deleteInputKeyboard);
    r->registerComponent<uranus::ecs::component::InputMouse>(deleteInputMouse);
    r->registerComponent<uranus::ecs::component::Sprite>(deleteSpriteComponent);
    r->registerComponent<uranus::ecs::component::Loop>(deleteLoopComponent);
    r->registerComponent<uranus::ecs::component::Collisionable>(deleteCollisionable);
    r->registerComponent<uranus::ecs::component::Animation>(deleteAnimationComponent);
    r->registerComponent<uranus::ecs::component::Name>(deleteNameComponent);
    r->registerComponent<uranus::ecs::component::RectangleShape>(deleteRectangleShapeComponent);
    r->registerComponent<uranus::ecs::component::NetworkId>(deleteNetworkIdComponent);
    r->registerComponent<uranus::ecs::component::Dead>(deleteDeadComponent);
}