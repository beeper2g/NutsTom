#include "LoadScene.h"
#include "ZipUtils.h"
#include "ResourceManager.h"
#include "SceneBuilder.h"
#include "comm/SoundManager.h"
#include "comm/UIHelper.h"
#include "comm/MenuItemButton.h"
#include "data/GlobalData.h"
#include "sdk/ShareMethod.h"

///////////////////////////////////////////////////////////////
// LoadScene
///////////////////////////////////////////////////////////////////////////////
bool LoadScene::init()
{
    bool ret = false;
    do 
    {
        _move_y = 40.0f*Director::getInstance()->getContentScaleFactor();
        // 启动加载界面不允许显示广告
        ShareMethod::showBanner(false);
        // 处理安全
        ZipUtils::setPvrEncryptionKeyPart(0, 0x1d3e8bd1);
        ZipUtils::setPvrEncryptionKeyPart(1, 0x733cd934);
        ZipUtils::setPvrEncryptionKeyPart(2, 0x056fdd39);
        ZipUtils::setPvrEncryptionKeyPart(3, 0x216f7ebd);

        CC_BREAK_IF(!BasicScene::init());
        CC_BREAK_IF(!createLogoUI());

        GLOBALDATA()->initialize();
        schedule(schedule_selector(LoadScene::onCheckLoadResourceFinish), 1);
        MenuItemButton::setSoundManagerCallback(dynamic_cast<SoundManagerCallback*>(SOUNDMANAGER()));
        RESOURCEMANAGER()->loadResource(CC_CALLBACK_0(LoadScene::onResourceLoadFinish, this));
        ret = true;
    } while (false);
    return ret;
}

bool LoadScene::createLogoUI()
{
    // 这里采用同步方式加载纹理
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("loading.plist", "loading.pvr.ccz");
    auto whiteBackLayer = LayerColor::create(Color4B(255, 255, 255, 255));
    addChild(whiteBackLayer);

    Point posCenter(_visibleSize.width/2.0f, _visibleSize.height/2.0f);
    auto loadRadarBack = Sprite::createWithSpriteFrameName("load_radar_back.png");
    loadRadarBack->setTag(LOADING_TAG_1);
    Size sizeLoadRaderBack(loadRadarBack->getContentSize());
    loadRadarBack->setPosition(Point(posCenter.x, posCenter.y-_move_y));
    addChild(loadRadarBack);

    auto loadRadarFront = Sprite::createWithSpriteFrameName("load_radar_front.png");
    loadRadarFront->setTag(LOADING_TAG_2);
    Size sizeLoadRaderFront(loadRadarFront->getContentSize());
    loadRadarFront->setPosition(Point(posCenter.x, posCenter.y-_move_y));
    auto rotateBy = RotateBy::create(0.7f, -360.0f);
    loadRadarFront->runAction(RepeatForever::create(rotateBy));
    addChild(loadRadarFront);

    auto textLoading = Sprite::createWithSpriteFrameName("text_loading1.png");
    textLoading->setTag(LOADING_TAG_3);
    Size sizeTextLoading(textLoading->getContentSize());
    textLoading->setPosition(Point(posCenter.x,
        loadRadarFront->getPositionY()-(sizeLoadRaderFront.height+sizeTextLoading.height)/2.0f-10.0f));
    auto animate = UIHelper::createAnimate("text_loading%d.png", 3, 6.0f, 1);
    textLoading->runAction(RepeatForever::create(animate));
    addChild(textLoading);
    return true;
}

void LoadScene::jumpToNextScene()
{
#ifdef _DEBUG
    switchScene(SceneBuilder::buildScene(ST_GAME_SCENE));
#else
    switchScene(SceneBuilder::buildScene(ST_GAME_SCENE));
#endif // _DEBUG
}

void LoadScene::onResourceLoadFinish()
{
    playLoadfinishAnimation();
}

void LoadScene::onCheckLoadResourceFinish(float delta)
{
    if (!RESOURCEMANAGER()->isResourceLoadFinish())
    {
        return;
    }
}

void LoadScene::playLoadfinishAnimation()
{
    for (int n=LOADING_TAG_1; n<LOADING_TAG_MAX; ++n)
    {
        removeChildByTag(n, true);
    }
    Point posCenter(_visibleSize.width/2.0f, _visibleSize.height/2.0f);
    auto logoFlag = Sprite::createWithSpriteFrameName("logo_flag.png");
    logoFlag->setTag(LOADING_TAG_1);
    Size sizeLogoFlag(logoFlag->getContentSize());
    logoFlag->setPosition(Point(posCenter.x, posCenter.y-_move_y));
    addChild(logoFlag);

    auto textLogo = Sprite::createWithSpriteFrameName("text_logo5.png");
    textLogo->setTag(LOADING_TAG_2);
    Size sizeTextLogo(textLogo->getContentSize());
    textLogo->setPosition(Point(posCenter.x,
        logoFlag->getPositionY()-(sizeLogoFlag.height+sizeTextLogo.height)/2.0f));
    addChild(textLogo);

    float duration = 0.7f;
    float moveY = _move_y;
    auto moveBy = MoveBy::create(duration, Point(0.0f, moveY));
    auto callFunc = CallFunc::create(CC_CALLBACK_0(LoadScene::jumpToNextScene, this));
    auto delayTime = DelayTime::create(0.5f);
    logoFlag->runAction(Sequence::create(moveBy, callFunc, delayTime, NULL));
    moveBy = MoveBy::create(duration, Point(0.0f, moveY));
    auto animate = UIHelper::createAnimate("text_logo%d.png", 5, 14.0f, 1);
    textLogo->runAction(Spawn::createWithTwoActions(moveBy, animate));
}
