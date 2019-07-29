#include <algorithm>
#include <chrono>
#include <functional>
#include <random>
#include <string>

#include "Entities/Sprite.h"
#include "Game.h"
#include "Scenes/GameOverScene.h"
#include "Scenes/LevelScene.h"
#include "Scenes/StageScene.h"
#include "Util/Pathfinding.h"

namespace bomberman
{
    LevelScene::LevelScene(Game* _game, const unsigned int _stage, const unsigned int prevScore)
        : Scene(_game), score(prevScore), stage(_stage)
    {
        // common field parameters
        fieldPositionX = 0;
        fieldPositionY = game->getWindowHeight() / 15;
        const float scale =
            (game->getWindowHeight() - fieldPositionY) / static_cast<float>(tileArrayHeight * tileSize);
        scaledTileSize = static_cast<int>(round(scale * tileSize));
        // menu music
        menuMusic = std::make_shared<Music>(game->getAssetManager()->getMusic(MusicEnum::Level));
        menuMusic->play();
        // sounds
        gameoverSound = std::make_shared<Sound>(game->getAssetManager()->getSound(SoundEnum::Lose));
        winSound = std::make_shared<Sound>(game->getAssetManager()->getSound(SoundEnum::Win));
        explosionSound = std::make_shared<Sound>(game->getAssetManager()->getSound(SoundEnum::Explosion));
        // draw text
        spawnTextObjects();
        // generate tile map
        generateTileMap();
        // prepare player
        spawnPlayer(fieldPositionX + playerStartX * scaledTileSize,
                    fieldPositionY + playerStartY * scaledTileSize);
        // generate enemies
        generateEnemies();
        // set timer
        updateLevelTimer();
    }

    void LevelScene::spawnTextObjects()
    {
        const int fontWidth = static_cast<int>(game->getWindowWidth() / 32.0f);
        const int fontHeight = static_cast<int>(game->getWindowHeight() / 30.0f);
        // timer text
        auto timerText =
            std::make_shared<Text>(game->getAssetManager()->getFont(), game->getRenderer(), "TIME");
        timerText->setSize(fontWidth * 4, fontHeight);
        timerText->setPosition(30, 10);
        timerText->attachToCamera(false);
        addObject(timerText);
        backgroundObjectLastNumber++;

        // timer number
        timerNumber = std::make_shared<Text>(game->getAssetManager()->getFont(), game->getRenderer(), "000");
        timerNumber->setSize(fontWidth * 3, fontHeight);
        timerNumber->setPosition(timerText->getPositionX() + timerText->getWidth() + 30,
                                 timerText->getPositionY());
        timerNumber->attachToCamera(false);
        addObject(timerNumber);
        backgroundObjectLastNumber++;

        // score
        std::string scoreText = std::to_string(score);
        scoreNumber =
            std::make_shared<Text>(game->getAssetManager()->getFont(), game->getRenderer(), scoreText);
        scoreNumber->setSize(fontWidth * static_cast<int>(scoreText.size()), fontHeight);
        scoreNumber->setPosition(
            static_cast<int>(game->getWindowWidth() / 2.0f - scoreNumber->getWidth() / 2.0f),
            timerText->getPositionY());
        scoreNumber->attachToCamera(false);
        addObject(scoreNumber);
        backgroundObjectLastNumber++;

        // stage
        std::string stageTextConv = "STAGE " + std::to_string(stage);
        auto stageText =
            std::make_shared<Text>(game->getAssetManager()->getFont(), game->getRenderer(), stageTextConv);
        stageText->setSize(fontWidth * static_cast<int>(stageTextConv.size()), fontHeight);
        stageText->setPosition(game->getWindowWidth() - 30 - stageText->getWidth(),
                               timerText->getPositionY());
        stageText->attachToCamera(false);
        addObject(stageText);
        backgroundObjectLastNumber++;
    }

