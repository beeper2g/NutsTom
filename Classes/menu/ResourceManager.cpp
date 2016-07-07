#include "ResourceManager.h"
#include "data/GlobalData.h"

///////////////////////////////////////////////////////////////////////////////
// RESOURCE_NODE
///////////////////////////////////////////////////////////////////////////////
ResourceManager::RESOURCE_NODE::RESOURCE_NODE(RESOURCE_TYPE type, const char* name, const CallBackFunc* callFunc/*=NULL*/)
    :_res_type(type)
    ,_res_name(name)
{
    if (NULL!=callFunc)
    {
        _call_func = *callFunc;
    }
}

///////////////////////////////////////////////////////////////////////////////
// ResourceManager
///////////////////////////////////////////////////////////////////////////////
ResourceManager::ResourceManager()
    :_cur_node_index(0)
    ,_init_finished(false)
    , _total_loaded_count(0)
{  

}

ResourceManager::~ResourceManager()
{

}

bool ResourceManager::loadResource(const CallBackFunc& onFinishFunc)
{
    _onFinishCallBack = onFinishFunc;
    initializeParams();
    loadResourceImpl();
    return true;
}

void ResourceManager::appendResourceNode(RESOURCE_TYPE type, const char* name, const CallBackFunc* callFunc)
{
    _ary_resources.push_back(ResourceManager::RESOURCE_NODE(type, name, callFunc));
}

ResourceManager::RESOURCE_NODE* ResourceManager::getNextResourceNode()
{
    RESOURCE_NODE* nextNode = NULL;
    if ((size_t)_cur_node_index < _ary_resources.size())
    {
        nextNode = &(_ary_resources.at(_cur_node_index));
        ++_cur_node_index;
    }
    return nextNode;
}

void ResourceManager::loadResourceImpl()
{
    RESOURCE_NODE* node = getNextResourceNode();
    while (NULL!=node)
    {
        std::string resFileName = getResourceFileName(*node);
        if (resFileName.empty())
        {
            CCLOGERROR("[%s:%d] Can't get resource file name. [%d]-[%s]", 
                __FUNCTION__, __LINE__,
                node->_res_type, node->_res_name.c_str());
            return;
        }
        CCLOG("[%s:%d]""Begin load resource [%s].", __FUNCTION__, __LINE__, resFileName.c_str());
        TextureCache* cacheTexture = Director::getInstance()->getTextureCache();
        cacheTexture->addImageAsync(resFileName.c_str(), CC_CALLBACK_1(ResourceManager::onLoadTextureFinish, this));
        node = getNextResourceNode();
    }
}

void ResourceManager::onLoadTextureFinish(Texture2D* texture2d)
{
    //RESOURCE_NODE* node = getNextResourceNode();
    RESOURCE_NODE* node = &_ary_resources[_total_loaded_count];
    if (NULL!=node)
    {
        if (ResourceManager::RT_PLIST==node->_res_type)
        {
            addToSpriteFrameCache(*node, texture2d);
        }
        if (NULL!=node->_call_func)
        {
            CCLOG("[%s:%d] Begin call node call back function.", __FUNCTION__, __LINE__);
            node->_call_func();
            CCLOG("[%s:%d] Call node call back function finish.", __FUNCTION__, __LINE__);
        }
    }
    else
    {
        CCLOGERROR("[%s:%d] Invalidate param.", __FUNCTION__, __LINE__);
    }

    ++_total_loaded_count;
    //++_cur_node_index;
    //loadResourceImpl();
}

std::string ResourceManager::getResourceFileName(const RESOURCE_NODE& node) const
{
    char fileName[128] = {0};
    switch (node._res_type)
    {
    case ResourceManager::RT_PLIST:
        snprintf(fileName, 127, "%s.pvr.ccz", node._res_name.c_str());
        break;
    case ResourceManager::RT_PNG_FILE:
        snprintf(fileName, 127, "%s.png", node._res_name.c_str());
        break;
    case ResourceManager::RT_JPG_FILE:
        snprintf(fileName, 127, "%s.jpg", node._res_name.c_str());
        break;
    default:
        CCASSERT(false, "Invalid resource type.");
        break;
    }
    return fileName;
}

void ResourceManager::addToSpriteFrameCache(const RESOURCE_NODE& node, Texture2D* texture2d)
{
    char fileName[128] = {0};
    snprintf(fileName, 127, "%s.plist", node._res_name.c_str());
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(fileName, texture2d);
}

void ResourceManager::initializeParams()
{
    _cur_node_index = 0;
    _total_loaded_count = 0;
    appendResourceNode(ResourceManager::RT_PLIST, "pillar");
    appendResourceNode(ResourceManager::RT_PLIST, "role");
    appendResourceNode(ResourceManager::RT_PLIST, "item");
    appendResourceNode(ResourceManager::RT_PLIST, "gameui", &_onFinishCallBack);

    CallBackFunc callFunc = CC_CALLBACK_0(GlobalData::onMapResourceLoadFinish, GLOBALDATA());
    appendResourceNode(ResourceManager::RT_JPG_FILE, "Bg_01", &callFunc);
//     appendResourceNode(ResourceManager::RT_JPG_FILE, "Bg_02");
//     appendResourceNode(ResourceManager::RT_JPG_FILE, "Bg_03");
//     appendResourceNode(ResourceManager::RT_JPG_FILE, "Bg_04");
//     appendResourceNode(ResourceManager::RT_JPG_FILE, "Bg_05");
//     appendResourceNode(ResourceManager::RT_JPG_FILE, "Bg_06");
//     appendResourceNode(ResourceManager::RT_JPG_FILE, "Bg_07");
//     appendResourceNode(ResourceManager::RT_JPG_FILE, "Bg_08");
//     appendResourceNode(ResourceManager::RT_JPG_FILE, "Bg_09");
//     appendResourceNode(ResourceManager::RT_JPG_FILE, "Bg_10");
//     appendResourceNode(ResourceManager::RT_JPG_FILE, "Bg_11");
//     appendResourceNode(ResourceManager::RT_JPG_FILE, "Bg_12");
//     appendResourceNode(ResourceManager::RT_JPG_FILE, "Bg_13");
//     appendResourceNode(ResourceManager::RT_JPG_FILE, "Bg_14");
//     appendResourceNode(ResourceManager::RT_JPG_FILE, "Bg_15");
//     appendResourceNode(ResourceManager::RT_JPG_FILE, "Bg_16");
//     appendResourceNode(ResourceManager::RT_JPG_FILE, "Bg_17");
//     appendResourceNode(ResourceManager::RT_JPG_FILE, "Bg_18");
//     appendResourceNode(ResourceManager::RT_JPG_FILE, "Bg_19");
//     appendResourceNode(ResourceManager::RT_JPG_FILE, "Bg_20");
}

bool ResourceManager::isResourceLoadFinish() const
{
    return _init_finished;
}

ResourceManager* ResourceManager::getInstance()
{
    static ResourceManager mgrResource;
    return &mgrResource;
}
