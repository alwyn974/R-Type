/*
** EPITECH PROJECT, 2023
** SceneManager.cpp
** File description:
** SceneManager.cpp
*/

#include "uranus/engine/manager/SceneManager.hpp"
#include "uranus/engine/manager/Manager.hpp"

void engine::SceneManager::addScene(const std::shared_ptr<engine::Scene> &newScene)
{
    this->_scenes.push_back(newScene);
}


void engine::SceneManager::changeScene(const std::string &sceneToSwitch)
{
    this->_sceneToSwitch = sceneToSwitch;
}

void engine::SceneManager::switchScene()
{
    if (this->_sceneToSwitch.empty())
        return;
    for (auto &scene : this->_scenes) {
        if (scene->getName() == this->_sceneToSwitch) {
            scene->clear();
//            engine::Manager::killAllEntitiesAndPrefabs();

            this->_actualScene = scene;
            this->_actualScene->init();
            this->_sceneToSwitch = "";
            break;
        }
    }
}
