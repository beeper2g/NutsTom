#include "MainMenuScene.h"

#include "../comm/SoundManager.h"
#include "../comm/MenuItemButton.h"
#include "../SceneBuilder.h"
#include "../data/GlobalData.h"
#include "../sdk/ShareMethod.h"

///////////////////////////////////////////////////////////////
// MainMenuScene
///////////////////////////////////////////////////////////////
MainMenuScene::MainMenuScene()
    :_sound_button(NULL)
    ,_play_button(NULL), _play_background(NULL)
    ,_share_button(NULL), _rank_button(NULL)
    ,_logo_image(NULL)
{

}

bool MainMenuScene::init()
{
    bool ret = false;
    do 
    {
        GLOBALDATA()->initialize();
        GLOBALDATA()->setEnableSceneSound(false);
        CC_BREAK_IF(!BasicScene::init());
        ShareMethod::showBanner(false);
        ret = true;
    } while (false);
    return ret;
}

bool MainMenuScene::createLogoUI()
{
    Sprite* background = Sprite::createWithSpriteFrameName("main_bg.png");
    GLView* glView = Director::getInstance()->getOpenGLView();
    background->setScaleX(_visibleSize.width/background->getContentSize().width);
    background->setScaleY(_visibleSize.height/background->getContentSize().height);
    background->setPosition(Point(_visibleSize.width/2.0f, _visibleSize.height/2.0f));
    addChild(background, 0);

    Widget* widget = GUIReader::getInstance()->widgetFromJsonFile("GameMain.ExportJson");
    addChild(widget, 1);
    _logo_image = widget->getChildByName("imgGameLogo");
    Button* button = (Button*)widget->getChildByName("btnSound");
    _sound_button = button;
    button->addTouchEventListener(this, toucheventselector(MainMenuScene::onSoundButtonClicked));
    _share_button = widget->getChildByName("btnShare");
    button = (Button*)_share_button;
    if (LanguageType::CHINESE==Application::getInstance()->getCurrentLanguage())
    {// 如果是中国区则需要改成微信
        button->loadTextureNormal("weixin_share.png", UI_TEX_TYPE_PLIST);
    }
    button->addTouchEventListener(this, toucheventselector(MainMenuScene::onShareButtonClicked));
    _rank_button = widget->getChildByName("btnRank");
    button = (Button*)_rank_button;
    button->addTouchEventListener(this, toucheventselector(MainMenuScene::onRankButtonClicked));

    _play_background = widget->getChildByName("imgGamePlayBg");
    _play_button = widget->getChildByName("btnGamePlay");
    _play_button->setScale(0.0f);
    button = (Button*)_play_button;
    button->addTouchEventListener(this, toucheventselector(MainMenuScene::onPlayButtonClicked));

    Widget* tmpWidget = widget->getChildByName("imgCoindFrame");
    Text* label = (Text*)tmpWidget->getChildByName("labCoin");
    char text[128] = {0};
    snprintf(text, 127, "%d", GLOBALDATA()->getTotalCoin());
    label->setText(text);

    updateSoundUI();
    executeEnterAnimation();
    return true;
}

void MainMenuScene::onEnter()
{
    BasicScene::onEnter();
    SOUNDMANAGER()->initialize();
    MenuItemButton::setSoundManagerCallback(dynamic_cast<SoundManagerCallback*>(SOUNDMANAGER()));

    GLOBALDATA()->loadFromFile();
    createLogoUI();
}

void MainMenuScene::jumpToNextScene()
{
    switchScene(SceneBuilder::buildScene(ST_GAME_SCENE));
}

void MainMenuScene::onSoundButtonClicked(Ref* sender, TouchEventType type)
{
    if (TOUCH_EVENT_ENDED==type)
    {
        GLOBALDATA()->setEnableMute(!GLOBALDATA()->getEnableMute());
        GLOBALDATA()->saveToFile();
        updateSoundUI();
    }
}

