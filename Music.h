#pragma once
#include "Game.h"
extern int g_soundID;		
//音频编号
typedef int SOUND;
//加载音频
void loadsound(SOUND* pSound, const wchar_t* fileName);
//结束播放
void stopsound(int sid);
//开始播放
void playsound(int sid, int repeat);