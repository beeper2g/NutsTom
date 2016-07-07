#include "AppDelegate.h"
#include "SceneBuilder.h"
#include "comm/SoundManager.h"

extern"C" {
    size_t fwrite$UNIX2003(const void *a, size_t b, size_t c, FILE *d)
    {
        return fwrite(a, b, c, d);
    }
    
    char* strerror$UNIX2003(int errnum)
    {
        return strerror(errnum);
    }
}

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("NutsTom");
        director->setOpenGLView(glview);
    }

#ifdef _DEBUG
    // turn on display FPS
    director->setDisplayStats(true);
    glview->setFrameZoomFactor(0.5f);   
    glview->setFrameSize(640, 960);     // s tandard
    //glview->setFrameSize(640, 1136);    // 5
    //glview->setFrameSize(768, 1024);    // pad
#endif // _DEBUG

    glview->setDesignResolutionSize(640, 960, ResolutionPolicy::FIXED_HEIGHT);
    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
    // run
    director->runWithScene(SceneBuilder::buildScene(ST_LOAD_SCENE));

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    SOUNDMANAGER()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    SOUNDMANAGER()->resumeBackgroundMusic();
}
