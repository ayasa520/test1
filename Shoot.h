#pragma once
#include "Game.h"
#include "Music.h"
#include "Boom.h"
#include "Vector2.h"
#define XM  ((double)pMyself->x+WIDTH_ME/2)
#define YM  ((double)pMyself->y+36)
#define RADIUS_M  6
#define RADIUS_M_1 40
//��Ѫ,�����ֱ�Ϊ���л����������е�ĳ����㣬�ۼ���Ѫ�����ǹ�����������
void DamageB(Node* p, int Hitpoints, int flag);
//ȫ�����˿�Ѫ������Ϊ�ۼ�Ѫ��
void DamageA(int Hitpoints);
//�����ж� 0 �Ҵ��  1 �д���
void Shoot(int flag);