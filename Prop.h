#pragma once
#include "Game.h"
#define WEAPON_UPDATE 0
#define SHIELD 1
#define HEALTHPOT 2
//�õ�����
void Get_prop(void);
//ɾ��
void DeletePropB(int x, int y);
void DeletePropA(void);
//���Ƶ���
void Paint_prop();
//�ƶ�����
void Move_prop(void);
//���ӵ���
void Addprop(int flag);


