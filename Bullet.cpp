#include "Bullet.h"


void Paint_Bullet(void)
{
	Node* p = pBullet->next;
	while (p != NULL)
	{
		switch (p->type)
		{
		case NORMAL:
			transparentimage(NULL, p->x, p->y, WIDTH_BULLET_ME_1, HEIGHT_BULLET_ME, 0, 0, WIDTH_BULLET_ME_1, HEIGHT_BULLET_ME, &zhujizidan);
			break;
		case UPDATE:
			transparentimage(NULL, p->x, p->y, WIDTH_BULLET_ME_2, HEIGHT_BULLET_ME, 161, 0, WIDTH_BULLET_ME_2, HEIGHT_BULLET_ME, &zhujizidan);
			break;
		case ULTRA:
			transparentimage(NULL, p->x, p->y, WIDTH_BULLET_ME_2, HEIGHT_BULLET_ME, 340, 0, 394-340, HEIGHT_BULLET_ME, &zhujizidan);
			break;
		}
		//p转向下一个结点
		p = p->next;
	}
}
void AddBullet_MeB(int flag, int x, int y)
{
	Node* pNew;
	switch (flag) {
	case NORMAL:
		//我机普通子弹
		pNew = (Node*)malloc(sizeof(Node));
		pNew->next = pBullet->next;
		pNew->x = x;
		pNew->y = y;
		pNew->type = NORMAL;
		pNew->width = WIDTH_BULLET_ME;
		pNew->height = HEIGHT_BULLET_ME;
		pNew->hitpoints = 1;
		pBullet->next = pNew;
		playsound(1, 0);
		break;
	case UPDATE:
		pNew = (Node*)malloc(sizeof(Node));
		pNew->next = pBullet->next;
		pNew->x = x;
		pNew->y = y;
		pNew->type = UPDATE;
		pNew->hitpoints = 1;
		pNew->width = WIDTH_BULLET_ME_2;
		pNew->height = HEIGHT_BULLET_ME;
		playsound(1, 0);
		pBullet->next = pNew;
		break;
	case ULTRA:
		pNew = (Node*)malloc(sizeof(Node));
		pNew->next = pBullet->next;
		pNew->x = x;
		pNew->y = y;
		pNew->type = ULTRA;
		pNew->hitpoints = 2;
		pNew->width = WIDTH_BULLET_ME_3;
		pNew->height = HEIGHT_BULLET_ME;
		pBullet->next = pNew;
		playsound(1, 0);

		break;
	}
}
void AddBullet_MeA(void) {
	int FDC = Frame.f_total - Frame.f_pause;
	int xl, xr, xm, y, ym;
	switch (pMyself->weaponlevel) {
	case 1:
		xl = pMyself->x + pMyself->width / 2 - WIDTH_BULLET_ME_1 / 2 - 30;
		xr = pMyself->x + pMyself->width / 2 - WIDTH_BULLET_ME_1 / 2 + 30;
		xm = pMyself->x + pMyself->width / 2 - WIDTH_BULLET_ME_1 / 2;
		y = pMyself->y - HEIGHT_BULLET_ME + 130;
		ym = pMyself->y - HEIGHT_BULLET_ME + 100;
		if (FDC % 36 == 0 && FDC >300)
		{
			AddBullet_MeB(NORMAL, xl, y);
			AddBullet_MeB(NORMAL, xr, y);

		}
		else if (FDC % 18 == 0 && FDC > 300)
		{
			AddBullet_MeB(NORMAL, xm, y);

		}
		break;
	case 2:
		xl = pMyself->x + pMyself->width / 2 - WIDTH_BULLET_ME_2 / 2 - 30;
		xr = pMyself->x + pMyself->width / 2 - WIDTH_BULLET_ME_2 / 2 + 30;
		xm = pMyself->x + pMyself->width / 2 - WIDTH_BULLET_ME_2 / 2;
		y = pMyself->y - HEIGHT_BULLET_ME + 130;
		ym = pMyself->y - HEIGHT_BULLET_ME + 100;

		if (FDC % 18 == 0 && FDC>300) {
			AddBullet_MeB(UPDATE, xm, ym);
			AddBullet_MeB(UPDATE, xl, y);
			AddBullet_MeB(UPDATE, xr, y);
		}
		break;
	case 3:
		xl = pMyself->x + pMyself->width / 2 - WIDTH_BULLET_ME_2 / 2 - 30;
		xr = pMyself->x + pMyself->width / 2 - WIDTH_BULLET_ME_2 / 2 + 30;
		xm = pMyself->x + pMyself->width / 2 - WIDTH_BULLET_ME_2 / 2;
		y = pMyself->y - HEIGHT_BULLET_ME + 130;
		ym = pMyself->y - HEIGHT_BULLET_ME + 100;
		if (FDC % 15 == 0 && FDC > 300) {
			AddBullet_MeB(ULTRA, xm, ym);
			AddBullet_MeB(ULTRA, xl, y);
			AddBullet_MeB(ULTRA, xr, y);
		}
	}

}
void Move_Bullet_Me(void)
{
	Node* p = pBullet->next;
	while (p != NULL)
	{
		switch (p->type)
		{
		case NORMAL:case UPDATE:
			p->y -= 10;											//将当前结点的子弹坐标上移
			break;
		case ULTRA:
			p -> y -= 11;
		}
		p = p->next;
	}
}