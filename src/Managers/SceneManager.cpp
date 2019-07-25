#include <iostream>

#include "Managers/SceneManager.h"

namespace bomberman
{
    SceneManager::SceneManager() {}

    void SceneManager::addScene(const std::string& name, const std::shared_ptr<Scene> scene)
    {
        const auto it = scenes.find(name);
        if(it != scenes.end() && it->second)
        {
            std::cout << "SceneManager::addScene - scene '" << name << "' already exist in scene tree!"
                      << std::endl;
            return;
        }
        scenes[name] = std::move(scene);
    }

    void SceneManager::activateScene(const std::string& name)
    {
        // try to find scene by name
        const auto it = scenes.find(name);
        if(it != scenes.end())
        {
            if(currentScene)
            {
                currentScene->onExit();
            }
            currentScene = it->second;
            currentScene->onEnter();
        }
        else
        {
            std::cout << "SceneManager::activateScene - scene '" << name << "' doesn't exist!" << std::endl;
        }
    }

    void SceneManager::removeScene(const std::string& name)
    {
        // try to find scene by name
        const auto it = scenes.find(name);
        if(it != scenes.end())
        {
            if(it->second == currentScene)
            {
                currentScene->onExit();
                currentScene = nullptr;
            }
            // add to the queue for later delete on update
            removedScenes.push(it->second);
            scenes.erase(name);
        }
        else
        {
            std::cout << "SceneManager::activateScene - scene '" << name << "' doesn't exist!" << std::endl;
        }
    }

    void SceneManager::onEvent(const SDL_Event& event)
    {
        currentScene->onEvent(event);
    }

    void SceneManager::update(const unsigned int delta)
    {
        // finally remove removed scenes
        while(removedScenes.size() > 0)
        {
            removedScenes.pop();
        }

        currentScene->update(delta);
    }

    void SceneManager::draw() const
    {
        currentScene->draw();
    }
} // namespace bomberman
