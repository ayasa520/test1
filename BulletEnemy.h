#pragma once
#include <math.h>
#include "Game.h"
#include "Vector2.h"
//���Ƶл������ӵ�
void Paint_Bullet_Enemy(void);
//�л��ӵ��ƶ�
void Move_Bullet_Enemy(void);
//���ɸ��ֵл��ӵ�
void AddBullet_EnemyA(void);

void AddBullet_EnemyB(int flag, int x0, int y0, double theta);
//�л��Ƿ񿪻�Ҫ�޸�Ϊ��ʱ����ҹ���
int Fire(Node* p);