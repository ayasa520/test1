#include "Shoot.h"




void DamageB(Node* p, int Hitpoints, int flag)
{

	p->blood -= Hitpoints;
	if (p->blood <= 0)																//��Ѫ��Ϊ0
	{
		switch (flag)
		{
		case ATTACK:																//�л�Ѫ��Ϊ��
			score++;
			playsound(2, 0);
			AddNodeboom(p->x, p->y, p->type, p->width);										//��ը�������
			Delete(0, p->x, p->y);
			break;
		case INJURE:																//��Ѫ��Ϊ��
			playsound(2, 0);
			AddNodeboom(p->x, p->y, p->type, p->width);										//��ը�������
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
		if (p->blood <= 0)															//��Ѫ��Ϊ0
		{
			score++;
			playsound(2, 0);
			AddNodeboom(p->x, p->y, p->type, p->width);										//��ը�������
			Delete(0, p->x, p->y);
		}
		p = p->next;
	}
}
bool ProjectionToCompare(Vector2* v1, Vector2* v2, Vector2* axis)
{
	//�ж�
	int i;
	int idxmax = 1;
	int idxmin = 1;
	double promodmax = 0;
	double promodmin = 1000;
	int mod;
	for (i = 1; i < 5; i++)
	{
		//printf("��ֵ����v[%d] %f %f\n", i, v1[i]);
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
		//������Ϊ��㣨�൱�ڰ�ͼƬ����ƽ�Ƶ���ԭ�㣩
		set(&v[0],0, 0);
		set(&v[1],-9, -13);
		set(&v[2],9, -13);
		set(&v[3],-9, 25);
		set(&v[4],9, 25);
		//printf("��ʼ %f %f\n", v[0]);
		//printf("��ʼ %f %f\n", v[1]);
		//printf("��ʼ %f %f\n", v[2]);
		//printf("��ʼ %f %f\n", v[3]);
		//printf("��ʼ %f %f\n", v[4]);

		for (i = 1; i < 5; i++)
			rotate(&v[i],&v[0], p->theta);
		/*	printf("��ת�� %f %f\n", v[0]);
			printf("��ת�� %f %f\n", v[1]);
			printf("��ת�� %f %f\n", v[2]);
			printf("��ת�� %f %f\n", v[3]);
			printf("��ת�� %f %f\n", v[4]);*/


		int NewWidth = p->height * sin(fabs(p->theta)) + p->width * cos(p->theta);
		int NewHeight = p->width * sin(fabs(p->theta)) + p->height * cos(p->theta);

		double MidX = (double)p->x + NewWidth / 2;
		double MidY = (double)p->y + NewHeight / 2;
		//	solidrectangle(MidX, MidY, MidX+199, MidY+ 1);
		//	printf("��ת�����ĵ� x=%f y=%f\n", MidX,MidY);

			//�������ѭ���󣬸�����������ֵ�����Ӧ������꣨��ԭ��Ϊ��㣩
		for (i = 1; i < 5; i++)
		{
			//	printf("�ӷ�ǰ������ v[%d].x=%f y=%f\n",i, v[i]);
			//	printf("��ת���Ӧ������ Midx=%f midy=%f\n", MidX,MidY);

			v[i].x += MidX;
			v[i].y += MidY;

			//	printf("��ת���Ӧ������ x=%f y=%f\n", v[i]);

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
		//������1��2 3��
		Vector2 Axis1, Axis2, Axis3;
		Axis1.x = v[2].x - v[1].x;
		Axis1.y = v[2].y - v[1].y;
		Axis2.x = v[3].x - v[1].x;
		Axis2.y = v[3].y - v[1].y;
		Axis3.x = XM - v[index].x;
		Axis3.y = YM - v[index].y;
		/*	printf("������1 %f %f\n", Axis1);
			printf("������2 %f %f\n", Axis2);
			printf("������3 %f %f\n", Axis3);*/

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
				if (p_B->x >= p_E->x - WIDTH_BULLET_ME / 2 && p_B->x <= p_E->x + p_E->width - WIDTH_BULLET_ME / 2 &&		//�ӵ���û����������
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