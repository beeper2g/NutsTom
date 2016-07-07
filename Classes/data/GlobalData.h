/**
 * @file    GlobalData.cpp
 * @brief   ��Ϸ��������Ҫ����Ϸ����ʵ����
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
    GM_EASY     = 0,    ///< ���Ѷȣ�ֻ��4��ñ��
    GM_NORMAL,          ///< ��ͨ�Ѷȣ�5��ñ��
    GM_HARD,            ///< �߼��Ѷȣ�6��ñ��
};

/// �����ƶ�����
#define MOVE_DISTANCE_UNIT 2

/// ȫ�����ݴ洢
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
    CC_SYNTHESIZE(bool, _enable_mute, EnableMute);  ///< �Ƿ�������Ч
    CC_SYNTHESIZE(bool, _enable_scene_sound, EnableSceneSound); ///< ָ�������Ƿ���������

    CC_SYNTHESIZE(long, _high_score, HighScore);    ///< ��óɼ�
    CC_SYNTHESIZE(float, _total_delta, TotalDelta); ///< ��ʱ
    CC_SYNTHESIZE(long, _cur_score, CurrentScore);
    CC_SYNTHESIZE(long, _total_coin, TotalCoin);    ///< �ܽ����
    CC_SYNTHESIZE(bool, _can_continue, CanContinue);  ///< �Ƿ��������
    CC_SYNTHESIZE_READONLY(long, _continue_cost, ContinueCost);  ///< �������Ļ���Ҫ�۳��Ľ���� 
    CC_SYNTHESIZE_READONLY(bool, _new_record, NewRecord);   ///< �Ƿ��Ƽ�¼

public:
    /// ������Ϸ�������
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
    float       _coin_rate;     ///< ���ֽ�ҵĸ���
    float       _clock_rate;    ///< ����ʱ����ߵĸ���
    float       _supper_rate;   ///< �����޵е��ߵĸ���

    bool        _in_supper_mode;    ///< �Ƿ����޵�ģʽ
    float       _supper_time;       ///< �޵�ʣ��ʱ��

    unsigned int    _bk_map_index;
    bool        _map_res_loaded;    ///< ��ͼ�����Ƿ����
};

#define GLOBALDATA()    GlobalData::getInstance()



#endif /*__GlobalData_H__*/