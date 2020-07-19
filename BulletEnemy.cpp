#include "BulletEnemy.h"

int Fire(Node* p)
{
	int f = Frame.f_total - Frame.f_pause;
	if (p->FireSwitch)
	{
		if (f - p->ff_fire >= p->fire_on)
		{
			//printf("开关将要关 %d\n", f - p->ff_fire);
			p->FireSwitch = 0;
			p->ff_fire = f;
		}
	}
	else if (p->FireSwitch == 0)
	{
		if (f - p->ff_fire >= p->fire_on) {
			//printf("开关将要开 %d\n", f - p->ff_fire);
			p->FireSwitch = 1;
			p->ff_fire = f;
		}
	}
	return p->FireSwitch;
}
void Paint_Bullet_Enemy(void)
{
	Node* p = pBullet_E->next;
	while (p != NULL)
	{

		switch (p->type)
		{
		case SSHOCKWAVE:
			if (p->theta >= 0)
				RotateImage(&yyy, &bullet1, p->theta);
			else
				RotateImage(&yyy, &bullet1, 2 * PI + p->theta);
			transparentimage(NULL, p->x, p->y, &yyy);
			break;
		case LONG:
			transparentimage(NULL, p->x, p->y, &bullet2);
			break;
		case REDBALL:
			transparentimage(NULL, p->x, p->y, &bullet3);
			break;
		case BOSSSHOCKWAVE:
			if (p->theta >= 0)
				RotateImage(&yyy, &bullet5, p->theta);
			else
				RotateImage(&yyy, &bullet5, 2 * PI - p->theta);
			transparentimage(NULL, p->x, p->y, &yyy);
			break;
		case RHOMBUS:
			transparentimage(NULL, p->x, p->y, &bullet4);
			break;
		}

		p = p->next;
	}
}
void Move_Bullet_Enemy(void) {
	Node* p = pBullet_E->next;
	while (p != NULL) {
		int FDC = Frame.f_total - Frame.f_pause - p->f_create;
		//printf("speed=%f x=%d y=%d x0=%d y0=%d theta=%f\n", p->speed, p->x,p->y,p->x0,p->y0,p->theta);
		p->x = (int)(p->x0 - p->speed * FDC * sin(p->theta));
		p->y = (int)(p->y0 + p->speed * FDC * cos(p->theta));

		p = p->next;
	}
}
void AddBullet_EnemyA(void)
{
	Node* p = pEnemy->next;
	int FDC = Frame.f_total - Frame.f_pause;
	Vector2* v1 = (Vector2*)malloc(sizeof(Vector2));
	Vector2* v2 = (Vector2*)malloc(sizeof(Vector2));

	while (p != NULL)
	{
		if (Fire(p))
		{
			switch (p->type)
			{
			case NORMAL:case NORMALB:

				if (FDC % 200 == 0 && FDC > 0)
				{
					set(v1, 0, HEIGHT);
					set(v2, (double)pMyself->x - p->x, (double)pMyself->y - p->y);
					double theta = angle(v1, v2);
					AddBullet_EnemyB(SSHOCKWAVE, p->x + p->width / 2 - WIDTH_BULLET_SSHOCKWAVE / 2, p->y + HEIGHT_BULLET_SSHOCKWAVE, theta);
				}
				break;
			case GUARD:
				if (FDC % 30 == 0 && FDC > 0)
				{
					double theta = PI / 32;
					for (int i = 12; i >= -12; i--)
						AddBullet_EnemyB(REDBALL, (int)((double)p->x + p->width / 2 - (double)WIDTH_BULLET_REDBALL / 2),(int)( (double)p->y + (double)HEIGHT_BULLET_REDBALL), i * theta);


				}
				if (FDC % 150 == 0 && FDC > 0)
				{
					set(v1, 0, HEIGHT);
					set(v2, (double)pMyself->x - p->x, (double)pMyself->y - p->y);
					double theta = angle(v1, v2);
					AddBullet_EnemyB(SSHOCKWAVE, p->x + p->width / 2 - WIDTH_BULLET_SSHOCKWAVE / 2, p->y + HEIGHT_BULLET_SSHOCKWAVE, theta);
				}
				break;
			case RAIDER:
				if (FDC % 10 == 0 && FDC > 0)
				{
					static int isClockWise = 1;
					static double theta = 0;

					for (int num = 6; num >= -6; num--)
						AddBullet_EnemyB(RHOMBUS, (double)p->x + p->width / 2 - (double)WIDTH_BULLET_RHOMBUS / 2, (double)p->y + p->height, theta - num * PI / 12);
					if (theta < PI / 10 && isClockWise)
						theta += PI / 12;
					else if (theta > -PI / 10 && !isClockWise)
						theta -= PI / 12;
					if (theta >= PI / 10) isClockWise = 0;
					else if (theta <= -PI / 10) isClockWise = 1;
				}
				break;

			}
		}
		p = p->next;
	}
}

