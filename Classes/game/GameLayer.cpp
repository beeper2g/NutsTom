#include "GameLayer.h"
#include "../comm/UIHelper.h"
#include "../data/GlobalData.h"
#include "../comm/Utility.h"
#include "../sdk/ShareMethod.h"
#include "../comm/SoundManager.h"
#include "GameBackground.h"
#include "Hero.h"
#include "Pillar.h"
#include "GameParam.h"
#include "WaitClockCtrl.h"

///////////////////////////////////////////////////////////////
// GameLayer
///////////////////////////////////////////////////////////////
GameLayer::GameLayer()
    :_pillar_start_y_pos(-1.0f)
    ,_in_action(false)
    ,_rotating(false)
    ,_reportWidget(NULL)
    ,_btnJump1(NULL)
    ,_btnJump2(NULL)
    ,_btnJump3(NULL)
{

}

bool GameLayer::init()
{
    bool ret = false;
    do 
    {
        GLOBALDATA()->setEnableSceneSound(true);
        CC_BREAK_IF(!BasicLayer::init());
        CC_BREAK_IF(!createBackground());
        CC_BREAK_IF(!createControl());

        scheduleUpdate();
        startGame();
        ret = true;
    } while (false);
    return ret;
}

bool GameLayer::createBackground()
{
    _bk_cur_pos = Point(0.0f, -370.0f);
    _background = GameBackground::create();
    _background->initBackground(_visibleSize, 0);
    _background->setRotation(-30.0f);
    _background->setPosition(_bk_cur_pos);
    addChild(_background, BACKANIMATION_Z);
    return true;
}

void GameLayer::update(float delta)
{
    if (GS_GAME_RUN == _game_status)
    {
        float totalDelta = GLOBALDATA()->getTotalDelta();
        totalDelta -= delta;
        if (totalDelta<0.0f)
        {
            totalDelta = 0.0f;
            _game_status = GS_GAME_OVER;
            GLOBALDATA()->setTotalDelta(totalDelta);
            onGameOver();
            return;
        }
        if (GLOBALDATA()->isInSupperMode())
        {
            GLOBALDATA()->updateSupperTime(delta);
            switchModeButton(true);
        }
        else
        {
            GLOBALDATA()->setTotalDelta(totalDelta);
            setLeaveTime(totalDelta);
            switchModeButton(false);
        }
        createBackgroundAnimation();
    }
}

bool GameLayer::createBackgroundAnimation()
{
    if (CCRANDOM_0_1()>0.0005f)
    {
        return true;
    }
    long score = GLOBALDATA()->getCurrentScore();
    Sprite* bkSprite = NULL;
    if (score <= 1600)
    {
        bkSprite = UIHelper::createSprite("S_Birdie01", "role");
        bkSprite->runAction(RepeatForever::create(UIHelper::createAnimate("S_Birdie%02d.png", 3, 4, 1)));
    }
    else if (score < 3200)
    {
        bkSprite = UIHelper::createSprite("S_Heli01", "role");
        bkSprite->runAction(RepeatForever::create(UIHelper::createAnimate("S_Heli%02d.png", 4, 4, 1)));
    }
    else if (score < 5000)
    {
        bkSprite = UIHelper::createSprite("S_Plane", "role");
    }
    else
    {
        bkSprite = UIHelper::createSprite("S_Comet", "role");
    }
    if (NULL!=bkSprite)
    {
        addChild(bkSprite, BACKANIMATION_Z);
        bkSprite->setPosition(Point(_visibleSize.width+bkSprite->getContentSize().width,
                                    CCRANDOM_0_1()*_visibleSize.height));
        ccBezierConfig bezier;  
        bezier.controlPoint_1 = Point(CCRANDOM_0_1()*_visibleSize.width+bkSprite->getContentSize().width, _visibleSize.height/2);  
        bezier.controlPoint_2 = Point(CCRANDOM_0_1()*_visibleSize.width+bkSprite->getContentSize().width, _visibleSize.height/2);  
        bezier.endPosition = Point(-1.0f*bkSprite->getContentSize().width, CCRANDOM_0_1()*_visibleSize.height); 

        BezierTo* bezierTo = BezierTo::create(2.0f+CCRANDOM_0_1(), bezier);
        RemoveSelf* removeSelf = RemoveSelf::create(true);
        bkSprite->runAction(Sequence::createWithTwoActions(bezierTo, removeSelf));
    }
    return true;
}

