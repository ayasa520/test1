#define _CRT_SECURE_NO_WARNINGS
#include <conio.h>
#include <time.h>

#include <stdlib.h>
#include <graphics.h>
#include "Game.h"
#include "Prop.h"
#include "Plane.h"
#include "Music.h"
#include "Shoot.h"
#include "BulletEnemy.h"
#include "Boom.h"
#include "Resource.h"
#include "Bullet.h"
#include "Interface.h"
#include "PlaneEnemy.h"
#include "Operate.h"
#include "Score.h"
#pragma comment(lib,"MSIMG32.LIB")
#pragma comment(lib,"Winmm.lib")

TIME imer;
int score;												//�÷�
typedef int SOUND;

Prop* prop;
Boom* pBoom;
Node* pBullet;												//�ӵ�
Node* pBullet_E;											//�л��ӵ�
Node* pEnemy;												//�л�
Node* pMyself;												//�һ�

int num[10];												//�÷�ÿһλ��,��ȫ���Է�������
int boss = 0;												//�Ƿ����boss
FRAME Frame;
struct CoverButton CoverButton;
struct Stage stage;
double lct = 0;													//��ͼ����

double distance(double x1, double y1, double x2, double y2)
{
	return sqrt(((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)));
}
void RotateImage(IMAGE* pTo, IMAGE* pFrom, double rad)
{
	IMAGE* pWorking = GetWorkingImage();
	SetWorkingImage(pFrom);
	int iWidth = getwidth();
	int iHeight = getheight();												// ��ȡԭͼ����
	while (rad > 2 * PI)													// ���򻡶�
		rad -= 2 * PI;

	double pad = rad;														// ������
	if (pad > PI / 2 && pad <= PI)
	{
		pad -= PI / 2;
		pad = PI / 2 - pad;
	}
	else if (pad > PI && pad <= PI / 2 * 3)
	{
		pad -= PI;
	}
	else if (pad > PI / 2 * 3 && pad <= PI * 2)
	{
		pad -= PI / 2 * 3;
		pad = PI / 2 - pad;
	}

	int	tWidth = int(iWidth * cos(pad) + iHeight * sin(pad));
	int	tHeight = int(iHeight * cos(pad) + iWidth * sin(pad));				// ������ͼ��С

	int iMinX = -(iWidth / 2), iMinY = -(iHeight / 2);
	int iMaxX = iMinX + iWidth, iMaxY = iMinY + iHeight;					// ����ԭͼ��С��������

	int tMinX = -(tWidth / 2), tMinY = -(tHeight / 2);
	int tMaxX = tMinX + tWidth, tMaxY = tMinY + tHeight;					// ������ͼ��С��������

	setorigin(-iMinX, -iMinY);												// ����ͼƬ����Ϊԭ��

	SetWorkingImage(NULL);
	pTo->Resize(tWidth, tHeight);											// ��ʼ����ͼ

	DWORD* dst = GetImageBuffer(pTo);
	DWORD* src = GetImageBuffer(pFrom);										// ��ȡ��ͼ��ԭͼ�Ļ�����

	SetWorkingImage(pTo);
	for (int y1 = 0; y1 < tHeight; y1++)
	{
		for (int x1 = 0; x1 < tWidth; x1++)
			dst[x1] = 0x00000000;
		dst += tWidth;
	}

	SetWorkingImage(pWorking);
	for (int y1 = 0; y1 < tHeight; y1++)									// ��ʼ����ͼ
		dst -= tWidth;

	for (int y1 = tMinY; y1 < tMaxY; y1++)
	{
		for (int x1 = tMinX; x1 < tMaxX; x1++)
		{
			int x = int(x1 * cos(rad) - y1 * sin(rad));
			int y = int(x1 * sin(rad) + y1 * cos(rad));						// ����任������

			int sxy = (iHeight - (y - iMinY) - 1) * iWidth + (x - iMinX);
			int dxy = (tHeight - (y1 - tMinY) - 1) * tWidth + (x1 - tMinX);	// ���������ڻ�������λ��

			if (x >= iMinX && x < iMaxX && y >= iMinY && y < iMaxY)			// Խ������
				dst[dxy] = src[sxy];
		}
	}

	SetWorkingImage(pFrom);
	setorigin(0, 0);
	SetWorkingImage(pWorking);												// ��ԭԭͼ����
}
void transparentimage(IMAGE* dstimg, int x, int y, IMAGE* srcimg)
{
	DWORD* dst = GetImageBuffer(dstimg);
	DWORD* src = GetImageBuffer(srcimg);
	int src_width = srcimg->getwidth();
	int src_height = srcimg->getheight();
	int dst_width = (dstimg == NULL ? getwidth() : dstimg->getwidth());
	int dst_height = (dstimg == NULL ? getheight() : dstimg->getheight());
	int iwidth = (x + src_width > dst_width) ? dst_width - x : src_width;
	int iheight = (y + src_height > dst_height) ? dst_height - y : src_height;
	if (x < 0) { src += -x;				iwidth -= -x;	x = 0; }
	if (y < 0) { src += src_width * -y;	iheight -= -y;	y = 0; }
	dst += dst_width * y + x;
	for (int iy = 0; iy < iheight; iy++)
	{
		for (int ix = 0; ix < iwidth; ix++)
		{
			int sa = ((src[ix] & 0xff000000) >> 24);
			int sr = ((src[ix] & 0xff0000) >> 16);
			int sg = ((src[ix] & 0xff00) >> 8);
			int sb = src[ix] & 0xff;
			int dr = ((dst[ix] & 0xff0000) >> 16);
			int dg = ((dst[ix] & 0xff00) >> 8);
			int db = dst[ix] & 0xff;
			dst[ix] = ((sr + dr * (255 - sa) / 255) << 16)
				| ((sg + dg * (255 - sa) / 255) << 8)
				| (sb + db * (255 - sa) / 255);
		}
		dst += dst_width;
		src += src_width;
	}
}
void transparentimage(IMAGE* dstimg, int xt, int yt, int wt, int ht,
	int xo, int yo, int wo, int ho, IMAGE* srcimg) {
	//xt ytΪĿ�괰�ڻ�ͼ����,wt htΪ���ƵĿ��,xo yo wo hoΪԴ�ļ���Ӧ����		
	HDC dstDC = GetImageHDC(dstimg);
	HDC srcDC = GetImageHDC(srcimg);
	//int w = srcimg->getwidth();
	//int h = srcimg->getheight(); 	// �ṹ��ĵ�������Ա��ʾ�����͸���ȣ�0 ��ʾȫ͸����255 ��ʾ��͸���� 	
	BLENDFUNCTION bf = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA }; 	// ʹ�� Windows GDI ����ʵ�ְ�͸��λͼ 	
	AlphaBlend(dstDC, xt, yt, wt, ht, srcDC, xo, yo, wo, ho, bf);
}
void transparentimage(IMAGE* dstimg, int x, int y, int w, int h, IMAGE* srcimg)
{
	HDC dstDC = GetImageHDC(dstimg);
	HDC srcDC = GetImageHDC(srcimg);
	int wo = srcimg->getwidth();
	int ho = srcimg->getheight();

	// �ṹ��ĵ�������Ա��ʾ�����͸���ȣ�0 ��ʾȫ͸����255 ��ʾ��͸����
	BLENDFUNCTION bf = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
	// ʹ�� Windows GDI ����ʵ�ְ�͸��λͼ
	AlphaBlend(dstDC, x, y, w, h, srcDC, 0, 0, wo, ho, bf);
}
void Delete(int flag, int x, int y) {
	Node* p;
	Node* ptr;
	Boom* pb;							//ɾ����ը������
	Boom* ptrb;
	switch (flag)
	{
	case 0:
		p = pEnemy->next;							//�����л�����ָ��ָ��ڶ���(����һ�ܵл�
		ptr = pEnemy;
		while (p != NULL) {
			if (p->y >= HEIGHT || (p->x == x && p->y == y))
			{
				ptr->next = p->next;
				free(p);							//��������Χ�Ľ��ɾ��
				p = nullptr;
			}
			else
				ptr = p;
			p = ptr->next;								//pת����һ�����
		}
		break;
	case 1:
		p = pBullet->next;							//�����һ��ӵ�����ָ��ָ��ڶ���
		ptr = pBullet;

		while (p != NULL) {							//���ѭ���ǻ�ɾ�������ӵ�

			if (p->y <= 0 || (p->x == x && p->y == y)) {
				ptr->next = p->next;
				free(p);						//��������Χ���ӵ�ɾ��
				p = nullptr;
			}
			else
				ptr = p;
			p = ptr->next;								//pת����һ�����
		}
		break;


	case 2:
		p = pBullet_E->next;							//�����ӵ�����ָ��ָ��ڶ���
		ptr = pBullet_E;
		while (p != NULL) {							//���ѭ���ǻ�ɾ������Խ���ӵ�

			if (p->y >= HEIGHT || p->y <= 0 || (p->x == x && p->y == y)) {
				//					printf("bullet:x=%d y=%d\n",p->x, p->y);
				//printf("%d %d\n", p->x, p->y);
				ptr->next = p->next;
				free(p);							//��������Χ���ӵ�ɾ��
				p = nullptr;
				//	printf("ɾ���ӵ�һ\n");
			}
			else
				ptr = p;
			p = ptr->next;								//pת����һ�����
		}
		break;
	case 3:
		pb = pBoom->next;							//ɾ����ը������
		ptrb = pBoom;
		while (pb != NULL) {							//���ѭ���ǻ�ɾ�������ӵ�

			if (pb->x == x && pb->y == y) {
				ptrb->next = pb->next;
				free(pb);
				pb = nullptr;
			}
			else
				ptrb = pb;
			pb = ptrb->next;								//pת����һ�����
		}
		break;

	}
}
void Delete(int flag) {
	Node* p;
	Node* ptr;
	Boom* pb, * ptrb;
	switch (flag)
	{
	case 0:
		p = pEnemy->next;							//�����л�����ָ��ָ��ڶ���(����һ�ܵл�
		ptr = pEnemy;
		while (p != NULL) {							//���ѭ���ǻ�ɾ������л�
			if (p->y >= HEIGHT || p->x<-100 || p->x>WIDTH + 100)
			{
				//	printf("ɾ���˵л�");
				ptr->next = p->next;
				free(p);							//��������Χ�Ľ��ɾ��
				p = nullptr;
			}
			else
				ptr = p;
			p = ptr->next;								//pת����һ�����
		}
		break;
	case 1:
		p = pBullet->next;								//�����һ��ӵ�����ָ��ָ��ڶ���
		ptr = pBullet;

		while (p != NULL) {								//���ѭ���ǻ�ɾ�������ӵ�

			if (p->y <= -p->height) {
				ptr->next = p->next;
				free(p);								//��������Χ���ӵ�ɾ��
				p = nullptr;
			}
			else
				ptr = p;
			p = ptr->next;								//pת����һ�����
		}
		break;


	case 2:
		p = pBullet_E->next;							//�����ӵ�����ָ��ָ��ڶ���
		ptr = pBullet_E;
		while (p != NULL) {								//���ѭ���ǻ�ɾ������Խ���ӵ�

			if (p->y > HEIGHT || p->y < -80 || p->x<-50 || p->x>WIDTH) {
				ptr->next = p->next;
				free(p);							//��������Χ���ӵ�ɾ��
				p = nullptr;
			}
			else
				ptr = p;
			p = ptr->next;								//pת����һ�����
		}
		break;
	case 3:
		p = pBullet->next;								//�����һ��ӵ�����ָ��ָ��ڶ���
		ptr = pBullet;
		while (p != NULL) {								//���ѭ���ǻ�ɾ�������ӵ�
			ptr->next = p->next;
			free(p);								//��������Χ���ӵ�ɾ��
			p = nullptr;
			p = ptr->next;								//pת����һ�����
		}

		p = pEnemy->next;							//�����л�����ָ��ָ��ڶ���(����һ�ܵл�
		ptr = pEnemy;
		while (p != NULL) {							//���ѭ���ǻ�ɾ������л�
			ptr->next = p->next;
			free(p);							//��������Χ�Ľ��ɾ��
			p = nullptr;
			p = ptr->next;								//pת����һ�����
		}

		p = pBullet_E->next;							//�����ӵ�����ָ��ָ��ڶ���
		ptr = pBullet_E;
		while (p != NULL) {								//���ѭ���ǻ�ɾ������Խ���ӵ�
			ptr->next = p->next;
			free(p);							//��������Χ���ӵ�ɾ��
			p = nullptr;
			p = ptr->next;								//pת����һ�����
		}

		pb = pBoom->next;							//ɾ����ը������
		ptrb = pBoom;
		while (pb != NULL) {							//���ѭ���ǻ�ɾ�������ӵ�
			ptrb->next = pb->next;
			free(pb);
			pb = nullptr;
			pb = ptrb->next;								//pת����һ�����
		}
		break;
	}
}

