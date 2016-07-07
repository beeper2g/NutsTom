/**
 * @file    GameBackground.h
 * @brief   游戏的背景实现
 * @version 1.0
 * @date    2014.7.30
 */
#ifndef __GameBackground_H__
#define __GameBackground_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../comm/Cocos2dxPlatform.h"

/// 游戏中背景实现类
class GameBackground : public Node
{
public:
    GameBackground();
    CREATE_FUNC(GameBackground);
    bool initBackground(const Size& sizeFull, int level=0);
    void updateBackground(const Point& curPos);
protected:
    void onAddImageFinish(Texture2D* texture2D);
    void loadNextMap();
private:
    int     _loaded_map_count;
    Point   _curPos;
    float   _full_height, _full_width;
    Sprite* _last_map;
};


#endif /*__GameBackground_H__*/