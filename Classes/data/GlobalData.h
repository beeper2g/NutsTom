/**
 * @file    GlobalData.cpp
 * @brief   游戏中所有需要的游戏数据实现类
 * @version 1.0
 * @date    2014.8.3
 */
#ifndef __GlobalData_H__
#define __GlobalData_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../comm/Cocos2dxPlatform.h"

enum GAME_LEVEL
{
    GM_EASY     = 0,    ///< 简单难度，只有4个帽子
    GM_NORMAL,          ///< 普通难度，5个帽子
    GM_HARD,            ///< 高级难度，6个帽子
};

/// 单次移动距离
#define MOVE_DISTANCE_UNIT 2

/// 全局数据存储
class GlobalData
{
public:
    static GlobalData* getInstance();
    void initialize();
    
    void loadFromFile();
    void saveToFile();

    int getBackgroundMapCount() const;
    const char* getBackgroundMap(unsigned int index) const;

    std::string getShareFormat();
    std::string getScoreShareFormat();
public:
    // Attributes 
    CC_SYNTHESIZE(bool, _enable_mute, EnableMute);  ///< 是否启用音效
    CC_SYNTHESIZE(bool, _enable_scene_sound, EnableSceneSound); ///< 指定场景是否允许音乐

    CC_SYNTHESIZE(long, _high_score, HighScore);    ///< 最好成绩
    CC_SYNTHESIZE(float, _total_delta, TotalDelta); ///< 耗时
    CC_SYNTHESIZE(long, _cur_score, CurrentScore);
    CC_SYNTHESIZE(long, _total_coin, TotalCoin);    ///< 总金币数
    CC_SYNTHESIZE(bool, _can_continue, CanContinue);  ///< 是否允许继续
    CC_SYNTHESIZE_READONLY(long, _continue_cost, ContinueCost);  ///< 如果允许的话需要扣除的金币数 
    CC_SYNTHESIZE_READONLY(bool, _new_record, NewRecord);   ///< 是否破记录

public:
    /// 重置游戏相关数据
    void resetGameData();
    void saveGameScore();
    float getCoinRate() const;
    float getSupperRate() const;
    float getClockRate() const;
    bool isInSupperMode() const;
    void setInSupperMode();
    void updateSupperTime(float delta);
    float getSupperTime() const;
    float getDefaultTotalTime() const;

    void setBackgroundMapIndex(unsigned int index);

    void onMapResourceLoadFinish();
    bool isMapResourceLoaded() const;
protected:
    GlobalData();
    ~GlobalData();
private:
    void copyConfigFileToExecutePath();

    void saveCheckKey(const char* key, long value);
    void saveCheckKey(const char* key, const char* value);

    bool checkValidateKey(const char* key, long value);
    bool checkValidateKey(const char* key, const char* value);

private:
    float       _coin_rate;     ///< 出现金币的概率
    float       _clock_rate;    ///< 出现时间道具的概率
    float       _supper_rate;   ///< 出现无敌道具的概率

    bool        _in_supper_mode;    ///< 是否处于无敌模式
    float       _supper_time;       ///< 无敌剩余时间

    unsigned int    _bk_map_index;
    bool        _map_res_loaded;    ///< 地图纹理是否加载
};

#define GLOBALDATA()    GlobalData::getInstance()



#endif /*__GlobalData_H__*/