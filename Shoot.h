#pragma once
#include "Game.h"
#include "Music.h"
#include "Boom.h"
#include "Vector2.h"
#define XM  ((double)pMyself->x+WIDTH_ME/2)
#define YM  ((double)pMyself->y+36)
#define RADIUS_M  6
#define RADIUS_M_1 40
//扣血,参数分别为：敌机或我链表中的某个结点，扣减的血量，是攻击还是受伤
void DamageB(Node* p, int Hitpoints, int flag);
//全屏敌人扣血，参数为扣减血量
void DamageA(int Hitpoints);
//攻击判定 0 我打敌  1 敌打我
void Shoot(int flag);