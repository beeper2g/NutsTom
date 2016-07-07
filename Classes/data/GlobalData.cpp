#include "GlobalData.h"
#include "../comm/LuaEngine.h"
#include "../comm/Utility.h"
#include "../crypto/CCCrypto.h"

/// 所有的背景图
const char* _bg_img_name[] = 
{
    "Bg_01",
    "Bg_02",
    "Bg_03",
    "Bg_04",
    "Bg_05",
    "Bg_06",
    "Bg_07",
    "Bg_08",
    "Bg_09",
    "Bg_10",
    "Bg_11",
    "Bg_12",
    "Bg_13",
    "Bg_14",
    "Bg_15",
    "Bg_16",
    "Bg_17",
    "Bg_18",
    "Bg_19",
    "Bg_20",
};

/// 默认无敌时间
#define DEFAULT_SUPPER_TIME 3.0f

///////////////////////////////////////////////////////////////
// GlobalData
///////////////////////////////////////////////////////////////
GlobalData::GlobalData()
    :_enable_mute(true), _enable_scene_sound(false)
    ,_high_score(0)
    ,_map_res_loaded(false)
#ifdef _DEBUG
    ,_continue_cost(10) 
#else
    ,_continue_cost(1000) 
#endif // _DEBUG
{
    resetGameData();
}

GlobalData::~GlobalData()
{

}

GlobalData* GlobalData::getInstance()
{
    static GlobalData globalData;
    return &globalData;
}

void GlobalData::loadFromFile()
{
    _enable_mute = READ_BOOL("enable_mute", true);
    _high_score = READ_INT("high_score", 0);
    _total_coin = READ_INT("total_coin", 0);
    if (!checkValidateKey("high_score", _high_score))
    {
        _high_score = 0;
    }
    if (!checkValidateKey("total_coin", _total_coin))
    {
        _total_coin = 0;
    }
}

void GlobalData::saveToFile()
{
    WRITE_BOOL("enable_mute", _enable_mute);
    WRITE_INT("high_score", _high_score);
    WRITE_INT("total_coin", _total_coin);
    saveCheckKey("high_score", _high_score);
    saveCheckKey("total_coin", _total_coin);
}

void GlobalData::copyConfigFileToExecutePath()
{
    std::string writableRoot = Utility::getWriteablePathRoot();
    //Utility::makeFolder((writableRoot+"data").c_str());
    Utility::copyFile((writableRoot + "config.data").c_str(), Utility::getFullPathName("", "config.data").c_str());
}

void GlobalData::initialize()
{
    copyConfigFileToExecutePath();
    std::string rootPath = Utility::getWriteablePathRoot();
    char configFile[512] = {0};
    snprintf(configFile, 511, "%sconfig.data", rootPath.c_str());
    bool ret = LUAENGINE()->loadScriptFile(configFile);
    CCAssert(ret, "Invalidate config data file.");
}

int GlobalData::getBackgroundMapCount() const
{
    return COUNTARRAY(_bg_img_name);
}

const char* GlobalData::getBackgroundMap(unsigned int index) const
{
    return _bg_img_name[index];
}

void GlobalData::resetGameData()
{
    _total_delta = getDefaultTotalTime();
    _cur_score = 0;
    _coin_rate = 0.1f;
    _clock_rate = 0.15f;
    _supper_rate = 0.01f;
    _in_supper_mode = false;
    _supper_time = DEFAULT_SUPPER_TIME;
    _can_continue = true;
    _bk_map_index = 0;
    _new_record = false;
}

void GlobalData::saveGameScore()
{
    if (_cur_score>_high_score)
    {
        _high_score = _cur_score;
        _new_record = true;
    }
}

bool GlobalData::isInSupperMode() const
{
    return _in_supper_mode;
}

void GlobalData::updateSupperTime(float delta)
{
    if (_in_supper_mode)
    {
        _supper_time -= delta;
        if (_supper_time <= 0.0f)
        {
            _supper_time = DEFAULT_SUPPER_TIME;
            _in_supper_mode = false;
        }
    }
}

float GlobalData::getCoinRate() const
{
    if (_in_supper_mode)
    {
        return -0.1f;
    }
    return _coin_rate;
}

