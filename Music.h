#pragma once
#include "Game.h"
extern int g_soundID;		
//��Ƶ���
typedef int SOUND;
//������Ƶ
void loadsound(SOUND* pSound, const wchar_t* fileName);
//��������
void stopsound(int sid);
//��ʼ����
void playsound(int sid, int repeat);