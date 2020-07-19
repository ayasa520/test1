#include "PlaneEnemy.h"
int levels = 0;
void DifficultyRise(void)
{
	levels++;
}
void DifiicultyReset(void)
{
	levels = 0;
}
int GetLevels()
{
	return levels;
}
void Paint_Plane_Enemy(void) {
	Node* p = pEnemy->next;
	while (p != NULL)
	{
		IMAGE pimg;
		switch (p->type)
		{
		case NORMAL:case NORMALB:
			if (p->type == NORMAL)
				pimg = enemy_normal;
			else
				pimg = enemy_normalb;
			if (p->movemod == LEFTARC)
			{
				if (p->x > 0)
					RotateImage(&yyy1, &pimg, atan((double)p->y / p->x));
				else
					RotateImage(&yyy1, &pimg, PI / 2 + atan((double)-p->x / p->y));

				transparentimage(NULL, p->x, p->y, &yyy1);		//绘制当前结点的敌机图像

			}
			else if (p->movemod == RIGHTARC)
			{
				if (p->x < WIDTH)
					RotateImage(&yyy2, &pimg, 2 * PI - atan((double)p->y / ((double)WIDTH - p->x)));
				else
					RotateImage(&yyy2, &pimg, 2 * PI - PI / 2 - atan((double)p->x - WIDTH / p->y));
				transparentimage(NULL, p->x, p->y, &yyy2);		//绘制当前结点的敌机图像
			}
			else if (p->movemod == STRAIGHT)
			{
				//printf("theta=%f\n", p->theta);
				if (p->theta >= 0)
					RotateImage(&yyy2, &pimg, p->theta);
				else
					RotateImage(&yyy2, &pimg, 2 * PI + p->theta);
				transparentimage(NULL, p->x, p->y, &yyy2);
			}
			break;
		case GUARD:
			transparentimage(NULL, p->x, p->y, p->width, p->height, &enemy_guard);
			break;
		case RAIDER:
			transparentimage(NULL, p->x, p->y, p->width, p->height, &enemy_raider);
			break;
		case QUICKER:
			transparentimage(NULL, p->x, p->y, p->width, p->height, &enemy_quicker);
			break;
		case BOSS:
			transparentimage(NULL, p->x, p->y, p->width, p->height, &enemy_boss);
			break;


		}

		double b = ((double)p->blood / (double)p->fullblood);
		int x = p->x;
		int y = p->y;
		int w = p->width;
		int h = p->height;
		transparentimage(NULL, x, y -20, b*w, w/20, 0, 0, 487, 15, &blood_enemy);
		p = p->next;
	}

}
void Move_Enemy(void)
{
	
	Node* p = pEnemy->next;
	//double a, b;
	while (p != NULL) {
		int FDC = Frame.f_total - Frame.f_pause - p->f_create;
		double theta;
		switch (p->movemod)
		{
		case LEFTARC:
			theta = -PI / 4 + FDC * p->speed / (WIDTH / 2);
			p->theta = theta;
			p->x = (WIDTH / 2) * cos(theta) + WIDTH / 4;
			p->y = (WIDTH / 2) * sin(theta);
			break;
		case RIGHTARC:
			theta = 5 * PI / 4 - FDC * p->speed / (WIDTH / 2);
			p->theta = theta - PI;
			p->x = WIDTH + (WIDTH / 2) * cos(theta) - (double)WIDTH / 4;
			p->y = (WIDTH / 2) * sin(theta);
			break;


		case STRAIGHT:
			//	printf("x0%d y0%d x%d y%d 角度%f\n", p->x0, p->y0, p->x, p->y,p->theta);
			p->x = p->x0 - p->speed * FDC * sin(p->theta);
			p->y = p->y0 + p->speed * FDC * cos(p->theta);
			break;
		case STOP:
			if (p->y <= 200) {
			p->x = p->x0 - p->speed * FDC * sin(p->theta);
			p->y = p->y0 + p->speed * FDC * cos(p->theta);
			//printf("x=%d,y=%d\n", p->x, p->y);
		}
			break;
		}
		p = p->next;
	}
}
int NumOfEnemies()
{
	int cnt = 0;
	Node* p =pBullet_E->next;
	while (p != NULL)
	{
		cnt++;
		p = p->next;
	}
	return cnt;
}
void AddEnemy(int flag, int mod,  int x0 , int y0 ,double theta) {
	//空指针头插法 ,xt,yt为指向坐标，x0,y0为初始坐标,theta为偏转角
	Node* pNew;
	switch (flag) {
	case NORMALB: case NORMAL:
		//普通敌人
		if (pMyself->blood != 0) {
			pNew = (Node*)malloc(sizeof(Node));
			pNew->next = pEnemy->next;
			pNew->x = x0;
			pNew->y = y0;
			pNew->fullblood = pNew->blood = 4+levels*2;
			pNew->type = flag;
			pNew->FireSwitch = 0;
			pNew->f_create = Frame.f_total - Frame.f_pause;
			pNew->fire_on = 200+levels+50;
			pNew->fire_off = 200;
			pNew->ff_fire = 0;
			pNew->width = WIDTH_NORMAL;
			pNew->height = HEIGHT_NORMAL;
			pNew->movemod = mod;
			pNew->speed =3;
			pEnemy->next = pNew;
			pNew->x0 = x0;
			pNew->y0 = y0;
			pNew->theta = theta;
		//	printf("mod %d x0%d y0%d x%d y%d 角度%f\n",pNew->movemod, pNew->x0, pNew->y0, pNew->x, pNew->y, pNew->theta);

		}
		break;
	case BOSS:
		pNew = (Node*)malloc(sizeof(Node));
		pNew->next = pEnemy->next;
		pNew->x = WIDTH / 2 - WIDTH_BOSS / 2;
		pNew->y = -HEIGHT_BOSS;
		pNew->fullblood = pNew->blood = 500;
		pNew->type = BOSS;
		pNew->f_create = Frame.f_total - Frame.f_pause;
		pNew->ff_fire = 0;
		pNew->width = WIDTH_BOSS;
		pNew->height = HEIGHT_BOSS;
		pNew->movemod = mod;
		pNew->fire_on = 100;
		pNew->theta = theta; 
		pNew->fire_off = 200;
		//printf("生成大boss一个\n");
		boss = 1;
		pEnemy->next = pNew;
		break;
	case QUICKER:
		if (pMyself->blood != 0) {
			pNew = (Node*)malloc(sizeof(Node));
			pNew->next = pEnemy->next;
			pNew->x = x0;
			pNew->y = -HEIGHT_QUICKER;
			pNew->fullblood = pNew->blood = 20+levels*10;
			pNew->type = QUICKER;
			pNew->width = WIDTH_QUICKER;
			pNew->height = HEIGHT_QUICKER;
			pNew->FireSwitch = 1;
			pNew->f_create = Frame.f_total - Frame.f_pause;
			pNew->theta = theta;

			pNew->ff_fire = 0;
			pNew->movemod = mod;
			//printf("生成速者一个\n");
			pNew->fire_on = 200;
			pNew->fire_off = 200;
			pEnemy->next = pNew;
			pNew->speed = 2;
		}
		break;
	case RAIDER:
		if (pMyself->blood != 0) {
			pNew = (Node*)malloc(sizeof(Node));
			pNew->next = pEnemy->next;
			srand((unsigned)time(NULL));
			pNew->x  = rand()%(WIDTH-WIDTH_RAIDER);
			pNew->y = -HEIGHT_RAIDER;
			pNew->fullblood = pNew->blood = 100+levels*40;
			pNew->type = RAIDER;
			pNew->FireSwitch = 1;
			pNew->f_create = Frame.f_total - Frame.f_pause;
			//printf("创建时间：%d\n", pNew->f_create);
			pNew->ff_fire = 0;
			pNew->theta = theta;
			pNew->fire_on = 200;
			pNew->fire_off = 200;
			pNew->width = WIDTH_RAIDER;
			pNew->height = HEIGHT_RAIDER;
			pNew->movemod = mod;
			//printf("生成突击者一个\n");
			pEnemy->next = pNew;
			pNew->speed = 1;
		}
		break;
	case GUARD:
		if (pMyself->blood != 0) {
			pNew = (Node*)malloc(sizeof(Node));
			pNew->next = pEnemy->next;
			pNew->x0=pNew->x = x0;
			pNew->y0=pNew->y = -HEIGHT_GUARD;
			pNew->theta = theta;
			pNew->fullblood = pNew->blood = 50+levels*20;
			pNew->type = GUARD;
			pNew->FireSwitch = 1;
			pNew->f_create = Frame.f_total - Frame.f_pause;
			pNew->ff_fire = 0;
			pNew->fire_on = 200;
			pNew->fire_off = 200;		
			pNew->width = WIDTH_GUARD;
			pNew->height = HEIGHT_GUARD;
			pNew->movemod = mod;
			pNew->speed = 0.6;
			//printf("生成守卫一个\n");
			pEnemy->next = pNew;
		}
		break;
	}
}
