/**
 * @file    GameControlDelegate.h
 * @brief   针对控制界面widiget的委托实现类
 * @version 1.0
 * @date    2014.7.31
 */
#ifndef __GameControlDelegate_H__
#define __GameControlDelegate_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../comm/Cocos2dxPlatform.h"

class GameLayer;

/// 游戏控制菜单的响应
class GameControlDelegate
{
public:
    GameControlDelegate(GameLayer* gameLayer);
    bool setDelegateWidget(Widget* widget);
protected:
private:
    GameLayer*      _game_layer;
};


#endif /*__GameControlDelegate_H__*/