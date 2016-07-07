/**
 * @file    WaitClockCtrl.h
 * @brief   
 * @version 1.0
 * @date    2014.8.10
 */
#ifndef __WaitClockCtrl_H__
#define __WaitClockCtrl_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../comm/Cocos2dxPlatform.h"

class WaittClockCtrl : public Sprite
{
    enum CONTROL_Z_ORDER
    {
        CZO_PROGRESS,
        CZO_CURSOR,
    };
public:
    CREATE_FUNC(WaittClockCtrl);
    virtual bool init();
    void initClock(float duration, std::function<void()>& func);
protected:
private:
};


#endif /*__WaitClockCtrl_H__*/