    void LevelScene::generateTileMap()
    {
        // we need random bricks
        const auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        auto randBrick = std::bind(std::uniform_int_distribution<int>(0, brickSpawnRandomize),
                                   std::mt19937(static_cast<unsigned int>(seed)));

        // iterate every tile
        for(int i = 0; i < static_cast<int>(tileArrayHeight); i++)
        {
            for(int j = 0; j < static_cast<int>(tileArrayWidth); j++)
            {
                tiles[i][j] = baseTiles[i][j];
                // generate random bricks
                if(tiles[i][j] == Tile::Grass)
                {
                    if(randBrick() == 0)
                    {
                        tiles[i][j] = Tile::Brick;
                    }
                }
                // spawn brick and grass
                if(tiles[i][j] == Tile::Brick)
                {
                    spawnGrass(fieldPositionX + j * scaledTileSize, fieldPositionY + i * scaledTileSize);
                    spawnBrick(fieldPositionX + j * scaledTileSize, fieldPositionY + i * scaledTileSize);
                }
                // spawn grass
                if(tiles[i][j] == Tile::Grass || tiles[i][j] == Tile::EmptyGrass)
                {
                    spawnGrass(fieldPositionX + j * scaledTileSize, fieldPositionY + i * scaledTileSize);
                }
                // spawn stone
                if(tiles[i][j] == Tile::Stone)
                {
                    spawnStone(fieldPositionX + j * scaledTileSize, fieldPositionY + i * scaledTileSize);
                }
            }
        }
    }

    void LevelScene::spawnGrass(const int positionX, const int positionY)
    {
        auto grass = std::make_shared<Sprite>(game->getAssetManager()->getTexture(Texture::Grass),
                                              game->getRenderer());
        grass->setPosition(positionX, positionY);
        grass->setSize(scaledTileSize, scaledTileSize);
        addObject(grass);
        backgroundObjectLastNumber++;
    }

    void LevelScene::spawnBrick(const int positionX, const int positionY)
    {
        auto brick = std::make_shared<Sprite>(game->getAssetManager()->getTexture(Texture::Brick),
                                              game->getRenderer());
        brick->setPosition(positionX, positionY);
        brick->setSize(scaledTileSize, scaledTileSize);
        addObject(brick);
        collisions.push_back(std::make_pair(Tile::Brick, brick));
    }

    void LevelScene::spawnStone(const int positionX, const int positionY)
    {
        auto stone = std::make_shared<Sprite>(game->getAssetManager()->getTexture(Texture::Stone),
                                              game->getRenderer());
        stone->setPosition(positionX, positionY);
        stone->setSize(scaledTileSize, scaledTileSize);
        addObject(stone);
        collisions.push_back(std::make_pair(Tile::Stone, stone));
        backgroundObjectLastNumber++;
    }

    void LevelScene::spawnPlayer(const int positionX, const int positionY)
    {
        // spawn player
        player = std::make_unique<Player>(game->getAssetManager()->getTexture(Texture::Player),
                                          game->getRenderer());
        player->setPosition(positionX, positionY);
        player->setSize(scaledTileSize, scaledTileSize);
        player->setClip(tileSize, tileSize, tileSize * 4, 0);
        addObject(player);
    }

    void LevelScene::spawnEnemy(Texture texture, AIType type, const int positionX, const int positionY)
    {
        auto enemy =
            std::make_shared<Enemy>(game->getAssetManager()->getTexture(texture), game->getRenderer());
        enemy->setPosition(positionX, positionY);
        enemy->setSize(scaledTileSize, scaledTileSize);
        enemy->setAIType(type);
        addObject(enemy);
        enemies.push_back(enemy);
    }

    void LevelScene::generateEnemies()
    {
        // we need enemy in random tile
        const auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        auto randCount = std::bind(std::uniform_int_distribution<int>(minEnemiesOnLevel, maxEnemiesOnLevel),
                                   std::mt19937(static_cast<unsigned int>(seed)));
        auto randType = std::bind(std::uniform_int_distribution<int>(0, 1),
                                  std::mt19937(static_cast<unsigned int>(seed)));
        auto randTexture = std::bind(std::uniform_int_distribution<int>(0, 2),
                                     std::mt19937(static_cast<unsigned int>(seed)));
        auto randCellX = std::bind(std::uniform_int_distribution<int>(0, tileArrayHeight - 1),
                                   std::mt19937(static_cast<unsigned int>(seed)));
        auto randCellY = std::bind(std::uniform_int_distribution<int>(0, tileArrayWidth - 1),
                                   std::mt19937(static_cast<unsigned int>(seed)));
        // start enemies spawn
        for(int i = 0; i < randCount(); i++)
        {
            // try to find suitable tile
            int cellX = randCellX();
            int cellY = randCellY();
            while(tiles[cellX][cellY] == Tile::Brick || tiles[cellX][cellY] == Tile::Stone ||
                  tiles[cellX][cellY] == Tile::EmptyGrass)
            {
                cellX = randCellX();
                cellY = randCellY();
            }
            // spawn enemy
            int textureRand = randTexture();
            spawnEnemy(textureRand == 0 ? Texture::Enemy1 :
                                          (textureRand == 1 ? Texture::Enemy2 : Texture::Enemy3),
                       randType() == 0 ? AIType::Wandering : AIType::Chasing,
                       fieldPositionX + cellY * scaledTileSize, fieldPositionY + cellX * scaledTileSize);
        }
    }