//���÷�ÿһλ�����ַ���������
int digitofscore(void) {
	int x = score;
	int i = 0;
	while (x > 0) {
		num[i] = x % 10;
		x /= 10;
		i++;
	}
	return i;
}
//��������
void CreateList(void) {
	pEnemy = (Node*)malloc(sizeof(Node));	//���л�ͷָ������ڴ�
	pEnemy->next = NULL;

	pBullet = (Node*)malloc(sizeof(Node));	//���ӵ������ڴ�
	pBullet->next = NULL;

	pBullet_E = (Node*)malloc(sizeof(Node));	//���ӵ������ڴ�
	pBullet_E->next = NULL;

	pMyself = (Node*)malloc(sizeof(Node));	//�һ�ͷָ������ڴ�
	pMyself->x = WIDTH / 2 - WIDTH_ME / 2;						//��ʼ����
	pMyself->y = HEIGHT - 200;
	pMyself->blood = 300;
	pMyself->next = NULL;
	pMyself->width = WIDTH_ME;
	pMyself->height = HEIGHT_ME;
	pMyself->invincible = 0;
	pMyself->weaponlevel = 1;
	pMyself->speed = 5;
	pMyself->slowspeed = 2;

	pBoom = (Boom*)malloc(sizeof(Boom));
	pBoom->next = NULL;

	prop = (Prop*)malloc(sizeof(Prop));
	prop->next = NULL;
}