bool GameLayer::createStartPillars()
{
    _last_pillar_pos_x = 0.0f;
    _last_pillar_pos_y = -100.0f;
    _space = 60.0f;
    // 创建开始3根柱子
    for (int n=0; n<3; ++n)
    {
        Pillar* ledge = createPillar(false);
        _pillars.push_back(ledge);
        ledge->setPosition(Point(_last_pillar_pos_x, _last_pillar_pos_y));
        if (0==n)
        {
            _pillar_width = ledge->getContentSize().width;
            _pillar_height = ledge->getContentSize().height;
        }
        _last_pillar_pos_x = _last_pillar_pos_x;
        _last_pillar_pos_x += _pillar_width;
        _last_pillar_pos_y += _space;
    }
    _hero_pos_x = _last_pillar_pos_x-_pillar_width;
    _hero_pos_y_base = _last_pillar_pos_y + _pillar_height/2.0f - _space;
    createPillarToMap();
    return true;
}

bool GameLayer::createControl()
{
    Widget* widget = GUIReader::getInstance()->widgetFromJsonFile("GameControl.ExportJson");
    addChild(widget, CONTROL_Z);
    Utility::forEach(_pillars, std::bind(&Pillar::setItemVisible, std::placeholders::_1, false));

    Button* button = (Button*)widget->getChildByName("btnSound");
    _sound_button = button;
    button->addTouchEventListener(this, toucheventselector(GameLayer::onSoundButtonClicked));
    button = (Button*)widget->getChildByName("btnRestart");
    button->addTouchEventListener(this, toucheventselector(GameLayer::onRestartButtonClicked));
    _btnJump1 = (Button*)widget->getChildByName("btnJump1");
    _btnJump1->addTouchEventListener(this, toucheventselector(GameLayer::onJump1ButtonClicked));
    _btnJump2 = (Button*)widget->getChildByName("btnJump2");
    _btnJump2->addTouchEventListener(this, toucheventselector(GameLayer::onJump2ButtonClicked));
    _btnJump3 = (Button*)widget->getChildByName("btnJump3");
    _btnJump3->addTouchEventListener(this, toucheventselector(GameLayer::onJump1ButtonClicked));

    Widget* tmpWidget = widget->getChildByName("imgHighScore");
    _high_score = (Text*)tmpWidget->getChildByName("labHighScore");
    tmpWidget = widget->getChildByName("imgDistance");
    _distance_score = (Text*)tmpWidget->getChildByName("labDistanceScore");
    tmpWidget = widget->getChildByName("imgTimeFrame");
    _leave_time = (Text*)tmpWidget->getChildByName("labLeaveTime");
    _leave_time_red = (Text*)tmpWidget->getChildByName("labLeaveTimeRed");
    _clock_flag = (ImageView*)tmpWidget->getChildByName("imgClock");

    updateSoundUI();
    return true;
}

void GameLayer::onSoundButtonClicked(Ref* sender, TouchEventType type)
{
    if (TOUCH_EVENT_ENDED==type)
    {
        GLOBALDATA()->setEnableMute(!GLOBALDATA()->getEnableMute());
        GLOBALDATA()->saveToFile();
        updateSoundUI();
    }
}

void GameLayer::onRestartButtonClicked(Ref* sender, TouchEventType type)
{
    if (TOUCH_EVENT_ENDED == type)
    {
        SOUNDMANAGER()->playSound(ST_BUTTON_CLICEKD);
        cleanGameElement();
        startGame();
    }
}

void GameLayer::onJump1ButtonClicked(Ref* sender, TouchEventType type)
{
    if (TOUCH_EVENT_ENDED == type)
    {
        moveScene(1);
    }
}

void GameLayer::onJump2ButtonClicked(Ref* sender, TouchEventType type)
{
    if (TOUCH_EVENT_ENDED == type)
    {
        moveScene(2);
    }
}