    void LevelScene::spawnBomb(Object* object)
    {
        // we can only have 1 bomb and should have object
        if(bomb || !object)
        {
            return;
        }
        // calculate position
        int bombPositionX = object->getPositionX();
        int bombPositionY = object->getPositionY() - fieldPositionY;
        const int bombPositionDiffX = bombPositionX % scaledTileSize;
        const int bombPositionDiffY = bombPositionY % scaledTileSize;
        // set bomb in strongly in cell
        bombPositionX = (bombPositionDiffX > scaledTileSize / 2) ?
                            bombPositionX + scaledTileSize - bombPositionDiffX :
                            bombPositionX - bombPositionDiffX;
        bombPositionY = (bombPositionDiffY > scaledTileSize / 2) ?
                            bombPositionY + scaledTileSize - bombPositionDiffY :
                            bombPositionY - bombPositionDiffY;
        bombPositionY += fieldPositionY;
        // create bomb in position
        bomb =
            std::make_shared<Sprite>(game->getAssetManager()->getTexture(Texture::Bomb), game->getRenderer());
        bomb->setSize(scaledTileSize, scaledTileSize);
        bomb->setPosition(bombPositionX, bombPositionY);
        insertObject(bomb, backgroundObjectLastNumber);
        // animation
        auto animation = std::make_shared<Animation>();
        animation->addAnimationEntity(AnimationEntity(0, 0, tileSize, tileSize));
        animation->addAnimationEntity(AnimationEntity(tileSize * 1, 0, tileSize, tileSize));
        animation->addAnimationEntity(AnimationEntity(tileSize * 2, 0, tileSize, tileSize));
        animation->addAnimationEntity(AnimationEntity(tileSize * 3, 0, tileSize, tileSize));
        animation->setSprite(bomb.get());
        bomb->addAnimation(animation);
        // change to bomb
        const int bombCellX = static_cast<int>(
            round((bomb->getPositionX() - fieldPositionX) / static_cast<float>(scaledTileSize)));
        const int bombCellY = static_cast<int>(
            round((bomb->getPositionY() - fieldPositionY) / static_cast<float>(scaledTileSize)));
        tiles[bombCellY][bombCellX] = Tile::Bomb;
        // update timer
        bombTimer = bombTimerStart;
        animation->play();
    }

    void LevelScene::spawnBang(Object* object)
    {
        // change to grass
        const int bombCellX = static_cast<int>(
            round((bomb->getPositionX() - fieldPositionX) / static_cast<float>(scaledTileSize)));
        const int bombCellY = static_cast<int>(
            round((bomb->getPositionY() - fieldPositionY) / static_cast<float>(scaledTileSize)));
        tiles[bombCellY][bombCellX] = Tile::Grass;
        // create bangs in position
        for(unsigned int i = 0; i < bangSpawnCells; i++)
        {
            auto bang = std::make_shared<Sprite>(game->getAssetManager()->getTexture(Texture::Explosion),
                                                 game->getRenderer());
            bang->setSize(scaledTileSize, scaledTileSize);
            bang->setPosition(object->getPositionX() + bangSpawnPositions[i][0] * scaledTileSize,
                              object->getPositionY() + bangSpawnPositions[i][1] * scaledTileSize);
            addObject(bang);
            bangs.push_back(bang);
            // change to bang
            const int bangCellX = static_cast<int>(
                round((bang->getPositionX() - fieldPositionX) / static_cast<float>(scaledTileSize)));
            const int bangCellY = static_cast<int>(
                round((bang->getPositionY() - fieldPositionY) / static_cast<float>(scaledTileSize)));
            tiles[bangCellY][bangCellX] = Tile::Bang;
            // animation
            auto animation = std::make_shared<Animation>();
            for(unsigned int j = 1; j < 12; j++)
            {
                animation->addAnimationEntity(AnimationEntity(tileSize * j, 0, tileSize, tileSize));
            }
            animation->setSprite(bang.get());
            bang->addAnimation(animation);
            animation->play();
            explosionSound->play();
        }
        // update timer
        bangTimer = bangTimerStart;
    }

