/**
 * @file    LuaEngine.h
 * @brief   针对Lua的接口调用进行简单封装，支持调用函数，取变量值等简单操作
 * @version 1.0
 * @date    2014.6.6
 */
#ifndef __LuaEngine_H__
#define __LuaEngine_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>

class LuaEngine
{
public:
    static LuaEngine* getInstance();
    bool loadScriptFile(const char* path, const char* file=nullptr);
    bool loadScriptFiles(const char* path, const char* files[], int fileCount);
    bool loadScriptString(const char* script);

    int getIntValue(const char* paramName, int defValue=0);
    double getDoubleValue(const char* paramName, double defValue=0.0);
    std::string getStringValue(const char* paramName, const char* defValue="");

    int getTableIntValue(const char* tableName, const char* keyName, int defValue=0);
    double getTableDoubleValue(const char* tableName, const char* keyName, double defValue=0.0);
    std::string getTableStringValue(const char* tableName, const char* keyName, const char* defValue="");

protected:
    LuaEngine();
    ~LuaEngine();
private:
};

#define LUAENGINE() LuaEngine::getInstance()

#endif /*__LuaEngine_H__*/