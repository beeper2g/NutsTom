/**
 * @file    Cocos2dPlatform.h
 * @brief   平台包含的头文件 
 * @version 1.0
 * @author  houguisang@vip.qq.com
 * @date    2014.5.4
 */
#ifndef __Cocos2dPlatform_H__
#define __Cocos2dPlatform_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "cocos2d.h"
#include "extensions/cocos-ext.h"   // cocos2d/extensions/proj.win32
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"            // cocos2d/cocos/ui/prorj.win32
#include "SimpleAudioEngine.h"

#include <map>
#include <list>
#include <deque>
#include <stack>
#include <vector>
#include <string>

#include <cstdlib>
#include <cstdio>

USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;
using namespace cocostudio;
using namespace CocosDenshion;

#ifndef Max
#   define Max(a,b) (((a) > (b)) ? (a) : (b))
#endif // !Max

#ifndef Min
#   define Min(a,b) (((a) < (b)) ? (a) : (b))
#endif

#define  COUNTARRAY(ary)    sizeof(ary)/sizeof(ary[0])

#define WRITE_BOOL(key, value)      UserDefault::getInstance()->setBoolForKey((key), (value))
#define WRITE_INT(key, value)       UserDefault::getInstance()->setIntegerForKey((key), (value))
#define WRITE_FLOAT(key, value)     UserDefault::getInstance()->setFloatForKey((key), (value))
#define WRITE_DOUBLE(key, value)    UserDefault::getInstance()->setDoubleForKey((key), (value))
#define WRITE_STRING(key, value)    UserDefault::getInstance()->setStringForKey((key), (value))

#define READ_BOOL(key, defValue)    UserDefault::getInstance()->getBoolForKey(key, defValue)
#define READ_INT(key, defValue)     UserDefault::getInstance()->getIntegerForKey(key, defValue)
#define READ_FLOAT(key, defValue)   UserDefault::getInstance()->getFloatForKey(key, defValue)
#define READ_DOUBLE(key, defValue)  UserDefault::getInstance()->getDoubleForKey(key, defValue)
#define READ_STRING(key, defValue)  UserDefault::getInstance()->getStringForKey(key, defValue)


#endif /*__Cocos2dPlatform_H__*/