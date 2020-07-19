#pragma once
#include "Game.h"
#include <math.h>
int GetLevels();
//绘制各种敌机
void Paint_Plane_Enemy(void);
//敌机移动
void Move_Enemy(void);
//生成各种敌机
void AddEnemy(int flag, int mod,int x0, int y0 ,double theta);
//获取在场敌机数量
int NumOfEnemies();
void DifficultyRise(void);
void DifiicultyReset(void);