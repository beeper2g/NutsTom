/**
 * @file    GameLayer.h
 * @brief   游戏主层
 * @version 1.0
 * @date    2014.7.30
 */
#ifndef __GameLayer_H__
#define __GameLayer_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../comm/BasicLayer.h"
#include "GameControl.h"

class GameBackground;
class Hero;
class Pillar;
class WaittClockCtrl;
/// 游戏主层界面
class GameLayer : public BasicLayer
                , public IGameControl
{
    /// 游戏中的元素Z轴
    enum LAYER_Z_ORDER
    {
        BACKGROUND_Z    = 0,
        BACKANIMATION_Z,
        PILLAR_Z,
        ITEM_Z,
        HERO_Z,
        REPORT_LABEL_Z,
        CONTROL_Z,
        WAIT_Z,
        REPORT_Z,
    };

    /// 游戏的状态
    enum GAME_STATUS
    {
        GS_GAME_READY,      ///< 游戏参数准备完毕，等待用户点击
        GS_GAME_RUN,        ///< 游戏中
        GS_GAME_OVER,       ///< 游戏结束
    };
    friend class GameControlDelegate;
public:
    GameLayer();
    CREATE_FUNC(GameLayer);
    virtual bool init();
protected:
    virtual void update(float delta);

    void onSoundButtonClicked(Ref* sender, TouchEventType type);
    void onRestartButtonClicked(Ref* sender, TouchEventType type);
    void onJump1ButtonClicked(Ref* sender, TouchEventType type);
    void onJump2ButtonClicked(Ref* sender, TouchEventType type);
    void onRestartClicked(Ref* sender, TouchEventType type);
    void onShareClicked(Ref* sender, TouchEventType type);
    void onRankClicked(Ref* sender, TouchEventType type);
    void onContinueButtonClicked(Ref* sender, TouchEventType type);
    void onMallClicked(Ref* sender, TouchEventType type);

    void onStandActionFinish();
    void onJumpActionFinish();

    void onDieActionFinish();
    void onResurgenceActionFinish();
    void onDownActionFinish();
    void onWaitWidgetFinish();

    // IGameControl 接口重载
    virtual void onEatCoin(int value);
    virtual void onEatTime(int value);
    virtual void onSupperMode();
private:
    bool createBackground();
    bool createBackgroundAnimation();
    bool createStartPillars();
    bool createControl();

    Pillar* createPillar(bool canCreateItem=true, bool record=false);
    void destroyPillar(Pillar* pillar);

    void createPillarToMap();
    bool createHero();

    void startGame();
    void cleanGameElement();

    void moveScene(int unit);
    void movePillars(int unit, float duration);
    void moveBackground(int unit);

    void switchModeButton(bool superMode);

    Pillar* findHitPillar();
    void setLeaveTime(float leaveTime);
    void onGameOver();
    void createWaitWidget();
    void createReportWidget();
    void addPopupLabel(const char* text, const Point& posStart, const Color3B& color);
    void onNormalMode();
    void setPillarItemVisible(bool visible);

    void shareScore();
    void shareGame();
    void callShareImpl(const char* shareText);
    void updateSoundUI();
private:
    GAME_STATUS     _game_status;
    Point           _bk_cur_pos;
    GameBackground* _background;
    
    typedef std::list<Pillar*>  PillarList;
    float           _space;
    float           _pillar_width;
    float           _pillar_height;
    float           _last_pillar_pos_x;
    float           _last_pillar_pos_y;
    float           _pillar_start_y_pos;
    long            _cur_distance;
    PillarList      _pillars;
    PillarList      _discard_pillars;
    
    bool            _in_action;
    Hero*           _hero;
    float           _hero_pos_x;
    float           _hero_pos_y;
    float           _hero_pos_y_base;
    
    Text*           _high_score;
    Text*           _distance_score;
    Text*           _leave_time;
    Text*           _leave_time_red;

    bool            _rotating;
    ImageView*      _clock_flag;

    Widget*         _reportWidget;
    Widget*         _waitWidget;
    WaittClockCtrl* _waitClock;

    Button*         _btnJump1;
    Button*         _btnJump2;
    Button*         _btnJump3;
    Button*         _sound_button;
};


#endif /*__GameLayer_H__*/