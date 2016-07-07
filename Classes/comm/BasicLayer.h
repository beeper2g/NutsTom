/**
 * @file    BasicLayer.h
 * @brief   ͨ�ò�ʵ�ֻ��࣬�ṩһϵ��ͨ�÷���
 * @version 1.0
 * @author  houguisang@vip.qq.com
 * @date    2014.5.15
 */
#ifndef __BasicLayer_H__
#define __BasicLayer_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Cocos2dxPlatform.h"

class BasicLayer : public Layer
{
public:
    BasicLayer();
    virtual ~BasicLayer();
    CREATE_FUNC(BasicLayer);
    virtual bool init();
protected:
    void switchScene(Scene* scene, bool next=true);
private:
protected:
    Point       _originPoint;
    Size        _visibleSize;
};

class BasicLayerColor : public LayerColor
{
public:
    virtual bool init();
protected:
    void switchScene(Scene* scene, bool next=true);
private:
protected:
    Point       _originPoint;
    Size        _visibleSize;
};

#endif /*__BasicLayer_H__*/