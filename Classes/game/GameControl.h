/**
 * @file    GameControl.h
 * @brief   
 * @version 1.0
 * @date    2014.8.10
 */
#ifndef __GameControl_H__
#define __GameControl_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

struct IGameControl
{
    virtual void onEatCoin(int value) = 0;
    virtual void onEatTime(int value) = 0;
    virtual void onSupperMode() = 0;
};

#endif /*__GameControl_H__*/