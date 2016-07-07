#include "ShareMethod.h"
#include "cocos2d.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#include "platform/android/jni/JniHelper.h"
#include <jni.h>

const char* AppActivityClassName = "org/cocos2dx/cpp/AppActivity";


void ShareMethod::showInterstitial()
{
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t, AppActivityClassName, "showInterstitial", "()V"))
    {

        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
}

void ShareMethod::showBanner(bool show)
{
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t, AppActivityClassName, show ? "showBanner" : "hideBanner", "()V"))
    {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
}

void ShareMethod::showGameCenter()
{
    cocos2d::MessageBox("Coming soon!", "Information");
}

void ShareMethod::reportScore(int score)
{
    cocos2d::MessageBox("Coming soon!", "Information");
}

void ShareMethod::shareWithWeChat(const char* text)
{
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t, AppActivityClassName, "shareWithWeChat", "(Ljava/lang/String;)V"))
    {
        jstring l_stringUrl = t.env->NewStringUTF(text);
        t.env->CallStaticVoidMethod(t.classID, t.methodID, l_stringUrl);
        t.env->DeleteLocalRef(t.classID);
    }
}

void ShareMethod::shareWithFacebook(const char* text)
{
    shareWithWeChat(text);
}

#else

void ShareMethod::showInterstitial()
{

}

void ShareMethod::showBanner(bool show)
{

}

void ShareMethod::showGameCenter()
{

}

void ShareMethod::reportScore(int score)
{

}

void ShareMethod::shareWithWeChat(const char* text)
{

}

void ShareMethod::shareWithFacebook(const char* text)
{

}

#endif