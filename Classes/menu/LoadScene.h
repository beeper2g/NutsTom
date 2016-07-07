/**
 * @file    LoadScene.h
 * @brief   初始化游戏资源的场景类实现
 * @version 1.0
 * @date    2014.8.3
 */
#ifndef __LoadScene_H__
#define __LoadScene_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../comm/BasicScene.h"

/// 资源加载场景类实现
class LoadScene : public BasicScene
{
    enum LOADING_TAG
    {
        LOADING_TAG_1   = 0,
        LOADING_TAG_2,
        LOADING_TAG_3,

        LOADING_TAG_MAX,
    };
public:
    CREATE_FUNC(LoadScene);
    virtual bool init();
protected:
private:
    bool createLogoUI();
    void jumpToNextScene();
    void playLoadfinishAnimation();
    void onResourceLoadFinish();
    void onCheckLoadResourceFinish(float delta);
private:
    float   _move_y;
};


#endif /*__LoadScene_H__*/