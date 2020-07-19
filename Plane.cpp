
#include "Plane.h"
#include "Operate.h"
enum { m_LEFT, m_RIGHT, m_STILL };
int m_move;
int fLoL, fLoR, f_LtoM, f_RtoM;
int DRT;
DIRECTION direction;
int tanjian_R, tanjian_L, t_RtM, t_LtM;					//我忘记这是啥了
void Paint_Plane_Me(void)
{
	//solidrectangle(pMyself->x, pMyself->y, pMyself->x + 1, pMyself->y + 1);
	if (pMyself->blood == 0)
		return;

	int t2 = Frame.f_total - Frame.f_pause;
	if (direction.right - direction.left > 0)
	{
		if (t2 - tanjian_R >= 0 && t2 - tanjian_R < 10)
			transparentimage(NULL, pMyself->x, pMyself->y, WIDTH_ME, HEIGHT_ME, 116, 0, WIDTH_ME, HEIGHT_ME, &p_01a);
		if (t2 - tanjian_R >= 10 && t2 - tanjian_R < 20)
			transparentimage(NULL, pMyself->x, pMyself->y, 92, HEIGHT_ME, 220, 0, 92, HEIGHT_ME, &p_01a);
		if (t2 - tanjian_R >= 20)
			transparentimage(NULL, pMyself->x, pMyself->y, 83, HEIGHT_ME, 312, 0, 83, HEIGHT_ME, &p_01a);
	}
	else if (direction.right - direction.left < 0)
	{
		if (t2 - tanjian_L >= 0 && t2 - tanjian_L < 10)
			transparentimage(NULL, pMyself->x, pMyself->y, WIDTH_ME, HEIGHT_ME, 602 - 116 - WIDTH_ME, 0, WIDTH_ME, HEIGHT_ME, &p_01b);
		if (t2 - tanjian_L >= 10 && t2 - tanjian_L < 20)
			transparentimage(NULL, pMyself->x, pMyself->y, 92, HEIGHT_ME, 602 - 220 - 92, 0, 92, HEIGHT_ME, &p_01b);
		if (t2 - tanjian_L >= 20)
			transparentimage(NULL, pMyself->x, pMyself->y, 83, HEIGHT_ME, 602 - 312 - 83, 0, 83, HEIGHT_ME, &p_01b);
	}
	else
	{
		if (DRT == -1)
		{
			if (t2 - t_LtM >= 0 && t2 - t_LtM < 10)
				transparentimage(NULL, pMyself->x, pMyself->y, 92, HEIGHT_ME, 602 - 220 - 92, 0, 92, HEIGHT_ME, &p_01b);
			else if (t2 - t_LtM >= 10 && t2 - t_LtM < 20)
				transparentimage(NULL, pMyself->x, pMyself->y, WIDTH_ME, HEIGHT_ME, 602 - 116 - WIDTH_ME, 0, WIDTH_ME, HEIGHT_ME, &p_01b);
			else
				transparentimage(NULL, pMyself->x, pMyself->y, WIDTH_ME, HEIGHT_ME, 7, 0, WIDTH_ME, HEIGHT_ME, &p_01a);

		}
		else if (DRT == 1)
		{
			if (t2 - t_RtM >= 0 && t2 - t_RtM < 10)
				transparentimage(NULL, pMyself->x, pMyself->y, 92, HEIGHT_ME, 220, 0, 92, HEIGHT_ME, &p_01a);
			else if (t2 - t_RtM >= 10 && t2 - t_RtM < 20)
				transparentimage(NULL, pMyself->x, pMyself->y, WIDTH_ME, HEIGHT_ME, 116, 0, WIDTH_ME, HEIGHT_ME, &p_01a);
			else
				transparentimage(NULL, pMyself->x, pMyself->y, WIDTH_ME, HEIGHT_ME, 7, 0, WIDTH_ME, HEIGHT_ME, &p_01a);
		}
		else
			transparentimage(NULL, pMyself->x, pMyself->y, WIDTH_ME, HEIGHT_ME, 7, 0, WIDTH_ME, HEIGHT_ME, &p_01a);

	}

	//尾焰
	transparentimage(NULL, pMyself->x + 25, pMyself->y + HEIGHT_ME - 33, 30, HEIGHT_ME, 500, 0, 30, HEIGHT_ME, &p_01a);
	transparentimage(NULL, pMyself->x + 49, pMyself->y + HEIGHT_ME - 33, 30, HEIGHT_ME, 500, 0, 30, HEIGHT_ME, &p_01a);
	if (pMyself->invincible)
	{
		RotateImage(&yyy, &shield1, 0.02*((double)t2 - pMyself->invincible));
		int w =(&yyy)->getwidth()/2;
		transparentimage(NULL, pMyself->x +pMyself->width/2-w, pMyself->y +pMyself->height/2-w,&yyy);
	}
	setfillcolor(WHITE);
//	solidrectangle(pMyself->x + WIDTH_ME / 2, pMyself->y, pMyself->x + WIDTH_ME / 2 + 1, pMyself->y + 1);
	//solidrectangle(pMyself->x + WIDTH_ME / 2, pMyself->y + 36, pMyself->x + WIDTH_ME / 2 + 100, pMyself->y + 36 +1);
}
void Move_Me(int _cmd)
{
	//这个我实在不会处理了i j k l都是开关,用来实现不要让飞机飞出地图,它写的实在很烂！，但我不想改了
	static int i = 1, j = 1, k = 0, l = 0;

	int speed = pMyself->speed;
	if (_cmd & CMD_SHIFT)
	{
		speed = pMyself->slowspeed;
	}

	if (_cmd & CMD_UP && pMyself->y > 0)
	{
		pMyself->y -= speed;
		direction.up = 1;
		//printf("up\n");
	}
	else {
		direction.up = 0;
	}
	if (_cmd & CMD_DOWN && pMyself->y < HEIGHT - HEIGHT_ME)
	{
		pMyself->y += speed;
		direction.down = 1;
		//printf("down\n");
	}
	else
	{
		direction.down = 0;
	}
	if (_cmd & CMD_LEFT && pMyself->x > 0)
	{
		pMyself->x -= speed;
		direction.left = 1;
		//printf("left\n");
		if (j == 1)
		{
			DRT = -1;
			tanjian_L = Frame.f_total - Frame.f_pause;
			j = 0;
			//k=1就是可以左移状态->中
		}
		k = 1;
	}
	else
	{
		direction.left = 0;
		if (k == 1)
		{
			t_LtM = Frame.f_total - Frame.f_pause;
			k = 0;
		}
		j = 1;
	}
	if (_cmd & CMD_RIGHT && pMyself->x < WIDTH - WIDTH_ME)
	{
		pMyself->x += speed;
		direction.right = 1;
		//printf("i=%d\n", i);
		if (i == 1)
		{
			DRT = 1;
			tanjian_R = Frame.f_total - Frame.f_pause;
			i = 0;
		}
		l = 1;
		//printf("right\n");
	}
	else
	{
		//printf("弹起\n");
		direction.right = 0;
		if (l == 1)
		{
			t_RtM = Frame.f_total - Frame.f_pause;
			l = 0;
		}
		i = 1;
	}
}