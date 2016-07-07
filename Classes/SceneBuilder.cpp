#include "SceneBuilder.h"
#include "menu/LoadScene.h"
#include "menu/MainMenuScene.h"
#include "game/GameScene.h"

BasicScene* SceneBuilder::buildScene(SCENE_TYPE type)
{
    BasicScene* scene = nullptr;
    switch (type)
    {
    case ST_LOAD_SCENE:
        scene = dynamic_cast<BasicScene*>(LoadScene::create());
        break;
    case ST_MAINMENU_SCENE:
        scene = dynamic_cast<BasicScene*>(MainMenuScene::create());
        break;
    case ST_GAME_SCENE:
        scene = dynamic_cast<BasicScene*>(GameScene::create());
        break;
    default:
        break;
    }
    CCASSERT(nullptr!=scene, "All game scene must be derived from BasiceScene.");
    return scene;
}
