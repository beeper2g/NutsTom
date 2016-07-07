/**
 * @file    Pillar.h
 * @brief   游戏中的柱子站台
 * @version 1.0
 * @date    2014.8.9
 */
#ifndef __Pillar_H__
#define __Pillar_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../comm/Cocos2dxPlatform.h"

struct IGameControl;

class Pillar : public Node
{
    enum ITEM_TYPE
    {
        IT_NONE     = 0,
        IT_COIN,
        IT_TIME,
        IT_SUPPER,
        IT_RECORD,
    };
public:
    Pillar();
    static Pillar* createPillar(bool canCreateItem=true, bool record=false);

    bool initPillar(bool canCreateItem=true);
    bool initPillarWithRecord();
    void onHeroStandOn(IGameControl* control);
    void setItemVisible(bool value);
protected:
    bool init(bool canCreateItem, bool record);
    std::string getLedgeName() const;
private:
    Sprite* _pillarItem;
    Sprite* _item;
    bool    _item_hited;
    ITEM_TYPE   _itemType;
};


#endif /*__Pillar_H__*/