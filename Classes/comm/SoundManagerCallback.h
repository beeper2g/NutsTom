/**
 * @file    SoundManagerCallback.h
 * @brief   
 * @version 1.0
 * @date    2014.6.9
 */
#ifndef __SoundManagerCallback_H__
#define __SoundManagerCallback_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

struct SoundManagerCallback 
{
    virtual void onButtonClicked() = 0;
};


#endif /*__SoundManagerCallback_H__*/