void GameLayer::createPillarToMap()
{
    srand(time(NULL));
    for (;;)
    {
        bool record = ((_cur_distance+MOVE_DISTANCE_UNIT)==GLOBALDATA()->getHighScore());
        if (!record && !GLOBALDATA()->isInSupperMode() && ((rand()%2) != 0))
        {
            _last_pillar_pos_x += _pillar_width;
            _last_pillar_pos_y += _space;
            _cur_distance += MOVE_DISTANCE_UNIT;
        }
        record = ((_cur_distance+MOVE_DISTANCE_UNIT)==GLOBALDATA()->getHighScore());
        Pillar* ledge = createPillar(true, record);
        _pillars.push_back(ledge);

        ledge->setPosition(Point(_last_pillar_pos_x, _last_pillar_pos_y));
        _last_pillar_pos_x += _pillar_width;
        _last_pillar_pos_y += _space;
        _cur_distance += MOVE_DISTANCE_UNIT;

        if (_last_pillar_pos_x>=(_visibleSize.width*2.0f))
        {
            break;
        }
    }
}

bool GameLayer::createHero()
{
    _hero = Hero::create();
    _hero_pos_y = _hero_pos_y_base+_hero->getContentSize().height/3.0f;
    _hero->setPosition(Point(_hero_pos_x, _hero_pos_y));
    std::function<void()> func = std::bind(&GameLayer::onStandActionFinish, this);
    _hero->stand(func);
    addChild(_hero, HERO_Z);
    return true;
}

void GameLayer::moveScene(int unit)
{
    if (_in_action || GS_GAME_OVER==_game_status)
    {
        return;
    }
    if (GS_GAME_READY==_game_status)
    {
        _game_status = GS_GAME_RUN;
    }
    _in_action = true;
    if (unit<1 || unit>2)
    {
        unit = 1;
    }
    GLOBALDATA()->setCurrentScore(GLOBALDATA()->getCurrentScore()+unit * MOVE_DISTANCE_UNIT);
    char buf[128] = {0};
    snprintf(buf, 127, "%dm", GLOBALDATA()->getCurrentScore());
    _distance_score->setText(buf);
    movePillars(unit, HERO_JUMP_FULL_TIME);
    moveBackground(unit*MOVE_DISTANCE_UNIT);
    std::function<void()> func = std::bind(&GameLayer::onJumpActionFinish, this);
    _hero->jump(func);
}

void GameLayer::onStandActionFinish()
{
    Pillar* pillarHit = findHitPillar();
    if (NULL!=pillarHit)
    {
        pillarHit->onHeroStandOn(dynamic_cast<IGameControl*>(this));
    }
    _in_action = false;
}

void GameLayer::onJumpActionFinish()
{
    Pillar* pillarHit = findHitPillar();
    if (NULL!=pillarHit)
    {
        std::function<void()> func = std::bind(&GameLayer::onStandActionFinish, this);
        _hero->stand(func);
        pillarHit->onHeroStandOn(dynamic_cast<IGameControl*>(this));
    }
    else
    {
        std::function<void()> func = std::bind(&GameLayer::onDieActionFinish, this);
        _hero->die(func);
    }
}

void GameLayer::onDieActionFinish()
{
    std::function<void()> func = std::bind(&GameLayer::onResurgenceActionFinish, this);
    _hero->resurgence(_hero_pos_y, func);
}

void GameLayer::onResurgenceActionFinish()
{
    std::function<void()> func = std::bind(&GameLayer::onDownActionFinish, this);
    _hero->down(func);

    GLOBALDATA()->setCurrentScore(GLOBALDATA()->getCurrentScore()+2);
    char buf[128] = {0};
    snprintf(buf, 127, "%dm", GLOBALDATA()->getCurrentScore());
    _distance_score->setText(buf);

    movePillars(1, HERO_JUMP_DOWN_TIME);
}

void GameLayer::onDownActionFinish()
{
    std::function<void()> func = std::bind(&GameLayer::onStandActionFinish, this);
    _hero->stand(func);
}

