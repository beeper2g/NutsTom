/**
 * @file    CommCocos2dxFunc.h
 * @brief   
 * @version 1.0
 * @date    2014.7.27
 */
#ifndef __CommCocos2dxFunc_H__
#define __CommCocos2dxFunc_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Cocos2dxPlatform.h"

namespace CommCocos2dxFunc
{
    void switchSceneMoveInLR(Scene* scene, bool next=true, float duration=0.3f);
    void switchSceneMoveInTB(Scene* scene, bool next=true, float duration=0.3f);
    void switchSceneSpliteRows(Scene* scene, bool next=true, float duration=0.3f);
    void switchSceneSpliteCols(Scene* scene, bool next=true, float duration=0.3f);
}

#endif /*__CommCocos2dxFunc_H__*/