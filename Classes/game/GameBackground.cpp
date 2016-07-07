#include "GameBackground.h"
#include "../comm/UIHelper.h"
#include "../data/GlobalData.h"


///////////////////////////////////////////////////////////////
// GameBackground
///////////////////////////////////////////////////////////////
GameBackground::GameBackground()
    :_loaded_map_count(0)
    ,_last_map(NULL)
    ,_full_height(0.0f), _full_width(0.0f)
{

}

bool GameBackground::initBackground(const Size& sizeFull, int level)
{
    _full_height = sizeFull.height+sizeFull.width*0.5f;
    _full_width = 0.0f;
    _loaded_map_count = 0;
    loadNextMap();
    return true;
}

void GameBackground::updateBackground(const Point& curPos)
{
    if (_loaded_map_count>=GLOBALDATA()->getBackgroundMapCount())
    {// 已经全部加载完毕
        return;
    }
    if (abs(curPos.x)-abs(_curPos.x)>=70.0f)
    {
        loadNextMap();
        _curPos = curPos;
    }
}

void GameBackground::loadNextMap()
{
    char fileName[128] = {0};
    snprintf(fileName, 127, "%s.jpg", GLOBALDATA()->getBackgroundMap(_loaded_map_count));
    TextureCache* cacheTexture = Director::getInstance()->getTextureCache();
    Texture2D* texture2D = cacheTexture->getTextureForKey(fileName);
    if (NULL==texture2D)
    {
        texture2D = cacheTexture->addImage(fileName);    
        CCLOG("Create file [%s] to texture2D", fileName);
    }
    if (NULL==texture2D)
    {
        CCLOGERROR("Can not load background image [%s].", fileName);
        CCASSERT(false, "Invalidate texture.");
        return;
    }
    Sprite* map = Sprite::createWithTexture(texture2D);
    map->setAnchorPoint(Point::ZERO);
    addChild(map);
    Size mapContext(map->getContentSize());
    float scaleRate = _full_height/mapContext.height;
    map->setScale(scaleRate);
    if (NULL!=_last_map)
    {
        map->setPosition(Point(_full_width, _last_map->getPositionY()));
    }
    else
    {
        map->setPosition(Point::ZERO);
    }
    _full_width += mapContext.width*scaleRate;
    setContentSize(Size(_full_width, _full_height));

    _last_map = map;
    ++_loaded_map_count;
}