void GameLayer::movePillars(int unit, float duration)
{
    float moveSpaceX = unit*_pillar_width;
    float moveSpaceY = unit*_space;
    PillarList tmpPillars;
    tmpPillars.swap(_pillars);
    PillarList::iterator iter = tmpPillars.begin();
    for (; iter!=tmpPillars.end(); ++iter)
    {
        Pillar* pillar = *iter;
        Point toPos(pillar->getPositionX()-moveSpaceX, pillar->getPositionY()-moveSpaceY);
        if ((toPos.x+_pillar_width) < 0.0f)
        {
            destroyPillar(pillar);
        }
        else
        {
            _pillars.push_back(pillar);
            MoveTo* moveTo = MoveTo::create(duration, toPos);
            pillar->runAction(moveTo);
        }
    }
    _last_pillar_pos_x -= moveSpaceX;
    _last_pillar_pos_y -= moveSpaceY;
    if (_last_pillar_pos_x < (_visibleSize.width+_pillar_width*2.0f))
    {
        createPillarToMap();
    }
}

void GameLayer::setLeaveTime(float leaveTime)
{
    if (leaveTime>5.0f)
    {
        if (!_leave_time->isVisible())
        {
            _leave_time->setVisible(true);
        }
        if (_leave_time_red->isVisible())
        {
            _leave_time_red->setVisible(false);
        }
        if (_rotating)
        {
            _rotating = false;
            _clock_flag->stopAllActions();
            _clock_flag->setRotation(0.0f);
        }
    }
    else
    {
        if (_leave_time->isVisible())
        {
            _leave_time->setVisible(false);
        }
        if (!_leave_time_red->isVisible())
        {
            _leave_time_red->setVisible(true);
        }

        if (!_rotating)
        {
            _rotating = true;
            RotateTo* rotateTo1 = RotateTo::create(0.06f, 10.0f);
            RotateTo* rotateTo2 = RotateTo::create(0.06f, -10.0f);
            Sequence* sequence = Sequence::createWithTwoActions(rotateTo1, rotateTo2);
            _clock_flag->runAction(RepeatForever::create(sequence));
        }
    }
    char buf[128] = {0};
    snprintf(buf, 127, "%.01f", leaveTime);
    _leave_time->setText(buf);
    _leave_time_red->setText(buf);
}

void GameLayer::onGameOver()
{
    SOUNDMANAGER()->stopSound();
    ShareMethod::showBanner(false);
    _rotating = false;
    _clock_flag->stopAllActions();
    GLOBALDATA()->saveGameScore();
    GLOBALDATA()->saveToFile();

    if (GLOBALDATA()->getCanContinue() && 
        (GLOBALDATA()->getTotalCoin()>=GLOBALDATA()->getContinueCost()))
    {
        createWaitWidget();
    }
    else
    {
        createReportWidget();
    }
}

void GameLayer::startGame()
{
    // 游戏开始时尝试播放背景音乐
    SOUNDMANAGER()->playSound(ST_MAIN_BACKGROUND, true);
    ShareMethod::showBanner(true);

    _cur_distance = 0;
    _bk_cur_pos = Point(0.0f, -370.0f);
    _background->setPosition(_bk_cur_pos);
    createStartPillars();
    createHero();
    setLeaveTime(GLOBALDATA()->getTotalDelta());

    char buf[128] = {0};
    snprintf(buf, 127, "%dm", GLOBALDATA()->getHighScore());
    _high_score->setText(buf);
    snprintf(buf, 127, "%dm", GLOBALDATA()->getCurrentScore());
    _distance_score->setText(buf);

    switchModeButton(false);

    _game_status = GS_GAME_READY;
}

void GameLayer::cleanGameElement()
{
    GLOBALDATA()->resetGameData();
    PillarList::iterator iter = _pillars.begin();
    for (; iter!=_pillars.end(); ++iter)
    {
        Pillar* pillar = *iter;
        pillar->stopAllActions();
        destroyPillar(pillar);
    }
    _pillars.clear();

    _hero->stopAllActions();
    _hero->removeFromParentAndCleanup(true);
    _hero = NULL;

    _background->setPosition(_bk_cur_pos);
    _clock_flag->stopAllActions();
    _in_action = false;
}

Pillar* GameLayer::findHitPillar()
{
    PillarList::iterator iter = _pillars.begin();
    PillarList::iterator iterEnd = _pillars.end();
    Pillar* pillarHit = NULL;
    for (; iter!=iterEnd; ++iter)
    {
        Pillar* pillar = *iter;
        if (pillar->isVisible() && abs((*iter)->getPositionX()-_hero->getPositionX())<0.1f)
        {
            pillarHit = *iter;
            break;
        }
    }
    return pillarHit;
}

