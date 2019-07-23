# SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

find_package(SDL2_TTF REQUIRED)
include_directories(${SDL2_TTF_INCLUDE_DIR})

find_package(SDL2_IMAGE REQUIRED)
include_directories(${SDL2_IMAGE_INCLUDE_DIR})

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Sources
set(
    SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Game.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Animation.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Scenes/Scene.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Scenes/MenuScene.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Scenes/LevelScene.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Scenes/GameOverScene.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Scenes/StageScene.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Managers/SceneManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Managers/AssetManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Entities/Object.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Entities/Text.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Entities/Sprite.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Entities/Creature.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Entities/Enemy.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Entities/Player.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Util/Pathfinding.cpp
)

add_executable(${PROJECT_NAME}
    ${SOURCES}
)

target_link_libraries(${PROJECT_NAME}
    ${SDL2_LIBRARY}
    ${SDL2_TTF_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES}
)

# Install 
install(
    TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)

# Resources
install(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../assets
    DESTINATION bin
    OPTIONAL)
