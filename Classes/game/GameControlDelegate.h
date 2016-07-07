/**
 * @file    GameControlDelegate.h
 * @brief   ��Կ��ƽ���widiget��ί��ʵ����
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

/// ��Ϸ���Ʋ˵�����Ӧ
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