#include "BasicLayer.h"
#include "CommCocos2dxFunc.h"

BasicLayer::BasicLayer()
{

}

BasicLayer::~BasicLayer()
{

}

bool BasicLayer::init()
{
    bool ret = false;
    do 
    {
        CC_BREAK_IF(!Layer::init());
        _originPoint = Director::getInstance()->getVisibleOrigin();
        _visibleSize = Director::getInstance()->getVisibleSize();


        ret = true;
    } while (false);
    return ret;
}

void BasicLayer::switchScene(Scene* scene, bool next/*=true*/)
{
    CommCocos2dxFunc::switchSceneSpliteCols(scene, next);
}

///////////////////////////////////////////////////////////////
// BasicLayerColor
///////////////////////////////////////////////////////////////
bool BasicLayerColor::init()
{
    bool ret = false;
    do 
    {
        CC_BREAK_IF(!LayerColor::init());
        _originPoint = Director::getInstance()->getVisibleOrigin();
        _visibleSize = Director::getInstance()->getVisibleSize();


        ret = true;
    } while (false);
    return ret;
}

void BasicLayerColor::switchScene(Scene* scene, bool next/*=true*/)
{
    CommCocos2dxFunc::switchSceneMoveInLR(scene, next);
}
