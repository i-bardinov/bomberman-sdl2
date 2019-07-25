#ifndef _BOMBERMAN_SCENES_MENU_SCENE_H_
#define _BOMBERMAN_SCENES_MENU_SCENE_H_

#include <SDL.h>
#include <memory>

#include "Entities/Music.h"
#include "Entities/Text.h"
#include "Scenes/Scene.h"

namespace bomberman
{
    /**
     * @brief Menu id
     *
     */
    enum class MenuItem
    {
        None,
        Start,
        Exit,
        Last
    };
    /**
     * @brief Menu Scene
     *
     */
    class MenuScene : public Scene
    {
      public:
        /**
         * @brief Construct a new Menu Scene
         *
         * @param game
         */
        MenuScene(Game* game);
        /**
         * @brief Called when scene was activated
         *
         */
        virtual void onEnter() override;
        /**
         * @brief Called when scene was deactivated
         *
         */
        virtual void onExit() override;
        /**
         * @brief Trigger on SDL2 event if scene is active
         *
         * @param event - SDL2 event
         */
        virtual void onEvent(const SDL_Event& event) override;

      private:
        /**
         * @brief called when menu item was selected
         *
         */
        void onMenuItemSelect();
        /**
         * @brief called when menu item was pressed
         *
         */
        void onMenuItemPress();

        std::shared_ptr<Text> startText = nullptr;      // menu start
        std::shared_ptr<Text> exitText = nullptr;       // menu exit
        std::shared_ptr<Music> menuMusic = nullptr;     // menu music
        MenuItem currentSelectedMenu = MenuItem::Start; // current selected menu

        // const colors for menu selection
        const SDL_Color colorStandard = {255, 255, 255, 255};
        const SDL_Color colorPressed = {66, 134, 244, 255};
    };
} // namespace bomberman

#endif // _BOMBERMAN_SCENES_MENU_SCENE_H_
