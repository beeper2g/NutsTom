/**
 * @file    UIHelper.h
 * @brief   
 * @version 1.0
 * @author  houguisang@vip.qq.com
 * @date    2014.5.15
 */
#ifndef __UIHelper_H__
#define __UIHelper_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Cocos2dxPlatform.h"

namespace UIHelper
{
Animate* createAnimate(const char* fmt, int count, float fps, int start=0);

enum FILE_TYPE
{
    FT_PNG  = 0,
    FT_JPG,
};
Sprite* createSprite(const char* fileName, const char* path, FILE_TYPE type=FT_PNG);

Widget* fildWidgetByName(Widget* fromWidget, const char* name);
}

#endif /*__UIHelper_H__*/