# SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

find_package(SDL2_TTF REQUIRED)
include_directories(${SDL2_TTF_INCLUDE_DIR})

find_package(SDL2_IMAGE REQUIRED)
include_directories(${SDL2_IMAGE_INCLUDE_DIR})

find_package(SDL2_MIXER REQUIRED)
include_directories(${SDL2_MIXER_INCLUDE_DIR})

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
    ${CMAKE_CURRENT_SOURCE_DIR}/Entities/Music.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Entities/Sound.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Util/Pathfinding.cpp
)

# MacOS bundle parameters
if (CMAKE_MACOSX_BUNDLE)
    set(MACOSX_BUNDLE_BUNDLE_NAME ${PROJECT_NAME})
    set(MACOSX_BUNDLE_GUI_IDENTIFIER "io.github.ibardinov.${PROJECT_NAME}")
    set(MACOSX_BUNDLE_INFO_STRING "Super Arcade Bang Bang")
    set(MACOSX_BUNDLE_ICON_FILE "icon.icns")
    set(MACOSX_BUNDLE_LONG_VERSION_STRING ${PROJECT_VERSION})
    set(MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION})
    set(MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION})
    set(MACOSX_BUNDLE_COPYRIGHT "Ilia Bardinov (c) 2019")
    set(APP_ICON ${CMAKE_CURRENT_SOURCE_DIR}/../icons/icon.icns)
    set_source_files_properties(${APP_ICON} PROPERTIES
       MACOSX_PACKAGE_LOCATION "Resources")
endif()

add_executable(${PROJECT_NAME} ${APP_ICON}
    ${SOURCES}
)

target_link_libraries(
    ${PROJECT_NAME}
    ${SDL2_LIBRARY}
    ${SDL2_TTF_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES}
    ${SDL2_MIXER_LIBRARY}
)

# Install 
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION .
    BUNDLE DESTINATION .
)
# Resources
if (CMAKE_MACOSX_BUNDLE)
    install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../assets DESTINATION ${PROJECT_NAME}.app/Contents/Resources )
else(CMAKE_MACOSX_BUNDLE)
    install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../assets DESTINATION . )
endif(CMAKE_MACOSX_BUNDLE)

# fix dylib
if (CMAKE_MACOSX_BUNDLE)
    install(CODE "include(BundleUtilities)
        fixup_bundle(\"${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}.app\" \"\" \"${CMAKE_BINARY_DIR}\")")
endif()
