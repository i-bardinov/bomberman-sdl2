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
        text->setSize(game->getWindowWidth() / 3.0f, game->getWindowHeight() / 20.0f);
        text->setPosition(game->getWindowWidth() / 2 - text->getWidth() / 2,
                          game->getWindowHeight() / 2 - text->getHeight() / 2);
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
