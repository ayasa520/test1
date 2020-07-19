#pragma once
#include "Game.h"
#define WEAPON_UPDATE 0
#define SHIELD 1
#define HEALTHPOT 2
//得到道具
void Get_prop(void);
//删除
void DeletePropB(int x, int y);
void DeletePropA(void);
//绘制道具
void Paint_prop();
//移动道具
void Move_prop(void);
//增加道具
void Addprop(int flag);


