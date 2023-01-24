#include <SFML/Graphics.hpp>
#include "include/entityManager.hpp"
#include <chrono>
#include "include/newScene.hpp"

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);

    auto &manager = EntityManager::getInstance();

    NewScene new_scene;
    manager->change_scene(new_scene);

    // Start the game loop
    std::chrono::high_resolution_clock::time_point start;
    std::chrono::high_resolution_clock::time_point end;
    float fps;

    while (window.isOpen())
    {
        manager->update(window);

        start = std::chrono::high_resolution_clock::now();

        manager->draw(window);

        end = std::chrono::high_resolution_clock::now();
        fps = (float)1e9/(float)std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
//        std::cout << fps << std::endl;
    }

    manager->clear();
    return EXIT_SUCCESS;
}