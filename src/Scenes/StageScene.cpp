#include <string>

#include "Game.h"
#include "Scenes/LevelScene.h"
#include "Scenes/MenuScene.h"
#include "Scenes/StageScene.h"

namespace bomberman
{
    StageScene::StageScene(Game* _game, const unsigned int level, const unsigned int _score)
        : Scene(_game), stage(level), score(_score)
    {
        // stage text
        auto text = std::make_shared<Text>(game->getAssetManager()->getFont(), game->getRenderer(),
                                           "STAGE " + std::to_string(level));
        text->setSize(static_cast<int>(game->getWindowWidth() / 3.0f),
                      static_cast<int>(game->getWindowHeight() / 20.0f));
        text->setPosition(static_cast<int>(game->getWindowWidth() / 2.0f - text->getWidth() / 2.0f),
                          static_cast<int>(game->getWindowHeight() / 2.0f - text->getHeight() / 2.0f));
        addObject(text);
    }

    void StageScene::update(const unsigned int delta)
    {
        untilNextSceneTimer += delta;
        if(untilNextSceneTimer >= sceneTimer)
        {
            untilNextSceneTimer = 0;
            game->getSceneManager()->addScene("level", std::make_shared<LevelScene>(game, stage, score));
            game->getSceneManager()->activateScene("level");
            game->getSceneManager()->removeScene("stage");
        }
    }
} // namespace bomberman
