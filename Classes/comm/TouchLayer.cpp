#include "TouchLayer.h"
#include "TouchDelegate.h"


void TouchLayer::onEnter()
{
    BasicLayer::onEnter();
}

void TouchLayer::setTouchDelegate(TouchDelegate* touchDelegate, bool multiTouch/*=true*/)
{
    _touchDelegate = touchDelegate;
    //_eventDispatcher->removeAllEventListeners();
    if (multiTouch)
    {
        auto listener = EventListenerTouchAllAtOnce::create();
        listener->onTouchesBegan = CC_CALLBACK_2(TouchLayer::onTouchesBegan, this);
        listener->onTouchesMoved = CC_CALLBACK_2(TouchLayer::onTouchesMoved, this);
        listener->onTouchesEnded = CC_CALLBACK_2(TouchLayer::onTouchesEnded, this);
        listener->onTouchesCancelled = CC_CALLBACK_2(TouchLayer::onTouchesCancelled, this);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    }
    else
    {
        auto listener = EventListenerTouchOneByOne::create();
        listener->setSwallowTouches(true);
        listener->onTouchBegan = CC_CALLBACK_2(TouchLayer::onTouchBegan, this);
        listener->onTouchMoved = CC_CALLBACK_2(TouchLayer::onTouchMoved, this);
        listener->onTouchEnded = CC_CALLBACK_2(TouchLayer::onTouchEnded, this);
        listener->onTouchCancelled = CC_CALLBACK_2(TouchLayer::onTouchCancelled, this);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    }
}

bool TouchLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
    if (nullptr != _touchDelegate)
    {
        return _touchDelegate->onTouchAt(touch->getLocation());
    }
    return true;
}

void TouchLayer::onTouchMoved(Touch *touch, Event *unused_event)
{
    if (nullptr != _touchDelegate)
    {
        _touchDelegate->onTouchMove(touch->getLocation());
    }
}

void TouchLayer::onTouchEnded(Touch *touch, Event *unused_event)
{
    if (nullptr != _touchDelegate)
    {
        _touchDelegate->onTouchEnd(touch->getLocation());
    }
}

void TouchLayer::onTouchCancelled(Touch *touch, Event *unused_event)
{
    if (nullptr != _touchDelegate)
    {
        _touchDelegate->onTouchEnd(touch->getLocation());
    }
}

void TouchLayer::onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event)
{
    if (nullptr == _touchDelegate)
    {
        return;
    }
    std::vector<Touch*>::const_iterator iter = touches.begin();
    for (; iter!=touches.end(); ++iter)
    {
        _touchDelegate->onTouchAt((*iter)->getLocation());
    }
}

void TouchLayer::onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event)
{
    if (nullptr == _touchDelegate)
    {
        return;
    }
    std::vector<Touch*>::const_iterator iter = touches.begin();
    for (; iter!=touches.end(); ++iter)
    {
        _touchDelegate->onTouchMove((*iter)->getLocation());
    }
}

void TouchLayer::onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event)
{
    if (nullptr == _touchDelegate)
    {
        return;
    }
    std::vector<Touch*>::const_iterator iter = touches.begin();
    for (; iter!=touches.end(); ++iter)
    {
        _touchDelegate->onTouchEnd((*iter)->getLocation());
    }
}

void TouchLayer::onTouchesCancelled(const std::vector<Touch*>&touches, Event *unused_event)
{
    if (nullptr == _touchDelegate)
    {
        return;
    }
    std::vector<Touch*>::const_iterator iter = touches.begin();
    for (; iter!=touches.end(); ++iter)
    {
        _touchDelegate->onTouchEnd((*iter)->getLocation());
    }
}