void MainMenuScene::onShareButtonClicked(Ref* sender, TouchEventType type)
{
    if (TOUCH_EVENT_ENDED==type)
    {
        std::string text = GLOBALDATA()->getShareFormat();
        if (LanguageType::CHINESE==Application::getInstance()->getCurrentLanguage())
        {
            ShareMethod::shareWithWeChat(text.c_str());
        }
        else
        {
            ShareMethod::shareWithFacebook(text.c_str());
        }
    }
}

void MainMenuScene::onRankButtonClicked(Ref* sender, TouchEventType type)
{
    if (TOUCH_EVENT_ENDED==type)
    {
        ShareMethod::showGameCenter();
    }
}

void MainMenuScene::onPlayButtonClicked(Ref* sender, TouchEventType type)
{
    if (TOUCH_EVENT_ENDED==type && GLOBALDATA()->isMapResourceLoaded())
    {
        switchScene(SceneBuilder::buildScene(ST_GAME_SCENE));
    }
}

void MainMenuScene::updateSoundUI()
{
    if (GLOBALDATA()->getEnableMute())
    {
        _sound_button->loadTextureNormal("button_sound_normal.png", ui::UI_TEX_TYPE_PLIST);
        //SOUNDMANAGER()->playSound(ST_MAIN_BACKGROUND, true);
    }
    else
    {
        _sound_button->loadTextureNormal("button_sound_pressed.png", ui::UI_TEX_TYPE_PLIST);
        //SOUNDMANAGER()->stopSound();
    }
}

void MainMenuScene::onEnterAnimationFinish()
{
    auto rotateBy = RotateBy::create(2.0f, 360.0f);
    _play_background->runAction(RepeatForever::create(rotateBy));
}

void MainMenuScene::executeEnterAnimation()
{
    Point posFrom, posTo;
    float duration = 0.8f;

    posFrom = _play_background->getPosition();
    posTo = posFrom;
    posFrom.y = 0.0f;
    _play_background->setPosition(posFrom);
    auto moveTo = MoveTo::create(duration, posTo);
    auto easeInMoveTo = EaseBounceOut::create(moveTo);
    auto playCallBack = CallFunc::create(CC_CALLBACK_0(MainMenuScene::onPlayBackgroundCallBack, this));
    _play_background->runAction(Sequence::createWithTwoActions(playCallBack, easeInMoveTo));

    posFrom = _logo_image->getPosition();
    posTo = posFrom;
    posFrom.y = _visibleSize.height;
    _logo_image->setPosition(posFrom);
    moveTo = MoveTo::create(duration, posTo);
    easeInMoveTo = EaseBounceOut::create(moveTo);
    _logo_image->runAction(easeInMoveTo);

    posFrom = _share_button->getPosition();
    posTo = posFrom;
    posFrom.x = 0.0f - _share_button->getContentSize().width;
    _share_button->setPosition(posFrom);
    moveTo = MoveTo::create(duration, posTo);
    easeInMoveTo = EaseBounceOut::create(moveTo);
    auto shareCallBack = CallFunc::create(CC_CALLBACK_0(MainMenuScene::onShareBackgroundCallBack, this));
    _share_button->runAction(
        Sequence::create(DelayTime::create(duration), shareCallBack, easeInMoveTo, NULL));

    posFrom = _rank_button->getPosition();
    posTo = posFrom;
    posFrom.x = _visibleSize.width + _rank_button->getContentSize().width;
    _rank_button->setPosition(posFrom);
    moveTo = MoveTo::create(duration, posTo);
    easeInMoveTo = EaseBounceOut::create(moveTo);
    _rank_button->runAction(Sequence::createWithTwoActions(
        DelayTime::create(duration), easeInMoveTo));

    auto scaleTo = ScaleTo::create(duration, 1.0f);
    auto easeInScaleTo = EaseBounceOut::create(scaleTo);
    _play_button->runAction(Sequence::createWithTwoActions(
        DelayTime::create(duration), easeInScaleTo));
}

void MainMenuScene::onPlayBackgroundCallBack()
{
    SOUNDMANAGER()->playSound(ST_PLAY_BACKGROUND);
}

void MainMenuScene::onShareBackgroundCallBack()
{
    SOUNDMANAGER()->playSound(ST_SHARE_BACKGROUND);
}