void GameLayer::addPopupLabel(const char* text, const Point& posStart, const Color3B& color)
{
    TTFConfig ttfConfig("game_font.TTF", 32, GlyphCollection::DYNAMIC);
    Label* label = Label::createWithTTF(ttfConfig, text);
    addChild(label, REPORT_LABEL_Z);
    Point posHero(_hero->getPosition());
    label->setPosition(posHero);
    label->setColor(color);

    auto fadeOut = FadeOut::create(0.5f);
    auto moveBy = MoveBy::create(0.5f, Point(0.0f, 120.0f));
    auto spawn = Spawn::createWithTwoActions(fadeOut, moveBy);
    auto removeSelf = RemoveSelf::create(true);
    label->runAction(Sequence::createWithTwoActions(spawn, removeSelf));
}

void GameLayer::onEatCoin(int value)
{
    char text[128] = {0};
    snprintf(text, 127, "+%d", value);
    addPopupLabel(text, _hero->getPosition(), Color3B::RED);
    GLOBALDATA()->setTotalCoin(GLOBALDATA()->getTotalCoin()+value);
}

void GameLayer::onEatTime(int value)
{
    GLOBALDATA()->setTotalDelta(GLOBALDATA()->getTotalDelta()+value);

    char text[128] = {0};
    snprintf(text, 127, "+%d", value);
    addPopupLabel(text, _hero->getPosition(), Color3B::YELLOW);
}

void GameLayer::onRestartClicked(Ref* sender, TouchEventType type)
{
    if (TOUCH_EVENT_ENDED==type)
    {
        SOUNDMANAGER()->playSound(ST_BUTTON_CLICEKD);
        _reportWidget->removeFromParentAndCleanup(true);
        _reportWidget = NULL;

        cleanGameElement();

        runAction(Sequence::createWithTwoActions(DelayTime::create(0.1f),
            CallFunc::create(CC_CALLBACK_0(GameLayer::startGame, this))));
    }
}

void GameLayer::onContinueButtonClicked(Ref* sender, TouchEventType type)
{
    if (TOUCH_EVENT_ENDED==type)
    {
        SOUNDMANAGER()->playSound(ST_BUTTON_CLICEKD);
        ShareMethod::showBanner(true);
        GLOBALDATA()->setCanContinue(false);
        GLOBALDATA()->setTotalCoin(GLOBALDATA()->getTotalCoin()-GLOBALDATA()->getContinueCost());
        GLOBALDATA()->setTotalDelta(GLOBALDATA()->getDefaultTotalTime());
        GLOBALDATA()->saveToFile();
        SOUNDMANAGER()->playSound(ST_MAIN_BACKGROUND, true);
        _game_status = GS_GAME_RUN;
        onWaitWidgetFinish();
    }
}

void GameLayer::createReportWidget()
{
    static int report_times = 1;
//    if (GLOBALDATA()->getNewRecord())
//    {// 破记录时，直接显示分享
//        shareScore();
//    }
//    else
    {// 没有破记录的处理
        if ((report_times++)%4==0)
        {
            ShareMethod::showInterstitial();
        }
    }    
    _reportWidget = GUIReader::getInstance()->widgetFromJsonFile("GameReport.ExportJson");
    addChild(_reportWidget, REPORT_Z);
    Widget* gameReportWidget = _reportWidget->getChildByName("GameReport");
    Widget* centerWidget = _reportWidget->getChildByName("CenterPanel");
    Widget* widget = centerWidget->getChildByName("imgBackground");
    Text* labScore = (Text*)widget->getChildByName("labScore");
    char buf[128] = {0};
    snprintf(buf, 128, "%dm", GLOBALDATA()->getCurrentScore());
    labScore->setText(buf);

    Widget* scoreBK = widget->getChildByName("imgScoreBack");
    Text* textBestScore = (Text*)scoreBK->getChildByName("labBestScore");
    snprintf(buf, 128, "%dm", GLOBALDATA()->getHighScore());
    textBestScore->setText(buf);
    Text* textTotalCoin = (Text*)scoreBK->getChildByName("labTotalCoin");
    snprintf(buf, 128, "%d", GLOBALDATA()->getTotalCoin());
    textTotalCoin->setText(buf);

    Button* btnRestart = (Button*)centerWidget->getChildByName("btnRestart");
    btnRestart->addTouchEventListener(this, toucheventselector(GameLayer::onRestartClicked));
    Button* btnShare = (Button*)centerWidget->getChildByName("btnShare");
    btnShare->addTouchEventListener(this, toucheventselector(GameLayer::onShareClicked));
    Button* btnRank = (Button*)widget->getChildByName("btnRank");
    btnRank->addTouchEventListener(this, toucheventselector(GameLayer::onRankClicked));
    Button* btnMall = (Button*)widget->getChildByName("btnMall");
    btnMall->addTouchEventListener(this, toucheventselector(GameLayer::onMallClicked));
}

