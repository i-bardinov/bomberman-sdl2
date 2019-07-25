# Bomberman

## Status:
| Linux GCC | Linux Clang | MacOS |
|-----------|-------------|-------|
| [![Build Status](https://travis-matrix-badges.herokuapp.com/repos/i-bardinov/bomberman-sdl2/branches/master/1)](https://travis-ci.org/i-bardinov/bomberman-sdl2) | [![Build Status](https://travis-matrix-badges.herokuapp.com/repos/i-bardinov/bomberman-sdl2/branches/master/2)](https://travis-ci.org/i-bardinov/bomberman-sdl2) | [![Build Status](https://travis-matrix-badges.herokuapp.com/repos/i-bardinov/bomberman-sdl2/branches/master/3)](https://travis-ci.org/i-bardinov/bomberman-sdl2) |

## Build:
- Install `SDL2, SDL2_image, SDL2_ttf, SDL2_mixer`.
  - MacOS:
    ```sh
    brew install SDL2 SDL2_image SDL2_ttf SDL2_mixer
    ```
  - Ubuntu:
    ```sh
    sudo apt install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev
    ```

- Build Bomberman SDL2
    ```sh
    mkdir build && cd build
    cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../install
    cmake --build . --target install
    ```

- Run
    ```sh
    cd ../install/bin
    ./bomberman
    ```

## Rules is simple:
  - Menu selection using SPACE or ENTER
  - To navigate use arrows or WSAD
  - You can exit from level using ESCAPE
  - You can skip level using BACKSPACE
  - You can pause a game using ENTER
  - You should kill all enemies and find the door in the bricks
  - Enemies can kill you!
  - You have 200 seconds, hurry up!
