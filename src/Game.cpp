#include <SDL_image.h>
#include <SDL_ttf.h>

#include <iostream>

#include "Game.h"
#include "Scenes/LevelScene.h"
#include "Scenes/MenuScene.h"

namespace bomberman
{
    Game::Game(const std::string& windowName, const int width, const int height)
        : windowWidth(width), windowHeight(height)
    {
        // let's init SDL2
        if(SDL_Init(SDL_INIT_VIDEO) != 0)
        {
            std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
            return;
        }

        // let's init SDL2 TTF
        if(TTF_Init() != 0)
        {
            std::cout << "TTF_Init Error: " << TTF_GetError() << std::endl;
            return;
        }

        // let's init SDL2 Image
        if(!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
        {
            std::cout << "IMG_Init Error: " << IMG_GetError() << std::endl;
            return;
        }

        // create a window
        window = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                  windowWidth, windowHeight, SDL_WINDOW_SHOWN);
        if(!window)
        {
            std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
            return;
        }

        // create a renderer for window
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if(renderer == nullptr)
        {
            std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
            return;
        }

        assetManager = new AssetManager();
        sceneManager = new SceneManager();
    }

    Game::~Game()
    {
        delete sceneManager;
        delete assetManager;
        // delete SDL2 C pointers
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);

        // SDL2 finish
        IMG_Quit();
        TTF_Quit();
        SDL_Quit();
    }

    void Game::run()
    {
        if(isRunning)
        {
            return;
        }

        isRunning = true;

        // load assets
        assetManager->load(renderer);
        // create menu scene
        sceneManager->addScene("menu", std::make_shared<MenuScene>(this));
        sceneManager->activateScene("menu");

        SDL_Event event;

        while(isRunning)
        {
            // check SDL2 events
            while(SDL_PollEvent(&event))
            {
                // send event to current scene
                sceneManager->onEvent(event);
                // stop loop on quit
                if(event.type == SDL_QUIT)
                {
                    stop();
                }
            }

            // calculate delta
            Uint32 tickTime = SDL_GetTicks();
            Uint32 delta = tickTime - lastTickTime;
            lastTickTime = tickTime;
            // update current scene
            sceneManager->update(delta);

            // clear the screen
            SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
            SDL_RenderClear(renderer);
            // draw current scene
            sceneManager->draw();
            // flip the backbuffer
            SDL_RenderPresent(renderer);
        }
    }

    void Game::stop()
    {
        isRunning = false;
    }

    int Game::getWindowWidth() const
    {
        return windowWidth;
    }

    int Game::getWindowHeight() const
    {
        return windowHeight;
    }

    SDL_Renderer* Game::getRenderer() const
    {
        return renderer;
    }

    SceneManager* Game::getSceneManager() const
    {
        return sceneManager;
    }

    AssetManager* Game::getAssetManager() const
    {
        return assetManager;
    }
} // namespace bomberman
