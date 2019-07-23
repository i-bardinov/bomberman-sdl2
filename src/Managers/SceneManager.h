#ifndef _BOMBERMAN_MANAGERS_SCENE_MANAGER_H_
#define _BOMBERMAN_MANAGERS_SCENE_MANAGER_H_

#include <memory>
#include <queue>
#include <string>
#include <unordered_map>

#include "Scenes/Scene.h"

namespace bomberman
{
    /**
     * @brief Scene Manager
     *
     */
    class SceneManager
    {
      public:
        /**
         * @brief Construct a new Scene Manager object
         *
         */
        SceneManager();
        /**
         * @brief add scene to manager
         *
         * @param name - name of scene
         * @param scene - scene pointer
         */
        void addScene(const std::string& name, std::shared_ptr<Scene> scene);
        /**
         * @brief activate scene by name
         *
         * @param name - name of scene
         */
        void activateScene(const std::string& name);
        /**
         * @brief remove scene by name
         *
         * @param name - name of scene
         */
        void removeScene(const std::string& name);
        /**
         * @brief send event to active scene
         *
         * @param event - SDL2 event
         */
        void onEvent(const SDL_Event& event);
        /**
         * @brief update active scene
         *
         * @param delta - time in milliseconds
         */
        void update(const unsigned int delta);
        /**
         * @brief draw objects of active scene
         *
         */
        void draw() const;

      private:
        std::unordered_map<std::string, std::shared_ptr<Scene>> scenes; // scenes
        std::queue<std::shared_ptr<Scene>> removedScenes;               // removed scenes, for clean up
        std::shared_ptr<Scene> currentScene = nullptr;                  // active scene
    };
} // namespace bomberman

#endif // _BOMBERMAN_MANAGERS_SCENE_MANAGER_H_
