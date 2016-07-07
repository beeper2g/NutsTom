/**
 * @file    Hero.h
 * @brief   游戏中的主角对象类实现
 * @version 1.0
 * @date    2014.7.31
 */
#ifndef __Hero_H__
#define __Hero_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../comm/Cocos2dxPlatform.h"

/// 游戏中的主角精灵类
class Hero : public Sprite
{
    enum HERO_STATUS
    {
        HS_STAND    = 0,
        HS_JUMP,
        HS_DIE,
        HS_RESURGENCE,
    };
public:
    CREATE_FUNC(Hero);
    virtual bool init();

    void stand(std::function<void()>& funcCallback);
    void jump(std::function<void()>& funcCallback);
    void die(std::function<void()>& funcCallback);
    void resurgence(float toPos, std::function<void()>& funcCallback);  // 复活！
    void down(std::function<void()>& funcCallback);
    bool createSupperBar();
    void tobeSupperMan(float duration, std::function<void()>& funcCallback);
protected:
    void tobeNormalMan();
private:
    HERO_STATUS     _hero_status;

    ProgressTimer*  _supper_timer;
    Sprite*         _supper_blod;
};


#endif /*__Hero_H__*/