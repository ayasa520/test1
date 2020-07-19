#include "Shoot.h"




void DamageB(Node* p, int Hitpoints, int flag)
{

	p->blood -= Hitpoints;
	if (p->blood <= 0)																//若血量为0
	{
		switch (flag)
		{
		case ATTACK:																//敌机血量为零
			score++;
			playsound(2, 0);
			AddNodeboom(p->x, p->y, p->type, p->width);										//爆炸链表添加
			Delete(0, p->x, p->y);
			break;
		case INJURE:																//我血量为零
			playsound(2, 0);
			AddNodeboom(p->x, p->y, p->type, p->width);										//爆炸链表添加
			Delete(0, p->x, p->y);
			break;
		}
	}
}
void DamageA(int Hitpoints)
{
	Node* p = pEnemy->next;
	while (p != NULL)
	{
		p->blood -= Hitpoints;
		if (p->blood <= 0)															//若血量为0
		{
			score++;
			playsound(2, 0);
			AddNodeboom(p->x, p->y, p->type, p->width);										//爆炸链表添加
			Delete(0, p->x, p->y);
		}
		p = p->next;
	}
}
bool ProjectionToCompare(Vector2* v1, Vector2* v2, Vector2* axis)
{
	//判断
	int i;
	int idxmax = 1;
	int idxmin = 1;
	double promodmax = 0;
	double promodmin = 1000;
	int mod;
	for (i = 1; i < 5; i++)
	{
		//printf("传值进来v[%d] %f %f\n", i, v1[i]);
		mod = (int)module(&projection(&v1[i],axis));
		if (mod > promodmax)
		{
			idxmax = i;
			promodmax = mod;
		}
		if (mod < promodmin)
		{
			idxmin = i;
			promodmin = mod;
		}
	}
	double Cirpromodmin, Cirpromodmax;
	if (!pMyself->invincible) {
		Cirpromodmin = module(&projection(v2,axis)) - RADIUS_M;
		Cirpromodmax = module(&projection(v2, axis)) + RADIUS_M;
	}
	else
	{
		Cirpromodmin = module(&projection(v2, axis)) - RADIUS_M_1;
		Cirpromodmax = module(&projection(v2, axis)) + RADIUS_M_1;
	}
	if (!(Cirpromodmax<promodmin || Cirpromodmin>promodmax))
		return TRUE;
	else
		return FALSE;

}
bool Judge(Node* p)
{
	Vector2 vm;
	set(&vm,XM, YM);
	int isHit = 0;
	switch (p->type)
	{
	case SSHOCKWAVE:
	{

		Vector2 v[5];
		int i = 1, index = 1;
		double Distance;
		double MinDistance = 1000;
		//以中心为起点（相当于把图片中心平移到了原点）
		set(&v[0],0, 0);
		set(&v[1],-9, -13);
		set(&v[2],9, -13);
		set(&v[3],-9, 25);
		set(&v[4],9, 25);
		//printf("初始 %f %f\n", v[0]);
		//printf("初始 %f %f\n", v[1]);
		//printf("初始 %f %f\n", v[2]);
		//printf("初始 %f %f\n", v[3]);
		//printf("初始 %f %f\n", v[4]);

		for (i = 1; i < 5; i++)
			rotate(&v[i],&v[0], p->theta);
		/*	printf("旋转后 %f %f\n", v[0]);
			printf("旋转后 %f %f\n", v[1]);
			printf("旋转后 %f %f\n", v[2]);
			printf("旋转后 %f %f\n", v[3]);
			printf("旋转后 %f %f\n", v[4]);*/


		int NewWidth = p->height * sin(fabs(p->theta)) + p->width * cos(p->theta);
		int NewHeight = p->width * sin(fabs(p->theta)) + p->height * cos(p->theta);

		double MidX = (double)p->x + NewWidth / 2;
		double MidY = (double)p->y + NewHeight / 2;
		//	solidrectangle(MidX, MidY, MidX+199, MidY+ 1);
		//	printf("旋转后中心点 x=%f y=%f\n", MidX,MidY);

			//做完这个循环后，各个向量的数值代表对应点的坐标（以原点为起点）
		for (i = 1; i < 5; i++)
		{
			//	printf("加法前点坐标 v[%d].x=%f y=%f\n",i, v[i]);
			//	printf("旋转后对应点坐标 Midx=%f midy=%f\n", MidX,MidY);

			v[i].x += MidX;
			v[i].y += MidY;

			//	printf("旋转后对应点坐标 x=%f y=%f\n", v[i]);

		}

		for (i = 1; i < 5; i++)
		{
			Distance = distance(&v[i],&vm);
			if (MinDistance > Distance)
			{
				MinDistance = Distance;
				index = i;
			}
		}
		//矩形轴1和2 3：
		Vector2 Axis1, Axis2, Axis3;
		Axis1.x = v[2].x - v[1].x;
		Axis1.y = v[2].y - v[1].y;
		Axis2.x = v[3].x - v[1].x;
		Axis2.y = v[3].y - v[1].y;
		Axis3.x = XM - v[index].x;
		Axis3.y = YM - v[index].y;
		/*	printf("轴向量1 %f %f\n", Axis1);
			printf("轴向量2 %f %f\n", Axis2);
			printf("轴向量3 %f %f\n", Axis3);*/

		int cnt = 0;
		if (ProjectionToCompare(v, &vm, &Axis1)) cnt += 1;
		if (ProjectionToCompare(v, &vm, &Axis2)) cnt += 1;
		if (ProjectionToCompare(v, &vm, &Axis3)) cnt += 1;
		if (cnt == 3) isHit = 1;


		break; }
	case REDBALL:case RHOMBUS:
	{
		Vector2 v1;
		double r;
		double x1 = p->x + 30.5;
		double y1 = p->y + 30.5;
		set(&v1,x1, y1);
		double dis = distance(&v1,&vm);
		if (pMyself->invincible == 0)
			r = RADIUS_M;
		else
			r = RADIUS_M_1;
		if (dis < 8.5 + r)
			isHit = 1;
		break;
	}
	}
	return isHit;
}
void Shoot(int flag)
{
	Node* p_E, * p_B;
	int frn = Frame.f_total - Frame.f_pause;


	switch (flag)
	{
	case 0:
		p_E = pEnemy->next;
		p_B = pBullet->next;
		while (p_E != NULL) 
		{
			p_B = pBullet->next;
			while (p_B != NULL)
			{
				if (p_B->x >= p_E->x - WIDTH_BULLET_ME / 2 && p_B->x <= p_E->x + p_E->width - WIDTH_BULLET_ME / 2 &&		//子弹有没有碰到敌人
					p_B->y >= p_E->y && p_B->y <= p_E->y + p_E->height - 20) {
					DamageB(p_E, p_B->hitpoints, ATTACK);
					Delete(1, p_B->x, p_B->y);
					p_E = pEnemy->next;
					break;
				}
				else 
					p_B = p_B->next;
			}
			if (p_E != NULL) 
				p_E = p_E->next;
		}
		break;
	case 1:
		p_B = pBullet_E->next;
		while (p_B != NULL)
		{
			if (Judge(p_B))
			{
				if (pMyself->invincible == 0)
					DamageB(pMyself, p_B->hitpoints, INJURE);
				else if (frn-pMyself->invincible  >= 1000)
					pMyself->invincible = 0;
				Delete(2, p_B->x, p_B->y);
				p_B = pBullet_E->next;
			}
			else
				p_B = p_B->next;
		}
		break;
	}
}