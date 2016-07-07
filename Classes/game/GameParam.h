/**
 * @file    GameParam.h
 * @brief   ��Ϸ�и��ֲ�������
 * @version 1.0
 * @date    2014.8.10
 */
#ifndef __GameParam_H__
#define __GameParam_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



/// ��Ϸ��ʹ�õ��ĸ��ֲ�������
#define HERO_JUMP_UP_TIME   0.05f    ///< ��ɫ��������ʱ��
#define HERO_JUMP_DOWN_TIME 0.05f    ///< ��ɫ��������ʱ��
#define HERO_JUMP_FULL_TIME (HERO_JUMP_UP_TIME+HERO_JUMP_DOWN_TIME)
#define HERI_MISS_ANIM_TIMES 6
#define HERO_MISS_DOWN_TIME 0.5f    ///< ��ɫ����ȥ��ʱ��
#define HERO_RESTORE_TIME   1.0f    ///< ��ɫ�����λ��ʱ��

#endif /*__GameParam_H__*/