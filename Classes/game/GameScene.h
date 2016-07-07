/**
 * @file    GameScene.h
 * @brief   ��Ϸ��������ʵ��
 * @version 1.0
 * @date    2014.7.30
 */
#ifndef __GameScene_H__
#define __GameScene_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../comm/BasicScene.h"

class GameLayer;

/// ��Ϸ������ʵ����
class GameScene : public BasicScene
{
public:
    CREATE_FUNC(GameScene);
    virtual bool init();
    bool createGameLayer();
protected:
private:
    GameLayer*          _game_layer;
};


#endif /*__GameScene_H__*/