void AddBullet_EnemyB(int flag, int x0, int y0, double theta)
{
	//theta为相对于初始坐标的角度，顺时针为负
	Node* pNew;

	switch (flag) {
	case SSHOCKWAVE:
		//生成时应该指定目标
		pNew = (Node*)malloc(sizeof(Node));
		pNew->next = pBullet_E->next;
		pNew->type = SSHOCKWAVE;
		pNew->theta = theta;
		pNew->x0 = pNew->x = x0;
		pNew->y0 = pNew->y = y0;
		pNew->hitpoints = 5;
		pNew->speed = 3;
		pNew->f_create = Frame.f_total - Frame.f_pause;
		pNew->width = WIDTH_BULLET_SSHOCKWAVE;
		pNew->height = HEIGHT_BULLET_SSHOCKWAVE;
		pBullet_E->next = pNew;
		break;
	case LONG:
		pNew = (Node*)malloc(sizeof(Node));
		pNew->next = pBullet_E->next;
		pNew->type = LONG;
		pNew->theta = theta;
		pNew->speed = 3;
		pNew->x0 = pNew->x = x0;
		pNew->y0 = pNew->y = y0;
		//下面两个是子弹的坐标，以子弹图片左上角为基准
		pNew->width = WIDTH_BULLET_LONG;
		pNew->f_create = Frame.f_total - Frame.f_pause;
		pNew->height = HEIGHT_BULLET_LONG;
		pNew->hitpoints = 15;
		pBullet_E->next = pNew;
		break;
	case REDBALL:

		pNew = (Node*)malloc(sizeof(Node));
		pNew->next = pBullet_E->next;
		pNew->type = REDBALL;
		pNew->speed = 2;

		pNew->f_create = Frame.f_total - Frame.f_pause;
		pNew->x0 = pNew->x = x0;
		pNew->y0 = pNew->y = y0;
		pNew->f_create = Frame.f_total - Frame.f_pause;
		pNew->theta = theta;
		pNew->width = WIDTH_BULLET_REDBALL;
		pNew->height = HEIGHT_BULLET_REDBALL;
		pNew->hitpoints = 5;
		pBullet_E->next = pNew;
		break;
	case RHOMBUS:
		pNew = (Node*)malloc(sizeof(Node));
		pNew->next = pBullet_E->next;
		pNew->type = RHOMBUS;
		pNew->x0 = pNew->x = x0;
		pNew->y0 = pNew->y = y0;
		pNew->f_create = Frame.f_total - Frame.f_pause;
		pNew->theta = theta;
		pNew->speed = 2;

		pNew->width = WIDTH_BULLET_RHOMBUS;
		pNew->height = HEIGHT_BULLET_RHOMBUS;
		pNew->hitpoints = 5;
		pBullet_E->next = pNew;
		break;
	case BOSSSHOCKWAVE:
		pNew = (Node*)malloc(sizeof(Node));
		pNew->f_create = Frame.f_total - Frame.f_pause;
		pNew->next = pBullet_E->next;
		pNew->type = BOSSSHOCKWAVE;
		pNew->theta = theta;
		pNew->speed = 2;

		pNew->x0 = pNew->x = x0;
		pNew->y0 = pNew->y = y0;
		pNew->width = WIDTH_BULLET_BOSSSHOCKWAVE;
		pNew->height = HEIGHT_BULLET_BOSSSHOCKWAVE;
		pNew->hitpoints = 5;
		pBullet_E->next = pNew;
		break;

	}



}