#pragma once
#include "Game.h"
#include "Music.h"
//绘制我机各种子弹
void Paint_Bullet(void);
//生成我机各种子弹
void AddBullet_MeB(int flag, int x, int y);
//按照时间、等级增加子弹
void AddBullet_MeA(void);
//我机子弹移动
void Move_Bullet_Me(void);