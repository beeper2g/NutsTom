#include "UIHelper.h"

namespace UIHelper
{

Animate* createAnimate(const char* fmt, int count, float fps, int start/*=0*/)
{
    int maxCount = start + count;
    Animation* animation = Animation::create();
    animation->setDelayPerUnit(1/fps);
    animation->setRestoreOriginalFrame(true);
    for (int n=start; n<maxCount; ++n)
    {
        const char* filename = String::createWithFormat(fmt, n)->getCString();
        SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(filename);
        animation->addSpriteFrame(frame);
    }
    return Animate::create(animation);
}

Sprite* createSprite(const char* fileName, const char* path, FILE_TYPE type/*=FT_PNG*/)
{
    char file[512] = {0};
    Sprite* sprite = NULL;
    switch (type)
    {
    case UIHelper::FT_PNG:
        if (NULL==path)
        {
            snprintf(file, 511, "%s.png", fileName);
        }
        else
        {
            snprintf(file, 511, "%s/%s.png", path, fileName);
        }
        break;
    case UIHelper::FT_JPG:
        if (NULL==path)
        {
            snprintf(file, 511, "%s.jpg", fileName);
        }
        else
        {
            snprintf(file, 511, "%s/%s.jpg", path, fileName);
        }
        break;
    default:
        break;
    }

    if (FileUtils::getInstance()->isFileExist(file))
    {
        sprite = Sprite::create(file);
    }
    
    if (NULL==sprite)
    {
        switch (type)
        {
        case UIHelper::FT_PNG:
            snprintf(file, 511, "%s.png", fileName);
            break;
        case UIHelper::FT_JPG:
            snprintf(file, 511, "%s.jpg", fileName);
            break;
        default:
            break;
        }
        sprite = Sprite::createWithSpriteFrameName(file);
    }

    return sprite;
}


}