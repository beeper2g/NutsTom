#include "Pillar.h"
#include "GameControl.h"
#include "../comm/UIHelper.h"
#include "../data/GlobalData.h"

///////////////////////////////////////////////////////////////
// Pillar
///////////////////////////////////////////////////////////////
Pillar::Pillar()
    :_pillarItem(NULL), _item(NULL)
    ,_itemType(IT_NONE)
    ,_item_hited(false)
{

}

Pillar* Pillar::createPillar(bool canCreateItem, bool record)
{
    Pillar* pRet = new Pillar;
    if (pRet && pRet->init(canCreateItem, record))
    {
        pRet->autorelease();
    }
    else
    {
        delete pRet;
        pRet = NULL;
    }
    return pRet;
}

bool Pillar::init(bool canCreateItem, bool record)
{
    bool ret = false;
    do 
    {
        CC_BREAK_IF(!Node::init());
        if (record)
        {
            CC_BREAK_IF(!initPillarWithRecord());
        }
        else
        {
            CC_BREAK_IF(!initPillar(canCreateItem));
        }
        ret = true;
    } while (false);
    return ret;
}

bool Pillar::initPillar(bool canCreateItem)
{
    if (NULL!=_item)
    {
        _item->removeFromParentAndCleanup(true);
        _item = NULL;
    }
    if (NULL!=_pillarItem)
    {
        _pillarItem->removeFromParentAndCleanup(true);
        _pillarItem = NULL;
    }
    _item_hited = false;
    Size contextSize;
    this->setAnchorPoint(Point(0.5f, 0.5f));
    _pillarItem = UIHelper::createSprite(getLedgeName().c_str(), "pillar", UIHelper::FT_PNG);
    _pillarItem->setAnchorPoint(Point(0.0f, 0.0f));
    _pillarItem->setPosition(Point::ZERO);
    Size pillarSize(_pillarItem->getContentSize());
    contextSize = pillarSize;
    addChild(_pillarItem);  

    if (canCreateItem)
    {
        if (CCRANDOM_0_1()<GLOBALDATA()->getCoinRate())
        {
            _itemType = IT_COIN;
            _item = UIHelper::createSprite("Coin", "item");
        }
        else if (CCRANDOM_0_1()<GLOBALDATA()->getClockRate())
        {
            _itemType = IT_TIME;
            _item = UIHelper::createSprite("Time", "item");
        }
        else if (CCRANDOM_0_1()<GLOBALDATA()->getSupperRate())
        {
            _itemType = IT_SUPPER;
            _item = UIHelper::createSprite("Supper", "item");
        }
    }
    
    if (NULL!=_item)
    {
        _item->setAnchorPoint(Point(0.5f, 0.5f));
        Size itemSize(_item->getContentSize());
        _item->setPosition(Point(pillarSize.width/2.0f, pillarSize.height+itemSize.height/2.0f));
        addChild(_item);
    }

    setContentSize(contextSize);
    return true;
}

void Pillar::onHeroStandOn(IGameControl* control)
{
    if (!isVisible())
    {
        return;
    }
    _item_hited = true;
    if (NULL!=control && NULL!=_item && _item->isVisible())
    {
        switch (_itemType)
        {
        case IT_COIN:
            control->onEatCoin(10);
            break;
        case IT_TIME:
            control->onEatTime(2);
            break;
        case IT_SUPPER:
            control->onSupperMode();
            break;
        default:
            break;
        }
    }
    if (NULL!=_item && IT_RECORD!=_itemType)
    {
        _item->setVisible(false);
    }
}

bool Pillar::initPillarWithRecord()
{
    this->removeAllChildrenWithCleanup(true);
    _item = NULL;
    _pillarItem = NULL;

    _item_hited = false;
    Size contextSize;
    this->setAnchorPoint(Point(0.5f, 0.5f));
    _pillarItem = UIHelper::createSprite(getLedgeName().c_str(), "pillar", UIHelper::FT_PNG);
    _pillarItem->setAnchorPoint(Point(0.0f, 0.0f));
    _pillarItem->setPosition(Point::ZERO);
    Size pillarSize(_pillarItem->getContentSize());
    contextSize = pillarSize;
    addChild(_pillarItem);  

    _itemType = IT_RECORD;
    _item = UIHelper::createSprite("S_Record", "item");
    _item->setAnchorPoint(Point(0.5f, 0.5f));
    Size itemSize(_item->getContentSize());
    _item->setPosition(Point(pillarSize.width/2.0f, pillarSize.height+itemSize.height/2.0f));
    addChild(_item);

    setContentSize(contextSize);
    return true;
}

void Pillar::setItemVisible(bool value)
{
    if (NULL==_item || IT_RECORD==_itemType)
    {
        return;
    }
    if (value)
    {
        if (!_item_hited)
        {
            _item->setVisible(true);
        }
    }
    else
    {
        _item->setVisible(false);
    }
}

std::string Pillar::getLedgeName() const
{
    char name[256] = {0};
    long score = GLOBALDATA()->getCurrentScore()/2;
    int nV1 = 0, nV2 = 1;
    if (score >= 20000)
    {
        nV1 = 10;
    }
    else
    {
        nV1 = score / 1000 + 1;
    }
    if (CCRANDOM_0_1()>0.5f)
    {
        nV2 = 2;
    }
    snprintf(name, 255, "ledge%d%d", nV1, nV2);
    return name;
}
