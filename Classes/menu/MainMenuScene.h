/**
 * @file    MainMenuScene.h
 * @brief   游戏操作控制主菜单场景类实现
 * @version 1.0
 * @date    2014.8.3
 */
#ifndef __MainMenuScene_H__
#define __MainMenuScene_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../comm/BasicScene.h"

/// 游戏菜单选择场景类实现
class MainMenuScene : public BasicScene
{
public:
    CREATE_FUNC(MainMenuScene);
    MainMenuScene();
    virtual bool init();
    virtual void onEnter();
protected:
    void onSoundButtonClicked(Ref* sender, TouchEventType type);
    void onShareButtonClicked(Ref* sender, TouchEventType type);
    void onRankButtonClicked(Ref* sender, TouchEventType type);
    void onPlayButtonClicked(Ref* sender, TouchEventType type);
private:
    bool createLogoUI();
    void jumpToNextScene();
    void updateSoundUI();
    void executeEnterAnimation();
    void onEnterAnimationFinish();
    void onPlayBackgroundCallBack();
    void onShareBackgroundCallBack();
private:
    Button*     _sound_button;
    Widget*     _play_button;
    Widget*     _play_background;
    Widget*     _share_button;
    Widget*     _rank_button;
    Widget*     _logo_image;
};


#endif /*__MainMenuScene_H__*/