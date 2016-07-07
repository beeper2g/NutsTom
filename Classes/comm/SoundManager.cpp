#include "SoundManager.h"
#include "../comm/Cocos2dxPlatform.h"
#include "../data/GlobalData.h"

SoundManager* SoundManager::getInstance()
{
    static SoundManager mgrSound;
    return &mgrSound;
}

void SoundManager::onButtonClicked()
{
    if (!GLOBALDATA()->getEnableMute())
    {
        return;
    }
    SimpleAudioEngine::getInstance()->playEffect("button_click.mp3");
}

void SoundManager::playSound(SOUND_TYPE type, bool repeated)
{
    if (!GLOBALDATA()->getEnableMute())
    {
        return;
    }
    switch (type)
    {
    case ST_MAIN_BACKGROUND:
        SimpleAudioEngine::getInstance()->playBackgroundMusic("bgmusic.mp3", repeated);
        break;
    case ST_HERO_JUMP:
        SimpleAudioEngine::getInstance()->playEffect("jump.mp3", repeated);
        break;
    case ST_HERO_DIE:
        SimpleAudioEngine::getInstance()->playEffect("die.mp3", false);
        break;
    case ST_PLAY_BACKGROUND:
        SimpleAudioEngine::getInstance()->playEffect("logo_fly_in.mp3", false);
        break;
    case ST_SHARE_BACKGROUND:
        SimpleAudioEngine::getInstance()->playEffect("share_fly_in.mp3", false);
        break;
    default:
        break;
    }
}

void SoundManager::stopSound()
{
    SimpleAudioEngine::getInstance()->stopBackgroundMusic(false);
    SimpleAudioEngine::getInstance()->stopAllEffects();
}

void SoundManager::initialize()
{
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic("bgmusic.mp3");
    SimpleAudioEngine::getInstance()->preloadEffect("die.mp3");
    SimpleAudioEngine::getInstance()->preloadEffect("jump.mp3");
    SimpleAudioEngine::getInstance()->preloadEffect("share_fly_in.mp3");
    SimpleAudioEngine::getInstance()->preloadEffect("logo_fly_in.mp3");

}

void SoundManager::resumeBackgroundMusic()
{
    if (GLOBALDATA()->getEnableMute() && GLOBALDATA()->getEnableSceneSound())
    {
        SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    }    
}

void SoundManager::pauseBackgroundMusic()
{
    if (GLOBALDATA()->getEnableMute())
    {
        SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    }     
}