float GlobalData::getSupperRate() const
{
    if (_in_supper_mode)
    {
        return -0.1f;
    }
    return _supper_rate;
}

float GlobalData::getClockRate() const
{
    if (_in_supper_mode)
    {
        return -0.1f;
    }

    int level = getCurrentScore() / 400; // 0~19
    float rate = _clock_rate * 20 / (20 - level);
    return rate;
}

void GlobalData::setInSupperMode()
{
    _in_supper_mode = true;
    _supper_time = DEFAULT_SUPPER_TIME;
}

float GlobalData::getSupperTime() const
{
    if (!_in_supper_mode)
    {
        return -1.0f;
    }
    return _supper_time;
}

float GlobalData::getDefaultTotalTime() const
{
#ifdef _DEBUG
    return 600.0f;
#endif // _DEBUG
    return 30.0f;
}

void GlobalData::setBackgroundMapIndex(unsigned int index)
{
    if (index>=COUNTARRAY(_bg_img_name))
    {
        index = 0;
    }
    _bk_map_index = index;
}

/**
 * @brief 分享文字
 * @return std::string 从配置中获取分享的文字
 */
std::string GlobalData::getShareFormat()
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    return "";
#else
    std::string fmt;
    if (LanguageType::CHINESE==Application::getInstance()->getCurrentLanguage())
    {
        fmt = LUAENGINE()->getTableStringValue("cn_string_table", "share_format");
    }
    else
    {
        fmt = LUAENGINE()->getTableStringValue("en_string_table", "share_format");
    }
    return fmt;
#endif
}

std::string GlobalData::getScoreShareFormat()
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    return "%d";
#else
    std::string fmt;
    if (LanguageType::CHINESE==Application::getInstance()->getCurrentLanguage())
    {
        fmt = LUAENGINE()->getTableStringValue("cn_string_table", "score_share_format");
    }
    else
    {
        fmt = LUAENGINE()->getTableStringValue("en_string_table", "score_share_format");
    }
    return fmt;
#endif
}

void GlobalData::saveCheckKey(const char* key, long value)
{
    char inputBuf[64] = {0};
    snprintf(inputBuf, 63, "%d", value);
    saveCheckKey(key, inputBuf);
}

void GlobalData::saveCheckKey(const char* key, const char* value)
{
    unsigned char md5Buf[CCCrypto::MD5_BUFFER_LENGTH] = {0};
    CCCrypto::MD5((unsigned char*)value, strlen(value), md5Buf);
    char base64Buf[256] = {0};
    int cp = CCCrypto::encodeBase64(md5Buf, CCCrypto::MD5_BUFFER_LENGTH, base64Buf, 256);
    if (cp>1)
    {
        cp -= 1;
        base64Buf[cp] = 0;
    }
    std::string saveKey(key);
    saveKey += "_KEY";

    WRITE_STRING(saveKey.c_str(), base64Buf);
}

bool GlobalData::checkValidateKey(const char* key, long value)
{
    char inputBuf[64] = {0};
    snprintf(inputBuf, 63, "%d", value);
    return checkValidateKey(key, inputBuf);
}

bool GlobalData::checkValidateKey(const char* key, const char* value)
{
    unsigned char md5Buf[CCCrypto::MD5_BUFFER_LENGTH] = {0};
    CCCrypto::MD5((unsigned char*)value, strlen(value), md5Buf);
    char base64Buf[256] = {0};
    int cp = CCCrypto::encodeBase64(md5Buf, CCCrypto::MD5_BUFFER_LENGTH, base64Buf, 256);
    if (cp>1)
    {
        cp -= 1;
        base64Buf[cp] = 0;
    }
    std::string saveKey(key);
    saveKey += "_KEY";

    std::string checkFlag = READ_STRING(saveKey.c_str(), "");
    return (!checkFlag.empty() && strcmp(checkFlag.c_str(), (const char*)base64Buf)==0);
}

void GlobalData::onMapResourceLoadFinish()
{
    _map_res_loaded = true;
}

bool GlobalData::isMapResourceLoaded() const
{
    return _map_res_loaded;
}
