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
    if (this->_sceneToSwitch == "")
        return;
    for (std::shared_ptr<engine::Scene> &sceneItem : this->_scenes) {
        if (sceneItem->getName() == this->_sceneToSwitch) {
            engine::Manager::killAllEntitiesAndPrefabs();

            this->_actualScene = sceneItem;
            this->_actualScene->init();
            this->_sceneToSwitch = "";
            break;
        }
    }
}
