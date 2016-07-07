/**
 * @file    SoundManager.h
 * @brief   统一游戏声音控制的实现
 * @version 1.0
 * @date    2014.6.9
 */
#ifndef __SoundManager_H__
#define __SoundManager_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../comm/SoundManagerCallback.h"

enum SOUND_TYPE
{
    ST_MAIN_BACKGROUND      = 1,
    ST_PLAY_BACKGROUND,
    ST_SHARE_BACKGROUND,

    ST_HERO_JUMP,
    ST_HERO_DIE,

    ST_BUTTON_CLICEKD,
};

class SoundManager : public SoundManagerCallback
{
public:
    static SoundManager* getInstance();
    void initialize();

    void playSound(SOUND_TYPE type, bool repeated=false);
    void stopSound();

    void resumeBackgroundMusic();
    void pauseBackgroundMusic();

protected:
    virtual void onButtonClicked();
private:
};

#define SOUNDMANAGER()  SoundManager::getInstance()

#endif /*__SoundManager_H__*/