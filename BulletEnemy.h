#pragma once
#include <math.h>
#include "Game.h"
#include "Vector2.h"
//绘制敌机各种子弹
void Paint_Bullet_Enemy(void);
//敌机子弹移动
void Move_Bullet_Enemy(void);
//生成各种敌机子弹
void AddBullet_EnemyA(void);

void AddBullet_EnemyB(int flag, int x0, int y0, double theta);
//敌机是否开火（要修改为与时间轴挂钩）
int Fire(Node* p);