/**
 * @file    SceneBuilder.h
 * @brief   ��������������ʵ��
 * @version 1.0
 * @date    2014.6.21
 */
#ifndef __SceneBuilder_H__
#define __SceneBuilder_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "comm/BasicScene.h"

enum SCENE_TYPE
{
    ST_LOAD_SCENE,
    ST_MAINMENU_SCENE,
    ST_GAME_SCENE,
};

/// ��Ϸ����������
class SceneBuilder
{
public:
    static BasicScene* buildScene(SCENE_TYPE type);
protected:
private:
};

#endif /*__SceneBuilder_H__*/