#include "BasicScene.h"
#include "CommCocos2dxFunc.h"

BasicScene::BasicScene()
{

}

BasicScene::~BasicScene()
{

}

bool BasicScene::init()
{
    bool ret = false;
    do 
    {
        CC_BREAK_IF(!Scene::init());
        _originPoint = Director::getInstance()->getVisibleOrigin();
        _visibleSize = Director::getInstance()->getVisibleSize();

        auto listenerkeyPad = EventListenerKeyboard::create();
        listenerkeyPad->onKeyReleased = CC_CALLBACK_2(BasicScene::onKeyReleased, this);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listenerkeyPad, this);

        ret = true;
    } while (false);
    return ret;
}

void BasicScene::switchScene(Scene* scene, bool next/*=true*/)
{
    CommCocos2dxFunc::switchSceneSpliteCols(scene, next);
}

void BasicScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    switch (keyCode)
    {
    case EventKeyboard::KeyCode::KEY_BACKSPACE:
    case EventKeyboard::KeyCode::KEY_MENU:
        Director::getInstance()->end();
        break;
    default:
        break;
    }
}