//����ʱ����������Ŀ
void AddItem(void)
{
	int FDC = Frame.f_total - Frame.f_pause;
	switch (FDC)
	{
		//case //100:	AddEnemy(GUARD, STRAIGHT, 150, -10, 0);		break;

	case	160:	AddEnemy(GUARD, STOP, 200, -100, 0);		break;
		//case	170:	AddEnemy(QUICKER, STOP, WIDTH / 2 - WIDTH_GUARD / 2);		break;

	case	300:	AddEnemy(NORMAL, STRAIGHT, -50, 84, -PI / 3);		break;
	case    340:	AddEnemy(NORMAL, STRAIGHT, -50, 84, -PI / 3);		break;
	case	380:	AddEnemy(NORMAL, STRAIGHT, -50, 84, -PI / 3);		break;
	case	420:	AddEnemy(NORMAL, STRAIGHT, -50, 84, -PI / 3);		break;
	case    423:	Addprop(SHIELD);		break;
	case    450:	if (pMyself->weaponlevel < 3) Addprop(WEAPON_UPDATE);		break;
	case	460:	AddEnemy(NORMAL, STRAIGHT, -50, 84, -PI / 3);		break;
	case	500:	AddEnemy(NORMALB, STRAIGHT, WIDTH + 50 - WIDTH_NORMAL, 84, PI / 3);		break;
	case	540:	AddEnemy(NORMALB, STRAIGHT, WIDTH + 50 - WIDTH_NORMAL, 84, PI / 3);		break;
	case	580:	AddEnemy(NORMALB, STRAIGHT, WIDTH + 50 - WIDTH_NORMAL, 84, PI / 3);		break;
	case	620:	AddEnemy(NORMALB, STRAIGHT, WIDTH + 50 - WIDTH_NORMAL, 84, PI / 3);		break;
	case	660:	AddEnemy(NORMALB, STRAIGHT, WIDTH + 50 - WIDTH_NORMAL, 84, PI / 3);		break;
	case	690:	AddEnemy(RAIDER, STOP, 200, -100, 0);		break;
	case	700:	AddEnemy(NORMALB, STRAIGHT, -50, 84, -PI / 3);		break;
	case	740:	AddEnemy(NORMALB, STRAIGHT, -50, 84, -PI / 3);		break;
	case	780:	AddEnemy(NORMALB, STRAIGHT, -50, 84, -PI / 3);		break;
	case	820:	AddEnemy(NORMALB, STRAIGHT, -50, 84, -PI / 3);		break;
	case	860:	AddEnemy(NORMALB, STRAIGHT, -50, 84, -PI / 3);		break;
	case	900:	AddEnemy(NORMALB, STRAIGHT, WIDTH + 50 - WIDTH_NORMAL, 84, PI / 3);		break;
	case	940:	AddEnemy(NORMALB, STRAIGHT, WIDTH + 50 - WIDTH_NORMAL, 84, PI / 3);		break;
	case	980:	AddEnemy(NORMALB, STRAIGHT, WIDTH + 50 - WIDTH_NORMAL, 84, PI / 3);		break;
	case	1020:	AddEnemy(NORMALB, STRAIGHT, WIDTH + 50 - WIDTH_NORMAL, 84, PI / 3);		break;
	case	1060:	AddEnemy(NORMALB, STRAIGHT, WIDTH + 50 - WIDTH_NORMAL, 84, PI / 3);		break;
		//case    1070:	Addprop(WEAPON_UPDATE);		break;




	case 	1270:
		if (pMyself->blood <= 150)
		{
			Addprop(HEALTHPOT);
		}
		AddEnemy(NORMALB, LEFTARC, -50, -100, 0);		break;
	case 	1300:	AddEnemy(NORMALB, LEFTARC, -50, -100, 0);		break;
	case 	1330:	AddEnemy(NORMALB, LEFTARC, -50, -100, 0);		break;
	case 	1360:	AddEnemy(NORMALB, LEFTARC, -50, -100, 0);		break;
	case 	1390:	AddEnemy(NORMALB, LEFTARC, -50, -100, 0);		break;
	case 	1420:	AddEnemy(NORMALB, LEFTARC, -50, -100, 0);		break;
	case 	1450:	AddEnemy(NORMALB, LEFTARC, -50, -100, 0);		break;
	case 	1480:	AddEnemy(NORMALB, LEFTARC, -50, -100, 0);		break;
	case 	1510:	AddEnemy(NORMALB, LEFTARC, -50, -100, 0);		break;
	case 	1540:	AddEnemy(NORMALB, LEFTARC, -50, -100, 0);		break;
	case 	1570:	AddEnemy(NORMAL, RIGHTARC, -50, -100, 0);		break;
	case 	1600:	AddEnemy(NORMAL, RIGHTARC, -50, -100, 0);		break;
	case 	1630:	AddEnemy(NORMAL, RIGHTARC, -50, -100, 0);		break;
	case 	1660:	AddEnemy(NORMAL, RIGHTARC, -50, -100, 0);		break;
	case 	1690:	AddEnemy(NORMAL, RIGHTARC, -50, -100, 0);		break;
	case 	1720:	AddEnemy(NORMAL, RIGHTARC, -50, -100, 0);		break;
	case 	1750:	AddEnemy(NORMAL, RIGHTARC, -50, -100, 0);		break;
	case 	1780:	AddEnemy(NORMAL, RIGHTARC, -50, -100, 0);		break;
	case 	1810:	AddEnemy(NORMAL, RIGHTARC, -50, -100, 0);		break;
	case 	1840:	AddEnemy(NORMAL, RIGHTARC, -50, -100, 0);		break;
	case 	1870:	AddEnemy(NORMALB, LEFTARC, -50, -100, 0);		break;
	case 	1900:	AddEnemy(NORMALB, LEFTARC, -50, -100, 0);		break;
	case 	1930:	AddEnemy(NORMALB, LEFTARC, -50, -100, 0);		break;
	case 	1960:	AddEnemy(NORMALB, LEFTARC, -50, -100, 0);		break;
	case 	1990:	AddEnemy(NORMALB, LEFTARC, -50, -100, 0);		break;

	case   2000:
		if (pMyself->weaponlevel < 3)
			Addprop(WEAPON_UPDATE);
		for (int i = 0; i < GetLevels(); i++)
		{
			AddEnemy(RAIDER, STOP, 200, -100, 0);
		}
		break;
	case   2010:	Addprop(SHIELD);				break;
	case 	2020:	AddEnemy(NORMALB, LEFTARC, -50, -100, 0);		break;
	case 	2050:	AddEnemy(NORMALB, LEFTARC, -50, -100, 0);		break;
	case 	2080:	AddEnemy(NORMALB, LEFTARC, -50, -100, 0);		break;
	case 	2110:	AddEnemy(NORMALB, LEFTARC, -50, -100, 0);		break;
	case 	2140:	AddEnemy(NORMALB, LEFTARC, -50, -100, 0);		break;
	case 	2170:	AddEnemy(NORMAL, RIGHTARC, -50, -100, 0);		break;
	case 	2200:	AddEnemy(NORMAL, RIGHTARC, -50, -100, 0);		break;
	case 	2230:	AddEnemy(NORMAL, RIGHTARC, -50, -100, 0);		break;
	case 	2260:	AddEnemy(NORMAL, RIGHTARC, -50, -100, 0);		break;
	case 	2290:	AddEnemy(NORMAL, RIGHTARC, -50, -100, 0);		break;
	case 	2320:	AddEnemy(NORMAL, RIGHTARC, -50, -100, 0);		break;
	case 	2350:	AddEnemy(NORMAL, RIGHTARC, -50, -100, 0);		break;
	case 	2380:	AddEnemy(NORMAL, RIGHTARC, -50, -100, 0);		break;
	case 	2410:	AddEnemy(NORMAL, RIGHTARC, -50, -100, 0);		break;
	case 	2440:	AddEnemy(NORMAL, RIGHTARC, -50, -100, 0);		break;



	case 	3000:
		if (pMyself->blood <= 150)
		{
			Addprop(HEALTHPOT);
		}
		AddEnemy(NORMAL, STRAIGHT, WIDTH / 4 - WIDTH_NORMAL / 2, -100, 0);
		AddEnemy(NORMALB, STRAIGHT, (int)((3.0 / 4) * WIDTH - WIDTH_NORMAL / 2), -100, 0); break;
	case 	3050:	AddEnemy(NORMAL, STRAIGHT, WIDTH / 4 - WIDTH_NORMAL / 2, -100, 0);
		AddEnemy(NORMALB, STRAIGHT, (int)((3.0 / 4) * WIDTH - WIDTH_NORMAL / 2), -100, 0); break;
	case 	3100:	AddEnemy(NORMAL, STRAIGHT, WIDTH / 4 - WIDTH_NORMAL / 2, -100, 0);
		AddEnemy(NORMALB, STRAIGHT, (int)((3.0 / 4) * WIDTH - WIDTH_NORMAL / 2), -100, 0); break;
	case 	3150:	AddEnemy(NORMAL, STRAIGHT, WIDTH / 4 - WIDTH_NORMAL / 2, -100, 0);
		AddEnemy(NORMALB, STRAIGHT, (int)((3.0 / 4) * WIDTH - WIDTH_NORMAL / 2), -100, 0); break;
	case 	3200:	AddEnemy(NORMAL, STRAIGHT, WIDTH / 4 - WIDTH_NORMAL / 2, -100, 0);
		AddEnemy(NORMALB, STRAIGHT, (int)((3.0 / 4) * WIDTH - WIDTH_NORMAL / 2), -100, 0);
		AddEnemy(GUARD, STOP, WIDTH / 2 - WIDTH_GUARD / 2, -100, 0);		break;
	case 	3250:	AddEnemy(NORMAL, STRAIGHT, WIDTH / 4 - WIDTH_NORMAL / 2, -100, 0);
		AddEnemy(NORMALB, STRAIGHT, (int)((3.0 / 4) * WIDTH - WIDTH_NORMAL / 2), -100, 0); break;
	case 	3300:	AddEnemy(NORMAL, STRAIGHT, WIDTH / 4 - WIDTH_NORMAL / 2, -100, 0);
		AddEnemy(NORMALB, STRAIGHT, (int)((3.0 / 4) * WIDTH - WIDTH_NORMAL / 2), -100, 0); break;
	case 	3350:	AddEnemy(NORMAL, STRAIGHT, WIDTH / 4 - WIDTH_NORMAL / 2, -100, 0);
		AddEnemy(NORMALB, STRAIGHT, (int)((3.0 / 4) * WIDTH - WIDTH_NORMAL / 2), -100, 0); break;
	case 	3400:	AddEnemy(NORMAL, STRAIGHT, WIDTH / 4 - WIDTH_NORMAL / 2, -100, 0);
		AddEnemy(NORMALB, STRAIGHT, (int)((3.0 / 4) * WIDTH - WIDTH_NORMAL / 2), -100, 0); break;
	case 	3450:	AddEnemy(NORMAL, STRAIGHT, WIDTH / 4 - WIDTH_NORMAL / 2, -100, 0);
		AddEnemy(NORMALB, STRAIGHT, (int)((3.0 / 4) * WIDTH - WIDTH_NORMAL / 2), -100, 0); break;

	}
	if (FDC >= 3800 && !NumOfEnemies())
	{
		Frame.f_total = 300;
		Frame.f_resume = Frame.f_zawarudo = Frame.f_pause = 0;
		DifficultyRise();
	}

}
//������ͣ����
void Paint_Pause() {
	int FDC = Frame.f_total - Frame.f_resume;

	transparentimage(NULL, 0, 200, &ipause);
	if (!stage.Countdown)
		transparentimage(NULL, 0, 200, &pausetxt);
	else
	{
		if (FDC <= 100)
			transparentimage(NULL, 281, 232, 78, 72, 156, 0, 78, 72, &pausenum);
		else if (FDC <= 200)
			transparentimage(NULL, 281, 232, 78, 72, 78, 0, 78, 72, &pausenum);
		else if (FDC <= 300)
			transparentimage(NULL, 281, 232, 78, 72, 0, 0, 78, 72, &pausenum);
		if (FDC < 300 && FDC % 100 >= 0 && FDC % 100 < 20)
			transparentimage(NULL, 116, 125, 410, 310, &kuangkuang);
		else if (FDC % 100 >= 20 && FDC % 100 < 40)
			transparentimage(NULL, 151, 155, 340, 250, &kuangkuang);
		else if (FDC % 100 >= 40)
		{
			transparentimage(NULL, 230, 213, 183, 134, &kuangkuang);
			transparentimage(NULL, 322, 144, &blink);
		}
	}
	if (stage.Pause.i == 0)
		transparentimage(NULL, 9, 360, 180, 75, 0, 0, 180, 75, &button_back);
	else
		transparentimage(NULL, 9, 360, 180, 75, 0, 75, 180, 75, &button_back);
	if (stage.Pause.j == 0)
		transparentimage(NULL, WIDTH - 180 - 9, 360, 180, 75, 0, 0, 180, 75, &button_resume);
	else
		transparentimage(NULL, WIDTH - 180 - 9, 360, 180, 75, 0, 75, 180, 75, &button_resume);



}

