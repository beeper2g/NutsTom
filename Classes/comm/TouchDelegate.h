/**
 * @file    TouchDelegate.h
 * @brief   屏幕触摸点击委托接口
 * @version 1.0
 * @date    2014.6.7
 */
#ifndef __TouchDelegate_H__
#define __TouchDelegate_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Cocos2dxPlatform.h"

struct TouchDelegate 
{
    virtual bool onTouchAt(const Point& pos) = 0;
    virtual void onTouchMove(const Point& pos){};
    virtual void onTouchEnd(const Point& pos){};
};

#endif /*__TouchDelegate_H__*/