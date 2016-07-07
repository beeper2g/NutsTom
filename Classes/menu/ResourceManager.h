/**
 * @file    ResourceManager.h
 * @brief   游戏中所有使用资源的管理类实现
 * @version 1.0
 * @date    2014.9.14
 */
#ifndef __ResourceManager_H__
#define __ResourceManager_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
#include <string>
#include <functional>
#include "../comm/Cocos2dxPlatform.h"

/// 资源管理器
class ResourceManager
{
public:
    typedef std::function<void()>   CallBackFunc;
private:
    enum RESOURCE_TYPE
    {
        RT_PLIST    = 1,
        RT_PNG_FILE,
        RT_JPG_FILE,
    };

    struct RESOURCE_NODE 
    {
        RESOURCE_NODE(RESOURCE_TYPE type, const char* name, const CallBackFunc* callFunc=NULL);
        RESOURCE_TYPE   _res_type;
        std::string     _res_name;
        CallBackFunc    _call_func;
    };
    typedef std::vector<RESOURCE_NODE>  RESOURCE_NODE_ARRAY;
public:
    ResourceManager();
    static ResourceManager* getInstance();
    void initializeParams();

    ~ResourceManager();
    bool loadResource(const CallBackFunc& onFinishFunc);

    bool isResourceLoadFinish() const;
protected:
    void loadResourceImpl();
    void onLoadTextureFinish(Texture2D* texture2d);
    std::string getResourceFileName(const RESOURCE_NODE& node) const;
    void addToSpriteFrameCache(const RESOURCE_NODE& node, Texture2D* texture2d);
    void appendResourceNode(RESOURCE_TYPE type, const char* name, const CallBackFunc* callFunc=NULL);
    RESOURCE_NODE* getNextResourceNode();
private:
    int     _cur_node_index;
    int     _total_loaded_count;
    RESOURCE_NODE_ARRAY     _ary_resources;
    CallBackFunc    _onFinishCallBack;
    bool    _init_finished;
};

#define RESOURCEMANAGER() ResourceManager::getInstance()

#endif /*__ResourceManager_H__*/