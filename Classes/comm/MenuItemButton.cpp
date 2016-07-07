#include "MenuItemButton.h"
#include "SoundManagerCallback.h"


SoundManagerCallback* MenuItemButton::_mgrSoundCallback = nullptr;

MenuItemButton::MenuItemButton()
    :_spriteFrame(NULL), _originScale(1.0f)
{

}

MenuItemButton::~MenuItemButton()
{

}

MenuItemButton* MenuItemButton::create(SpriteFrame* frame, const ccMenuCallback& callback)
{
    MenuItemButton* ret = new MenuItemButton;
    if (ret && ret->initWithSpriteFrame(frame, callback))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return ret;
}

bool MenuItemButton::initWithSpriteFrame(SpriteFrame* frame, const ccMenuCallback& callback)
{
    MenuItem::initWithCallback(callback);
    _spriteFrame = Sprite::createWithSpriteFrame(frame);
    if (_spriteFrame)
    {
        addChild(_spriteFrame);
        _spriteFrame->setAnchorPoint(Point::ZERO);
        setContentSize(_spriteFrame->getContentSize());
    }
    setCascadeColorEnabled(true);
    setCascadeOpacityEnabled(true);
    return true;
}

void MenuItemButton::activate()
{
    if(_enabled)
    {
        this->stopAllActions();
        this->setScale(_originScale);
        MenuItem::activate();
    }
}

void MenuItemButton::selected()
{
    // subclass to change the default action
    if(_enabled)
    {
        MenuItem::selected();

        Action *action = getActionByTag(ZOOMACTION_TAGET);
        if (action)
        {
            this->stopAction(action);
        }
        else
        {
            _originScale = this->getScale();
        }
        if (nullptr!=_mgrSoundCallback)
        {
            _mgrSoundCallback->onButtonClicked();
        }
        Action *zoomAction = ScaleTo::create(0.1f, _originScale * 0.9f);
        zoomAction->setTag(ZOOMACTION_TAGET);
        this->runAction(zoomAction);
    }
}

void MenuItemButton::unselected()
{
    // subclass to change the default action
    if(_enabled)
    {
        MenuItem::unselected();
        this->stopActionByTag(ZOOMACTION_TAGET);
        Action *zoomAction = ScaleTo::create(0.1f, _originScale);
        zoomAction->setTag(ZOOMACTION_TAGET);
        this->runAction(zoomAction);
    }

}

bool MenuItemButton::changeSpriteFrame(SpriteFrame* frame)
{
    CCAssert(NULL!=_spriteFrame, "Before it, must create.");
    _spriteFrame->setSpriteFrame(frame); 
    _spriteFrame->setAnchorPoint(Point::ZERO);
    setContentSize(_spriteFrame->getContentSize());
    return true;
}

void MenuItemButton::setSoundManagerCallback(SoundManagerCallback* callBack)
{
    _mgrSoundCallback = callBack;
}

