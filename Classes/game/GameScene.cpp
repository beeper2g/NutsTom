#include "GameScene.h"
#include "GameLayer.h"
#include "../comm/TouchLayer.h"


///////////////////////////////////////////////////////////////
// GameScene
///////////////////////////////////////////////////////////////
bool GameScene::init()
{
    bool ret = false;
    do 
    {
        CC_BREAK_IF(!BasicScene::init());
        CC_BREAK_IF(!createGameLayer());
        ret = true;
    } while (false);
    return ret;
}

bool GameScene::createGameLayer()
{
    _game_layer = GameLayer::create();
    addChild(_game_layer);
    return true;
}
