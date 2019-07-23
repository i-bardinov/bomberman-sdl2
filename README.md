# Instruction for Bomberman SDL2
## Build:
- Install `SDL2, SDL2_image, SDL2_ttf` for example using: 
    ```sh
    brew install SDL2 SDL2_image SDL2_ttf
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

- CONTROL:
   - Menu selection using SPACE or ENTER
   - To navigate use arrows or WSAD
   - You can exit from level using ESCAPE
   - You can skip level using BACKSPACE
   - You should kill all enemies and find the door in the bricks by destroying it
   - Enemies can kill you!
   - You have 200 seconds, hurry up!