//��ͼ�ƶ�
void Move_Map(void) {
	lct += 1;
	if (lct >= HEIGHT_MAP_1) lct = 0;
}
void Paint_Ready(void)
{
	int FDC = Frame.f_total - Frame.f_pause;
	if (!isStop())
		if (FDC <= 100)
		{
			transparentimage(NULL, WIDTH / 2 - 120, HEIGHT / 2 - 63 / 2, 227, 63, 0, 107, 227, 63, &readygo);
			transparentimage(NULL, WIDTH / 2 - 120, HEIGHT / 2 - 63 / 2, 227, 63, 0, 170, 227, 63, &readygo);
		}
		else if (FDC <= 300)
			transparentimage(NULL, WIDTH / 2 - 100, HEIGHT / 2 - 107 / 2, 227, 107, 0, 0, 227, 107, &readygo);
}
//���ƺ���
void Paint(void)
{

	BeginBatchDraw();
	cleardevice();
	putimage(0, (int)(lct - HEIGHT_MAP_1), &map1);
	putimage(0, (int)lct, &map1);

	Paint_Boom();
	Paint_Plane_Me();
	Paint_Bullet();
	Paint_Plane_Enemy();
	Paint_Bullet_Enemy();
	Paint_Ready();
	Paint_prop();
	//Ѫ��
	transparentimage(NULL, 0, HEIGHT - 44, WIDTH, 44, 0, 0, WIDTH, 44, &blood);
	transparentimage(NULL, 131, HEIGHT - 32, (int)(301 * (1.0 * pMyself->blood / 300)), 16, 4, 4, (int)(1.0 * 301 * (1.0 * pMyself->blood / 300)), 16, &blood_red);
	//���»��Ʒ���
	if (score == 0)
		transparentimage(NULL, WIDTH - 32, HEIGHT - 42, 32, 38, num[1 - 1] * 32, 0, 32, 38, &number);
	else
		for (int i = digitofscore(); i > 0; i--)
			transparentimage(NULL, WIDTH - 32 * i, HEIGHT - 42, 32, 38, num[i - 1] * 32, 0, 32, 38, &number);
	if (isStop()) Paint_Pause();
	EndBatchDraw();
}
bool isStop(void)
{
	if (stage.pause)
		return	true;
	else
		return false;
}
//��Ϸ����
void Gaming(void)
{

	CreateList();												//��������
	playsound(0, 1);											//bgm
	Frame.f_total = Frame.f_resume = Frame.f_zawarudo = Frame.f_pause = 0;
	DifiicultyReset();
	int c;
	clock_t t0 = clock();
	clock_t t1;
	while (stage.game)
	{
		t1 = clock();
		if (t1 - t0 >= 10)
		{
			t0 = t1;
			Frame.f_total++;
		}
		else
			continue;
		Paint();
		MouseListener();
		if (!isStop()) 									//��Ϸδ��ͣʱ��
		{
			Move_prop();

			c = GetCommand();								//��ȡ�����¼�
			Move_Enemy();									//���ֵл��ƶ�
			Move_Me(c); 									//�һ��ƶ�
			Move_Map();
			Move_Bullet_Me();								//�һ������ӵ��ƶ�  
			Move_Bullet_Enemy();							//�л������ӵ��ƶ�
			AddBullet_MeA();
			AddBullet_EnemyA();
			AddItem();

		}
		Shoot(1);												//���˴�������
		Shoot(0);												//�Ҵ����
		Get_prop();
		Delete(0);											//ɾ�������ӵ��л�
		Delete(1);
		Delete(2);
		if (pMyself->blood <= 0)
			if (saveScore())
			{
				stage.game = 0;
				stage.mainInterface = 1;
			}
		Sleep(1);
	}
	//�������Щ�ǹ��㣻
	Delete(3);
	DeletePropA();
	score = 0;
	num[0] = 0;
	stopsound(0);
}

