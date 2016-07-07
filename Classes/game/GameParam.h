/**
 * @file    GameParam.h
 * @brief   游戏中各种参数设置
 * @version 1.0
 * @date    2014.8.10
 */
#ifndef __GameParam_H__
#define __GameParam_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



/// 游戏中使用到的各种参数定义
#define HERO_JUMP_UP_TIME   0.05f    ///< 角色往上跳的时间
#define HERO_JUMP_DOWN_TIME 0.05f    ///< 角色掉下来的时间
#define HERO_JUMP_FULL_TIME (HERO_JUMP_UP_TIME+HERO_JUMP_DOWN_TIME)
#define HERI_MISS_ANIM_TIMES 6
#define HERO_MISS_DOWN_TIME 0.5f    ///< 角色掉下去的时间
#define HERO_RESTORE_TIME   1.0f    ///< 角色复活归位的时间

#endif /*__GameParam_H__*/