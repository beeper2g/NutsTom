#include "WaitClockCtrl.h"
#include "../comm/UIHelper.h"


bool WaittClockCtrl::init()
{
    bool ret = false;
    do 
    {
        CC_BREAK_IF(!initWithSpriteFrameName("popup_timer.png"));
        setAnchorPoint(Point(0.5f, 0.5f));
        ret = true;
    } while (false);
    return ret;
}

void WaittClockCtrl::initClock(float duration, std::function<void()>& func)
{
    removeAllChildrenWithCleanup(true);
    Size contextSize(this->getContentSize());

    auto procTo = ProgressTo::create(duration, 100.0f);
    auto procTimer = ProgressTimer::create(UIHelper::createSprite("popup_bk_pie", "item"));
    procTimer->setAnchorPoint(Point(0.5f, 0.5f));
    procTimer->setType(ProgressTimer::Type::RADIAL);
    procTimer->setPosition(Point(contextSize.width/2.0f, contextSize.height/2.0f));
    addChild(procTimer, CZO_PROGRESS);

    Sprite* cursor = UIHelper::createSprite("popup_timer_cursor", "item");
    cursor->setAnchorPoint(Point(0.5f, 0.5f));
    cursor->setPosition(Point::ZERO);
    cursor->setPosition(Point(contextSize.width/2.0f, contextSize.height/2.0f));
    addChild(cursor, CZO_CURSOR);
    auto rotateBy = RotateBy::create(duration, 360.0f);
    auto callFunc = CallFunc::create(func);

    procTimer->runAction(procTo);
    cursor->runAction(Sequence::createWithTwoActions(rotateBy, callFunc));
}
