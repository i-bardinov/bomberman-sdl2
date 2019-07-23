Instruction for bomberman clone

- BUILD:

0) Tested on MacOS 10.4.4, AppleClang 9, SDL 2.0.15

1) Install SDL2, SDL2_image, SDL2_ttf
   for example using: 
   - brew install SDL2 SDL2_image SDL2_ttf

2) Build bomberman
   - mkdir build && cd build
   - cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../install
   - cmake --build . --target install

3) Run bomberman
   - cd ../install/bin
   - ./bomberman

- CONTROL:
   - Menu selection using SPACE or ENTER
   - To navigate use arrows or WSAD
   - You can add random enemy in random position by pressing ENTER
   - You can exit from level using ESCAPE
   - In level you can place BOMB using SPACE
   - You should kill all enemies and find the door in the bricks by destroying it
   - Enemies can kill you!
   - You have 120 seconds, hurry up!