void GameLayer::onWaitWidgetFinish()
{
    if (NULL!=_waitWidget)
    {
        _waitClock->stopAllActions();
        _waitClock = NULL;
        _waitWidget->removeFromParentAndCleanup(true);
        _waitWidget = NULL;
    }
    if (GS_GAME_RUN!=_game_status)
    {
        createReportWidget();
    }
}

void GameLayer::createWaitWidget()
{
    _waitWidget = GUIReader::getInstance()->widgetFromJsonFile("GameWait.ExportJson");
    addChild(_waitWidget, WAIT_Z);
    Widget* bgWidget = _waitWidget->getChildByName("imgBackground");
    Size bgSize(bgWidget->getContentSize());
    _waitClock = WaittClockCtrl::create();
    std::function<void()> func = std::bind(&GameLayer::onWaitWidgetFinish, this);
    _waitClock->initClock(3.0f, func);
    _waitClock->setPosition(Point(0.0f, bgSize.height));
    bgWidget->addChild(_waitClock);

    Widget* coinFrame = bgWidget->getChildByName("imgCoinFrame");
    Text* labTotalCoin = (Text*)coinFrame->getChildByName("labTotalCoin");
    char text[256] = {0};
    snprintf(text, 255, "%d", GLOBALDATA()->getTotalCoin());
    labTotalCoin->setText(text);

    Button* btnContinue = (Button*)_waitWidget->getChildByName("btnContinue");
    btnContinue->addTouchEventListener(this, toucheventselector(GameLayer::onContinueButtonClicked));

    Widget* temp = btnContinue->getChildByName("labFor");
    Point pos(temp->getPosition());
    temp->removeFromParentAndCleanup(true);
    TTFConfig ttfConfig("game_font.TTF", 32, GlyphCollection::DYNAMIC);
    snprintf(text, 255, "FOR:");
    Label* label = Label::createWithTTF(ttfConfig, text);
    label->setTextColor(Color4B::WHITE);
    label->setPosition(pos);
    btnContinue->addChild(label);

    temp = btnContinue->getChildByName("labAddTime");
    pos = temp->getPosition();
    temp->removeFromParentAndCleanup(true);
    snprintf(text, 255, "+%.0fs", GLOBALDATA()->getDefaultTotalTime());
    label = Label::createWithTTF(ttfConfig, text);
    label->setTextColor(Color4B::BLACK);
    label->setPosition(pos);
    btnContinue->addChild(label);

    temp = btnContinue->getChildByName("labDelCoin");
    pos = temp->getPosition();
    temp->removeFromParentAndCleanup(true);
    snprintf(text, 255, "-%d", GLOBALDATA()->getContinueCost());
    label = Label::createWithTTF(ttfConfig, text);
    label->setTextColor(Color4B::BLACK);
    label->setPosition(pos);
    btnContinue->addChild(label);
}

void GameLayer::moveBackground(int unit)
{
    _bk_cur_pos.x -= unit;
    _bk_cur_pos.y -= unit * sqrt(3.0) / 3.0;
    _background->setPosition(_bk_cur_pos);
    _background->updateBackground(_bk_cur_pos);
}

