#include "Hero.h"
#include "GameParam.h"
#include "../comm/UIHelper.h"
#include "../comm/SoundManager.h"

///////////////////////////////////////////////////////////////
// Hero
///////////////////////////////////////////////////////////////
bool Hero::init()
{
    bool ret = false;
    do 
    {
        CC_BREAK_IF(!Sprite::init());
        CC_BREAK_IF(!initWithSpriteFrameName("tom_standing_1.png"));
        CC_BREAK_IF(!createSupperBar());
        ret = true;
    } while (false);
    return ret;
}

void Hero::stand(std::function<void()>& funcCallback)
{
    if (HS_STAND==_hero_status)
    {
        return;
    }
    stopAllActions();
    _hero_status = HS_STAND;
    initWithSpriteFrameName("tom_standing_1.png");
    runAction(RepeatForever::create(UIHelper::createAnimate("tom_standing_%d.png", 3, 4, 1)));
    funcCallback();
}

void Hero::jump(std::function<void()>& funcCallback)
{
    if (HS_JUMP==_hero_status)
    {
        return;
    }
    stopAllActions();
    _hero_status = HS_JUMP;
    SOUNDMANAGER()->playSound(ST_HERO_JUMP);
    initWithSpriteFrameName("tom_jump_1.png");
    MoveBy* moveByUp = MoveBy::create(HERO_JUMP_UP_TIME, Point(0.0f, 35.0f));
    MoveBy* moveByDown = MoveBy::create(HERO_JUMP_DOWN_TIME, Point(0.0f, -35.0f));
    CallFunc* callFunc = CallFunc::create(funcCallback);
    runAction(Sequence::create(moveByUp, moveByDown, callFunc, NULL));
}

void Hero::down(std::function<void()>& funcCallback)
{
    stopAllActions();
    initWithSpriteFrameName("tom_jump_1.png");
    MoveBy* moveByDown = MoveBy::create(HERO_JUMP_DOWN_TIME, Point(0.0f, -90.0f));
    CallFunc* callFunc = CallFunc::create(funcCallback);
    runAction(Sequence::create(moveByDown, callFunc, NULL));
}

void Hero::die(std::function<void()>& funcCallback)
{
    if (HS_DIE==_hero_status)
    {
        return;
    }
    stopAllActions();
    _hero_status = HS_DIE;
    SOUNDMANAGER()->playSound(ST_HERO_DIE);
    initWithSpriteFrameName("tom_miss_1.png");
    auto repeatMiss = Repeat::create(UIHelper::createAnimate("tom_miss_%d.png", 3, HERI_MISS_ANIM_TIMES, 1), 3);
    auto moveBy = MoveBy::create(HERO_MISS_DOWN_TIME, Point(0.0f, -getPositionY()));
    auto callFunc = CallFunc::create(funcCallback);
    runAction(Sequence::create(repeatMiss, moveBy, callFunc, NULL));
}

void Hero::resurgence(float toPos, std::function<void()>& funcCallback)
{
    if (HS_RESURGENCE==_hero_status)
    {
        return;
    }
    stopAllActions();
    _hero_status = HS_RESURGENCE;
    initWithSpriteFrameName("tom_miss_1.png");
    auto moveBy = MoveBy::create(HERO_RESTORE_TIME, Point(0.0f, toPos+90.0f));
    auto callFunc = CallFunc::create(funcCallback);
    runAction(Sequence::createWithTwoActions(moveBy, callFunc));
    runAction(RepeatForever::create(UIHelper::createAnimate("tom_res_%d.png", 4, 4, 1)));
}

bool Hero::createSupperBar()
{
    Size contentSize(getContentSize());
    _supper_blod = UIHelper::createSprite("supper_progress_bk", "item");
    _supper_blod->setPosition(Point(contentSize.width/2.0f, contentSize.height));
    addChild(_supper_blod);

    _supper_timer = ProgressTimer::create(UIHelper::createSprite("supper_progress", "item"));
    _supper_timer->setType(ProgressTimer::Type::BAR);
    //_supper_timer->setMidpoint(Point(0, 0));
    _supper_timer->setMidpoint(Point(1, 0));
    _supper_timer->setBarChangeRate(Point(1, 0));
    _supper_timer->setPosition(Point(contentSize.width/2.0f, contentSize.height));
    addChild(_supper_timer);

    _supper_timer->setVisible(false);
    _supper_blod->setVisible(false);
    return true;
}

void Hero::tobeSupperMan(float duration, std::function<void()>& funcCallback)
{
    _supper_blod->setVisible(true);
    _supper_timer->setVisible(true);
    auto procTo = ProgressTo::create(duration, 100.0f);
    auto tobeNormal = CallFunc::create(CC_CALLBACK_0(Hero::tobeNormalMan, this));
    auto callBack = CallFunc::create(funcCallback);
    _supper_timer->runAction(Sequence::create(procTo, tobeNormal, callBack, NULL));
}

void Hero::tobeNormalMan()
{
    _supper_timer->setVisible(false);
    _supper_blod->setVisible(false);
}
