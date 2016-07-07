/**
 * @file    BasicScene.h
 * @brief   
 * @version 1.0
 * @author  houguisang@vip.qq.com
 * @date    2014.5.15
 */
#ifndef __BasicScene_H__
#define __BasicScene_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Cocos2dxPlatform.h"

class BasicScene : public Scene
{
public:
    BasicScene();
    virtual ~BasicScene();
    CREATE_FUNC(BasicScene);
    virtual bool init();
protected:
    virtual void switchScene(Scene* scene, bool next=true);
    virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
private:
private:
protected:
    Point       _originPoint;
    Size        _visibleSize;
};

#endif /*__BasicScene_H__*/