void GameLayer::onSupperMode()
{
    if (GLOBALDATA()->isInSupperMode())
    {
        return;
    }
    GLOBALDATA()->setInSupperMode();
    setPillarItemVisible(false);
    switchModeButton(true);
    std::function<void()> func = std::bind(&GameLayer::onNormalMode, this);
    _hero->tobeSupperMan(GLOBALDATA()->getSupperTime(), func);
    PillarList aryTemp;
    aryTemp.swap(_pillars);
    PillarList::iterator iter = aryTemp.begin();
    Pillar* leftPillar = *iter;
    leftPillar->setItemVisible(false);
    _pillars.push_back(leftPillar);
    ++iter;
    for (; iter!=aryTemp.end(); ++iter)
    {
        Pillar* rightPillar = *iter;
        if ((rightPillar->getPositionX()-leftPillar->getPositionX())>=_pillar_width)
        {
            Pillar* pillar = createPillar();
            _pillars.push_back(pillar);
            pillar->setPosition(Point(leftPillar->getPositionX()+_pillar_width,
                                      leftPillar->getPositionY()+_space));
            
        }
        leftPillar = rightPillar;
        leftPillar->setItemVisible(false);
        _pillars.push_back(leftPillar);
    }
}

Pillar* GameLayer::createPillar(bool canCreateItem, bool record)
{
    Pillar* pillar = NULL;
    if (_discard_pillars.empty())
    {
        pillar = Pillar::createPillar(canCreateItem, record);
        addChild(pillar, PILLAR_Z);
    }
    else
    {
        pillar = _discard_pillars.front();
        _discard_pillars.pop_front();
        pillar->setVisible(true);
        if (record)
        {
            pillar->initPillarWithRecord();
        }
        else
        {
            pillar->initPillar();
        }
    }
    return pillar;
}

void GameLayer::destroyPillar(Pillar* pillar)
{
    pillar->removeFromParentAndCleanup(true);
//     pillar->setVisible(false);
//     _discard_pillars.push_back(pillar);
}

void GameLayer::onNormalMode()
{
    setPillarItemVisible(true);
    switchModeButton(false);
    onStandActionFinish();
}

void GameLayer::setPillarItemVisible(bool visible)
{
    Utility::forEach(_pillars, std::bind(&Pillar::setItemVisible, std::placeholders::_1, visible));
}

void GameLayer::onShareClicked(Ref* sender, TouchEventType type)
{
    if (TOUCH_EVENT_ENDED==type)
    {
        SOUNDMANAGER()->playSound(ST_BUTTON_CLICEKD);
        shareScore();
    }
}

void GameLayer::onRankClicked(Ref* sender, TouchEventType type)
{
    if (TOUCH_EVENT_ENDED==type)
    {
        SOUNDMANAGER()->playSound(ST_BUTTON_CLICEKD);
        ShareMethod::showGameCenter();
    }
}

void GameLayer::switchModeButton(bool superMode)
{
    if (superMode)
    {
        _btnJump2->setVisible(false);
        _btnJump3->setVisible(true);
        _btnJump2->setLocalZOrder(0);
        _btnJump3->setLocalZOrder(1);
    }
    else
    {
        _btnJump2->setVisible(true);
        _btnJump3->setVisible(false);
        _btnJump2->setLocalZOrder(1);
        _btnJump3->setLocalZOrder(0);
    }
}

void GameLayer::onMallClicked(Ref* sender, TouchEventType type)
{
    if (TOUCH_EVENT_ENDED==type)
    {// 商店
        cocos2d::MessageBox("Coming soon!", "Information");
    }
}

void GameLayer::shareScore()
{
    char text[256] = {0};
    snprintf(text, 255, GLOBALDATA()->getScoreShareFormat().c_str(), GLOBALDATA()->getCurrentScore());
    callShareImpl(text);
}

void GameLayer::shareGame()
{
    callShareImpl(GLOBALDATA()->getShareFormat().c_str());
}

void GameLayer::callShareImpl(const char* shareText)
{
    if (LanguageType::CHINESE==Application::getInstance()->getCurrentLanguage())
    {
        ShareMethod::shareWithWeChat(shareText);
    }
    else
    {
        ShareMethod::shareWithFacebook(shareText);
    }
}

void GameLayer::updateSoundUI()
{
    if (GLOBALDATA()->getEnableMute())
    {
        _sound_button->loadTextureNormal("button_sound_normal.png", ui::UI_TEX_TYPE_PLIST);
        SOUNDMANAGER()->playSound(ST_MAIN_BACKGROUND, true);
    }
    else
    {
        _sound_button->loadTextureNormal("button_sound_pressed.png", ui::UI_TEX_TYPE_PLIST);
        SOUNDMANAGER()->stopSound();
    }
}
