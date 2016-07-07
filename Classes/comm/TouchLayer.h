/**
 * @file    TouchLayer.h
 * @brief   ´¥Ãþ²ã
 * @version 1.0
 * @date    2014.6.7
 */
#ifndef __TouchLayer_H__
#define __TouchLayer_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BasicLayer.h"

struct TouchDelegate;

class TouchLayer : public BasicLayer
{
public:
    CREATE_FUNC(TouchLayer);
    virtual void onEnter();
    void setTouchDelegate(TouchDelegate* touchDelegate, bool multiTouch=true);
protected:
    virtual bool onTouchBegan(Touch *touch, Event *unused_event); 
    virtual void onTouchMoved(Touch *touch, Event *unused_event); 
    virtual void onTouchEnded(Touch *touch, Event *unused_event); 
    virtual void onTouchCancelled(Touch *touch, Event *unused_event);

    virtual void onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event);
    virtual void onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event);
    virtual void onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event);
    virtual void onTouchesCancelled(const std::vector<Touch*>&touches, Event *unused_event);
private:
    TouchDelegate*  _touchDelegate;
};

#endif /*__TouchLayer_H__*/