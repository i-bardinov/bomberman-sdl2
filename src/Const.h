#ifndef _BOMBERMAN_CONST_H_
#define _BOMBERMAN_CONST_H_
/**
 * @brief Tiles class for tile map creation
 *
 */
enum class Tile
{
    Stone,
    Grass,
    Brick,
    EmptyGrass,
    Bomb,
    Bang
};

const int playerStartX = 1; // player start position X on tilemap
const int playerStartY = 1; // player start position Y on tilemap

const unsigned int brickSpawnRandomize = 10; // less value => more bricks
const unsigned int doorSpawnRandomize = 10;  // less value => door is far
const unsigned int bangSpawnCells = 5;       // bang spawn number of cells
const unsigned int minEnemiesOnLevel = 2;    // minimum enemies count on level
const unsigned int maxEnemiesOnLevel = 10;   // maximum enemies count on level
const int bangSpawnPositions[bangSpawnCells][2] = {{0, 0},
                                                   {0, 1},
                                                   {1, 0},
                                                   {0, -1},
                                                   {-1, 0}}; // cell's position of bang

const unsigned int tileArrayWidth = 31;                   // tile array width
const unsigned int tileArrayHeight = 13;                  // tile array height
const unsigned int tileSize = 16;                         // size in pixels of tile
const Tile baseTiles[tileArrayHeight][tileArrayWidth] = { // base tilemap
    {Tile::Stone, Tile::Stone, Tile::Stone, Tile::Stone, Tile::Stone, Tile::Stone, Tile::Stone, Tile::Stone,
     Tile::Stone, Tile::Stone, Tile::Stone, Tile::Stone, Tile::Stone, Tile::Stone, Tile::Stone, Tile::Stone,
     Tile::Stone, Tile::Stone, Tile::Stone, Tile::Stone, Tile::Stone, Tile::Stone, Tile::Stone, Tile::Stone,
     Tile::Stone, Tile::Stone, Tile::Stone, Tile::Stone, Tile::Stone, Tile::Stone, Tile::Stone},
    {Tile::Stone, Tile::EmptyGrass, Tile::EmptyGrass, Tile::EmptyGrass, Tile::Grass, Tile::Grass, Tile::Grass,
     Tile::Grass, Tile::Grass,      Tile::Grass,      Tile::Grass,      Tile::Grass, Tile::Grass, Tile::Grass,
     Tile::Grass, Tile::Grass,      Tile::Grass,      Tile::Grass,      Tile::Grass, Tile::Grass, Tile::Grass,
     Tile::Grass, Tile::Grass,      Tile::Grass,      Tile::Grass,      Tile::Grass, Tile::Grass, Tile::Grass,
     Tile::Grass, Tile::Grass,      Tile::Stone},
    {Tile::Stone, Tile::EmptyGrass, Tile::Stone, Tile::EmptyGrass, Tile::Stone, Tile::Grass, Tile::Stone,
     Tile::Grass, Tile::Stone,      Tile::Grass, Tile::Stone,      Tile::Grass, Tile::Stone, Tile::Grass,
     Tile::Stone, Tile::Grass,      Tile::Stone, Tile::Grass,      Tile::Stone, Tile::Grass, Tile::Stone,
     Tile::Grass, Tile::Stone,      Tile::Grass, Tile::Stone,      Tile::Grass, Tile::Stone, Tile::Grass,
     Tile::Stone, Tile::Grass,      Tile::Stone},
    {Tile::Stone, Tile::EmptyGrass, Tile::EmptyGrass, Tile::EmptyGrass, Tile::Grass, Tile::Grass, Tile::Grass,
     Tile::Grass, Tile::Grass,      Tile::Grass,      Tile::Grass,      Tile::Grass, Tile::Grass, Tile::Grass,
     Tile::Grass, Tile::Grass,      Tile::Grass,      Tile::Grass,      Tile::Grass, Tile::Grass, Tile::Grass,
     Tile::Grass, Tile::Grass,      Tile::Grass,      Tile::Grass,      Tile::Grass, Tile::Grass, Tile::Grass,
     Tile::Grass, Tile::Grass,      Tile::Stone},
    {Tile::Stone, Tile::Grass, Tile::Stone, Tile::Grass, Tile::Stone, Tile::Grass, Tile::Stone, Tile::Grass,
     Tile::Stone, Tile::Grass, Tile::Stone, Tile::Grass, Tile::Stone, Tile::Grass, Tile::Stone, Tile::Grass,
     Tile::Stone, Tile::Grass, Tile::Stone, Tile::Grass, Tile::Stone, Tile::Grass, Tile::Stone, Tile::Grass,
     Tile::Stone, Tile::Grass, Tile::Stone, Tile::Grass, Tile::Stone, Tile::Grass, Tile::Stone},
    {Tile::Stone, Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass,
     Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass,
     Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass, Tile::Brick, Tile::Grass, Tile::Grass, Tile::Grass,
     Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass, Tile::Stone},
    {Tile::Stone, Tile::Grass, Tile::Stone, Tile::Grass, Tile::Stone, Tile::Grass, Tile::Stone, Tile::Grass,
     Tile::Stone, Tile::Grass, Tile::Stone, Tile::Grass, Tile::Stone, Tile::Grass, Tile::Stone, Tile::Grass,
     Tile::Stone, Tile::Grass, Tile::Stone, Tile::Grass, Tile::Stone, Tile::Grass, Tile::Stone, Tile::Grass,
     Tile::Stone, Tile::Grass, Tile::Stone, Tile::Grass, Tile::Stone, Tile::Grass, Tile::Stone},
    {Tile::Stone, Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass,
     Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass,
     Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass,
     Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass, Tile::Stone},
    {Tile::Stone, Tile::Grass, Tile::Stone, Tile::Grass, Tile::Stone, Tile::Grass, Tile::Stone, Tile::Grass,
     Tile::Stone, Tile::Grass, Tile::Stone, Tile::Grass, Tile::Stone, Tile::Grass, Tile::Stone, Tile::Grass,
     Tile::Stone, Tile::Grass, Tile::Stone, Tile::Grass, Tile::Stone, Tile::Grass, Tile::Stone, Tile::Grass,
     Tile::Stone, Tile::Grass, Tile::Stone, Tile::Grass, Tile::Stone, Tile::Grass, Tile::Stone},
    {Tile::Stone, Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass,
     Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass,
     Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass,
     Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass, Tile::Stone},
    {Tile::Stone, Tile::Grass, Tile::Stone, Tile::Grass, Tile::Stone, Tile::Grass, Tile::Stone, Tile::Grass,
     Tile::Stone, Tile::Grass, Tile::Stone, Tile::Grass, Tile::Stone, Tile::Grass, Tile::Stone, Tile::Grass,
     Tile::Stone, Tile::Grass, Tile::Stone, Tile::Grass, Tile::Stone, Tile::Grass, Tile::Stone, Tile::Grass,
     Tile::Stone, Tile::Grass, Tile::Stone, Tile::Grass, Tile::Stone, Tile::Grass, Tile::Stone},
    {Tile::Stone, Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass,
     Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass,
     Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass,
     Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass, Tile::Stone},
    {Tile::Stone, Tile::Stone, Tile::Stone, Tile::Stone, Tile::Stone, Tile::Stone, Tile::Stone, Tile::Stone,
     Tile::Stone, Tile::Stone, Tile::Stone, Tile::Stone, Tile::Stone, Tile::Stone, Tile::Stone, Tile::Stone,
     Tile::Stone, Tile::Stone, Tile::Stone, Tile::Stone, Tile::Stone, Tile::Stone, Tile::Stone, Tile::Stone,
     Tile::Stone, Tile::Stone, Tile::Stone, Tile::Stone, Tile::Stone, Tile::Stone, Tile::Stone}};

#endif // _BOMBERMAN_CONST_H_
