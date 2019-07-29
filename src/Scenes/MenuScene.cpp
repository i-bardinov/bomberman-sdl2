#include <string>

#include "Entities/Sprite.h"
#include "Game.h"
#include "Scenes/GameOverScene.h"
#include "Scenes/LevelScene.h"
#include "Scenes/MenuScene.h"
#include "Scenes/StageScene.h"

namespace bomberman
{
    // ++increment for menu id
    MenuItem& operator++(MenuItem& c)
    {
        using type = typename std::underlying_type<MenuItem>::type;
        c = static_cast<MenuItem>(static_cast<type>(c) + 1);
        if(c == MenuItem::Last)
            c = static_cast<MenuItem>(static_cast<type>(MenuItem::None) + 1);
        return c;
    }

    // --decrement for menu id
    MenuItem& operator--(MenuItem& c)
    {
        using type = typename std::underlying_type<MenuItem>::type;
        c = static_cast<MenuItem>(static_cast<type>(c) - 1);
        if(c == MenuItem::None)
            c = static_cast<MenuItem>(static_cast<type>(MenuItem::Last) - 1);
        return c;
    }

    // increment++ for menu id
    MenuItem operator++(MenuItem& c, int)
    {
        MenuItem result = c;
        ++c;
        return result;
    }

    // decrement-- for menu id
    MenuItem operator--(MenuItem& c, int)
    {
        MenuItem result = c;
        --c;
        return result;
    }

    MenuScene::MenuScene(Game* _game) : Scene(_game)
    {
        // background
        auto background = std::make_shared<Sprite>(game->getAssetManager()->getTexture(Texture::MenuBack),
                                                   game->getRenderer());
        background->setPosition(30, 20);
        background->setSize(game->getWindowWidth() - 60,
                            static_cast<int>(game->getWindowHeight() / 1.5f) - 20);
        addObject(background);

        // start menu
        startText = std::make_shared<Text>(game->getAssetManager()->getFont(), game->getRenderer(), "START");
        startText->setColor(colorPressed);
        startText->setSize(static_cast<int>(game->getWindowWidth() / 4.0f),
                           static_cast<int>(game->getWindowHeight() / 20.0f));
        startText->setPosition(static_cast<int>(game->getWindowWidth() / 2.0f - startText->getWidth() / 2.0f),
                               background->getHeight() + 60);
        addObject(startText);

        // exit menu
        exitText = std::make_shared<Text>(game->getAssetManager()->getFont(), game->getRenderer(), "EXIT");
        exitText->setSize(static_cast<int>(game->getWindowWidth() / 4.0f),
                          static_cast<int>(game->getWindowHeight() / 20.0f));
        exitText->setPosition(startText->getPositionX(),
                              startText->getPositionY() + exitText->getHeight() + 40);
        addObject(exitText);

        game->getSceneManager()->addScene("gameover", std::make_shared<GameOverScene>(game));
        // menu music
        menuMusic = std::make_shared<Music>(game->getAssetManager()->getMusic(MusicEnum::MainMenu));
    }

    void MenuScene::onEnter()
    {
        menuMusic->play();
    }

    void MenuScene::onExit()
    {
        menuMusic->stop();
    }

    void MenuScene::onEvent(const SDL_Event& event)
    {
        Scene::onEvent(event);
        if(event.type == SDL_KEYDOWN)
        {
            switch(event.key.keysym.scancode)
            {
                // we should select next menu item
                case SDL_SCANCODE_S:
                case SDL_SCANCODE_DOWN:
                    currentSelectedMenu++;
                    onMenuItemSelect();
                    break;
                // we should select prev menu item
                case SDL_SCANCODE_W:
                case SDL_SCANCODE_UP:
                    currentSelectedMenu--;
                    onMenuItemSelect();
                    break;
                // enter in menu item
                case SDL_SCANCODE_SPACE:
                case SDL_SCANCODE_RETURN:
                    onMenuItemPress();
                    break;
                default:
                    break;
            }
        }
    }

    void MenuScene::onMenuItemSelect()
    {
        // reset menu items color
        startText->setColor(colorStandard);
        exitText->setColor(colorStandard);
        // change color of selected menu item
        switch(currentSelectedMenu)
        {
            case MenuItem::Start:
                startText->setColor(colorPressed);
                break;
            case MenuItem::Exit:
                exitText->setColor(colorPressed);
                break;
            default:
                break;
        }
    }

    void MenuScene::onMenuItemPress()
    {
        switch(currentSelectedMenu)
        {
            case MenuItem::Start:
                // go to level scene
                game->getSceneManager()->addScene("stage", std::make_shared<StageScene>(game, 1, 0));
                game->getSceneManager()->activateScene("stage");
                break;
            case MenuItem::Exit:
                // stop game loop
                game->stop();
                break;
            default:
                break;
        }
    }
} // namespace bomberman
