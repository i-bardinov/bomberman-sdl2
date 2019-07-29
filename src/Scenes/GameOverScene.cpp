#include <string>

#include "Game.h"
#include "Scenes/GameOverScene.h"
#include "Scenes/MenuScene.h"

namespace bomberman
{
    GameOverScene::GameOverScene(Game* _game) : Scene(_game)
    {
        // game over text
        auto gameOverText =
            std::make_shared<Text>(game->getAssetManager()->getFont(), game->getRenderer(), "GAME OVER");
        gameOverText->setSize(static_cast<int>(game->getWindowWidth() / 3.0f),
                              static_cast<int>(game->getWindowHeight() / 20.0f));
        gameOverText->setPosition(
            static_cast<int>(game->getWindowWidth() / 2.0f - gameOverText->getWidth() / 2.0f),
            static_cast<int>(game->getWindowHeight() / 2.0f - gameOverText->getHeight() / 2.0f));
        addObject(gameOverText);
    }

    void GameOverScene::update(const unsigned int delta)
    {
        untilNextSceneTimer += delta;
        if(untilNextSceneTimer >= sceneTimer)
        {
            untilNextSceneTimer = 0;
            game->getSceneManager()->activateScene("menu");
        }
    }
} // namespace bomberman
