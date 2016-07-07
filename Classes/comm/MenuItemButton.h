/**
 * @file    MenuItemButton.h
 * @brief   
 * @version 1.0
 * @date    2014.6.1
 */
#ifndef __MenuItemButton_H__
#define __MenuItemButton_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Cocos2dxPlatform.h"

struct SoundManagerCallback;

class MenuItemButton : public MenuItem
{
    enum
    {
        ZOOMACTION_TAGET    = 1,
    };
public:
    MenuItemButton();
    virtual ~MenuItemButton();
    static void setSoundManagerCallback(SoundManagerCallback* callBack);
    static MenuItemButton* create(SpriteFrame* frame, const ccMenuCallback& callback);
    bool initWithSpriteFrame(SpriteFrame* frame, const ccMenuCallback& callback);
    bool changeSpriteFrame(SpriteFrame* frame);

    virtual void activate();
    virtual void selected();
    virtual void unselected();
protected:
private:
    Sprite*     _spriteFrame;
    float       _originScale;

private:
    static SoundManagerCallback*    _mgrSoundCallback;
};


#endif /*__MenuItemButton_H__*/