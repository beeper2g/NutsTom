/**
 * @file    UIDebug.h
 * @brief   
 * @version 1.0
 * @author  houguisang@vip.qq.com
 * @date    2014.5.15
 */
#ifndef __UIDebug_H__
#define __UIDebug_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Cocos2dxPlatform.h"

namespace UIDebug
{
void drawNodeRect(Node* node, const Color4F& color=Color4F(1.0f, 0.0f, 0.0f, 1.0f), int tag_id=99999);
void drawNodeRectAndAnchorPoint(Node* node, const Color4F& color=Color4F(0.0f, 1.0f, 0.0f, 1.0f), int tag_id=99999);
}

#endif /*__UIDebug_H__*/