#pragma once
#include "Game.h"
#include <math.h>
int GetLevels();
//���Ƹ��ֵл�
void Paint_Plane_Enemy(void);
//�л��ƶ�
void Move_Enemy(void);
//���ɸ��ֵл�
void AddEnemy(int flag, int mod,int x0, int y0 ,double theta);
//��ȡ�ڳ��л�����
int NumOfEnemies();
void DifficultyRise(void);
void DifiicultyReset(void);