    void LevelScene::spawnDoor(Object* object)
    {
        // create door in position
        door =
            std::make_shared<Sprite>(game->getAssetManager()->getTexture(Texture::Door), game->getRenderer());
        door->setSize(scaledTileSize, scaledTileSize);
        door->setPosition(object->getPositionX(), object->getPositionY());
        insertObject(door, backgroundObjectLastNumber);
    }

    void LevelScene::finish() const
    {
        menuMusic->stop();
        if(isWin)
        {
            winSound->play();
            game->getSceneManager()->addScene("stage", std::make_shared<StageScene>(game, stage + 1, score));
            game->getSceneManager()->activateScene("stage");
        }
        else
        {
            gameoverSound->play();
            game->getSceneManager()->activateScene("gameover");
        }
        game->getSceneManager()->removeScene("level");
    }

    void LevelScene::gameOver()
    {
        menuMusic->stop();
        gameOverTimer = gameOverTimerStart;
        isGameOver = true;
    }

    void LevelScene::exit() const
    {
        menuMusic->stop();
        game->getSceneManager()->activateScene("menu");
        game->getSceneManager()->removeScene("level");
    }

    void LevelScene::onEvent(const SDL_Event& event)
    {
        Scene::onEvent(event);
        // we need to update movement if movement keys pressed or released
        if((event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) && event.key.repeat == 0)
        {
            updateMovement(event.type == SDL_KEYDOWN ? true : false, event.key.keysym.scancode);
        }

        if(event.type == SDL_KEYDOWN)
        {
            // we should go to main menu by Escape key
            if(event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
            {
                gameOver();
                isWin = false;
                gameOverTimer = winTimerStart;
            }
            // we can spawn a bomb by space press
            else if(event.key.keysym.scancode == SDL_SCANCODE_SPACE)
            {
                if(!isGameOver)
                {
                    spawnBomb(player.get());
                }
            }
            // we can pause a game by pressing enter key
            else if(event.key.keysym.scancode == SDL_SCANCODE_RETURN)
            {
                isPaused = !isPaused;
                if(isPaused)
                {
                    menuMusic->pause();
                }
                else
                {
                    menuMusic->resume();
                }
            }
            // stage complete cheat
            else if(event.key.keysym.scancode == SDL_SCANCODE_BACKSPACE)
            {
                gameOver();
                isWin = true;
                score += scoreRewardForStage * 100;
                gameOverTimer = winTimerStart;
            }
        }
    }

    void LevelScene::update(const unsigned int delta)
    {
        // pause
        if(isPaused)
        {
            return;
        }
        Scene::update(delta);
        // update collision of player
        updatePlayerCollision();
        // update collision of enemies
        updateEnemiesCollision();
        // update collision of bricks
        updateBangsCollision();
        // update camera
        updateCamera();
        // update timers
        updateTimers(delta);
    }

    void LevelScene::updateTimers(const unsigned int delta)
    {
        // update level timer
        levelTimer -= delta;
        levelTimerDelta += delta;
        if(levelTimerDelta >= levelTimerUpdateText)
        {
            updateLevelTimer();
        }
        // update bomb timer
        if(bomb != nullptr)
        {
            updateBombTimer(delta);
        }
        // update bang timer
        if(bangs.size() > 0)
        {
            updateBangTimer(delta);
        }
        // update game over timer
        if(isGameOver)
        {
            updateGameOverTimer(delta);
        }

        // finish level if level timer is 0
        if(levelTimer <= 0 && !isGameOver)
        {
            gameOver();
            isWin = false;
            gameOverTimer = winTimerStart;
        }
    }

    void LevelScene::updateLevelTimer()
    {
        if(levelTimer < 0)
        {
            return;
        }
        levelTimerDelta = 0;
        const int timeInSec = static_cast<int>(levelTimer / 1000.0f);
        std::string timeString = std::to_string(timeInSec);
        while(timeString.size() < 3)
        {
            timeString = "0" + timeString;
        }
        timerNumber->setText(timeString);
    }

    void LevelScene::updateBombTimer(const unsigned int delta)
    {
        if(bombTimer > 0)
        {
            bombTimer -= delta;
        }
        else
        {
            spawnBang(bomb.get());
            removeObject(bomb);
            bomb = nullptr;
        }
    }

    void LevelScene::updateBangTimer(const unsigned int delta)
    {
        if(bangTimer > 0)
        {
            bangTimer -= delta;
        }
        else
        {
            for(auto& bang : bangs)
            {
                removeObject(bang);
                // change to grass
                const int bangCellX = static_cast<int>(
                    round((bang->getPositionX() - fieldPositionX) / static_cast<float>(scaledTileSize)));
                const int bangCellY = static_cast<int>(
                    round((bang->getPositionY() - fieldPositionY) / static_cast<float>(scaledTileSize)));
                tiles[bangCellY][bangCellX] = baseTiles[bangCellY][bangCellX];
            }
            bangs.clear();
        }
    }

    void LevelScene::updateGameOverTimer(const unsigned int delta)
    {
        if(gameOverTimer > 0)
        {
            gameOverTimer -= delta;
        }
        else
        {
            finish();
        }
    }

    void LevelScene::updateMovement(const bool isPressed, const int keycode)
    {
        if(player == nullptr)
        {
            return;
        }
        // on press we start movement
        if(isPressed)
        {
            switch(keycode)
            {
                case SDL_SCANCODE_W:
                case SDL_SCANCODE_UP:
                    playerDirectionY -= 1;
                    break;
                case SDL_SCANCODE_S:
                case SDL_SCANCODE_DOWN:
                    playerDirectionY += 1;
                    break;
                case SDL_SCANCODE_A:
                case SDL_SCANCODE_LEFT:
                    playerDirectionX -= 1;
                    break;
                case SDL_SCANCODE_D:
                case SDL_SCANCODE_RIGHT:
                    playerDirectionX += 1;
                    break;
                default:
                    break;
            }
        }
        // on release we stop moving
        else
        {
            switch(keycode)
            {
                case SDL_SCANCODE_W:
                case SDL_SCANCODE_UP:
                    playerDirectionY += 1;
                    break;
                case SDL_SCANCODE_S:
                case SDL_SCANCODE_DOWN:
                    playerDirectionY -= 1;
                    break;
                case SDL_SCANCODE_A:
                case SDL_SCANCODE_LEFT:
                    playerDirectionX += 1;
                    break;
                case SDL_SCANCODE_D:
                case SDL_SCANCODE_RIGHT:
                    playerDirectionX -= 1;
                    break;
                default:
                    break;
            }
        }
        // depend on pressed key choose player's direction
        MovementDirection direction = MovementDirection::None;
        if(playerDirectionX != 0)
        {
            if(playerDirectionX > 0)
            {
                direction = MovementDirection::Right;
            }
            else
            {
                direction = MovementDirection::Left;
            }
        }
        else if(playerDirectionY != 0)
        {
            if(playerDirectionY > 0)
            {
                direction = MovementDirection::Down;
            }
            else
            {
                direction = MovementDirection::Up;
            }
        }
        // apply direction
        player->setMovementDirection(direction);
    }

    void LevelScene::updateCamera()
    {
        if(player == nullptr)
        {
            return;
        }
        // consts for camera checking
        const int screenStart = fieldPositionX;
        const int screenFinish = fieldPositionX + scaledTileSize * static_cast<int>(tileArrayWidth);
        const int screenWidthHalf = game->getWindowWidth() / 2;
        int cameraPositionX = player->getPositionX();
        // check borders of screen
        if(cameraPositionX <= screenWidthHalf)
        {
            cameraPositionX = screenStart;
        }
        else if(cameraPositionX + screenWidthHalf >= screenFinish)
        {
            cameraPositionX = screenFinish - game->getWindowWidth();
        }
        else
        {
            cameraPositionX -= screenWidthHalf;
        }
        // time to move camera
        setCamera(cameraPositionX, 0);
    }

    void LevelScene::updateScore()
    {
        std::string scoreText = std::to_string(score);
        scoreNumber->setText(scoreText);
        scoreNumber->setSize(static_cast<int>(timerNumber->getWidth() / 3.0f) *
                                 static_cast<int>(scoreText.size()),
                             scoreNumber->getHeight());
        scoreNumber->setPosition(game->getWindowWidth() / 2 - scoreNumber->getWidth() / 2,
                                 scoreNumber->getPositionY());
    }

    void LevelScene::updatePlayerCollision()
    {
        if(player == nullptr)
        {
            return;
        }
        // there is no reason to check collision if player is idle
        if(!player->isMoving())
        {
            return;
        }
        // set width to smaller size for easer path
        SDL_Rect playerRect = player->getRect();
        playerRect.w = static_cast<int>(playerRect.w * 0.5);
        playerRect.h = static_cast<int>(playerRect.h * 0.5);
        // iterate objects for collision
        for(const auto& collisionObject : collisions)
        {
            if(isCollisionDetected(playerRect, collisionObject.second->getRect()))
            {
                player->revertLastMove();
            }
        }
        // door collision
        if(door != nullptr)
        {
            if(isCollisionDetected(playerRect, door->getRect()))
            {
                // check win condition
                if(!isGameOver && enemies.size() == 0)
                {
                    gameOver();
                    isWin = true;
                    score += scoreRewardForStage;
                    gameOverTimer = winTimerStart;
                }
            }
        }
    }

    void LevelScene::updateEnemiesCollision()
    {
        // iterate enemies for collision
        for(const auto& enemy : enemies)
        {
            // iterate drawables for collision
            for(const auto& collisionObject : collisions)
            {
                // check for block collision
                if(isCollisionDetected(enemy->getRect(), collisionObject.second->getRect()))
                {
                    // stop moving on collision detection
                    enemy->setMoving(false);
                    enemy->revertLastMove();
                }
            }
            // check for bomb collision
            if(bomb && isCollisionDetected(enemy->getRect(), bomb->getRect()))
            {
                // stop moving on collision detection
                enemy->setMoving(false);
                enemy->revertLastMove();
            }
            // check for player collision
            if(player != nullptr)
            {
                // set width to smaller size
                SDL_Rect playerRect = player->getRect();
                playerRect.w = static_cast<int>(playerRect.w * 0.2);
                playerRect.h = static_cast<int>(playerRect.h * 0.2);
                if(isCollisionDetected(playerRect, enemy->getRect()))
                {
                    // player killed by enemy
                    removeObject(player);
                    player = nullptr;
                    gameOver();
                }
            }
            if(player != nullptr)
            {
                // can attack?
                if(!enemy->isMovingToCell() && enemy->canAttack())
                {
                    // check for attack radius
                    if(abs(player->getPositionX() + player->getWidth() / 2 - enemy->getPositionX() -
                           enemy->getWidth() / 2) < enemy->getAttackRadius() &&
                       abs(player->getPositionY() + player->getHeight() / 2 - enemy->getPositionY() -
                           enemy->getHeight() / 2) < enemy->getAttackRadius())
                    {
                        // start follow to player
                        followToPlayer(enemy.get());
                    }
                }
            }
        }
    }

    void LevelScene::updateBangsCollision()
    {
        // check for bang collision
        for(const auto& bang : bangs)
        {
            // check bricks
            auto itCollision = collisions.begin();
            while(itCollision != collisions.end())
            {
                if((*itCollision).first == Tile::Brick)
                {
                    auto brick = (*itCollision).second;
                    if(isCollisionDetected(brick->getRect(), bang->getRect()))
                    {
                        destroyBrick(brick);
                        // remove brick from collision array
                        itCollision = collisions.erase(itCollision);
                        continue;
                    }
                }
                ++itCollision;
            }
            // check enemies
            auto itEnemies = enemies.begin();
            while(itEnemies != enemies.end())
            {
                SDL_Rect enemyRect = (*itEnemies)->getRect();
                enemyRect.w = static_cast<int>(enemyRect.w * 0.2);
                enemyRect.h = static_cast<int>(enemyRect.h * 0.2);
                if(isCollisionDetected(enemyRect, bang->getRect()))
                {
                    removeObject(*itEnemies);
                    itEnemies = enemies.erase(itEnemies);

                    // enemy killed by bang
                    score += scoreRewardForKill;
                    updateScore();
                    continue;
                }
                ++itEnemies;
            }
            // check player
            if(player != nullptr)
            {
                SDL_Rect playerRect = player->getRect();
                playerRect.w = static_cast<int>(playerRect.w * 0.2f);
                playerRect.h = static_cast<int>(playerRect.h * 0.2f);
                if(isCollisionDetected(playerRect, bang->getRect()))
                {
                    removeObject(player);
                    player = nullptr;
                    gameOver();
                }
            }
        }
    }

    bool LevelScene::isCollisionDetected(const SDL_Rect& rect1, const SDL_Rect& rect2) const
    {
        // check for collision
        if(rect1.x + rect1.w / 2 < rect2.x - rect2.w / 2)
            return false;
        if(rect1.x - rect1.w / 2 > rect2.x + rect2.w / 2)
            return false;
        if(rect1.y + rect1.h / 2 < rect2.y - rect2.h / 2)
            return false;
        if(rect1.y - rect1.h / 2 > rect2.y + rect2.h / 2)
            return false;

        return true;
    }

    void LevelScene::destroyBrick(std::shared_ptr<Object> brick)
    {
        // we need door if don't have
        if(door == nullptr)
        {
            // left bricks count
            long bricksCount = std::count_if(collisions.begin(), collisions.end(),
                                             [](auto collision) { return collision.first == Tile::Brick; });
            // random for door spawn
            const auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
            auto randDoor = std::bind(std::uniform_int_distribution<int>(0, doorSpawnRandomize),
                                      std::mt19937(static_cast<unsigned int>(seed)));
            // spawn door if we can
            if(randDoor() == 0 || bricksCount <= 1)
            {
                spawnDoor(brick.get());
            }
        }
        // change brick to grass and remove it
        const int brickCellX = static_cast<int>(
            round((brick->getPositionX() - fieldPositionX) / static_cast<float>(scaledTileSize)));
        const int brickCellY = static_cast<int>(
            round((brick->getPositionY() - fieldPositionY) / static_cast<float>(scaledTileSize)));
        tiles[brickCellY][brickCellX] = Tile::Grass;
        removeObject(brick);
    }

    void LevelScene::followToPlayer(Enemy* enemy)
    {
        // move to nearest cell if enemy is wandering
        if(enemy->isMoving())
        {
            std::pair<int, int> cell = std::make_pair(0, 0);
            enemy->moveToCell(cell);
            return;
        }
        // get cells of creatures by their position
        const int playerCellX = static_cast<int>(
            round((player->getPositionX() - fieldPositionX) / static_cast<float>(scaledTileSize)));
        const int playerCellY = static_cast<int>(
            round((player->getPositionY() - fieldPositionY) / static_cast<float>(scaledTileSize)));
        const int enemyCellX = static_cast<int>(
            round((enemy->getPositionX() - fieldPositionX) / static_cast<float>(scaledTileSize)));
        const int enemyCellY = static_cast<int>(
            round((enemy->getPositionY() - fieldPositionY) / static_cast<float>(scaledTileSize)));

        // Source is the left-most bottom-most corner
        std::pair<unsigned int, unsigned int> src = std::make_pair(enemyCellY, enemyCellX);

        // Destination is the left-most top-most corner
        std::pair<unsigned int, unsigned int> dest = std::make_pair(playerCellY, playerCellX);

        // get best nearest cell to follow
        std::pair<int, int> cell = findBestCell(tiles, src, dest);
        if(cell.first >= 0 && cell.second >= 0)
        {
            cell.first -= src.first;
            cell.second -= src.second;
            enemy->moveToCell(cell);
        }
        else
        {
            enemy->generateNewPath();
        }
    }
} // namespace bomberman
