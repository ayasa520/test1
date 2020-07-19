#include "Interface.h"
#include <math.h>
#include "Score.h"
//界面
void Interface(void)
{
	while (stage.mainInterface)
	{

		PaintInterface();
		MouseListener();
		Sleep(10);
	}
}
void PaintRankinglist(void)
{
	static int y = -784;
	if (stage.rankinglist)
	{
		transparentimage(NULL, 0, y, &rankinglist);
		if (y < -10) {
			y =(int)(y+ sqrt((double)2 * 3 * ((double)785 + y)));

		}
		else
		{
			if (!CoverButton.button_back2) transparentimage(NULL, 193, 693, 255, 48, 0, 0, 255, 48, &button_back2);
			else transparentimage(NULL, 193, 693, 255, 48, 0, 89, 255, 48, &button_back2);
			ReadLog();
		}
	}
	else
	{
		transparentimage(NULL, 0, y, &rankinglist);
		if (y > -784)
			y =(int)(y-sqrt((double)2 * 3 * ((double)785 + y)));
		else
			y = -784;

	}
}

	void PaintButton(void)
{
	if (stage.rankinglist == 0) {
		if (!CoverButton.button_blue)
			transparentimage(NULL, 215, 650, 209, 64, 0, 0, 209, 64, &button_quit);
		else
			transparentimage(NULL, 215, 650, 209, 64, 0, 64, 209, 64, &button_quit);
		if (!CoverButton.button_rankinglist)
			transparentimage(NULL, 215, 575, 209, 64, 0, 0, 209, 64, &button_rankinglist);
		else
			transparentimage(NULL, 215, 575, 209, 64, 0, 64, 209, 64, &button_rankinglist);
		if (!CoverButton.button_green)
			transparentimage(NULL, 215, 500, 209, 64, 0, 0, 209, 64, &button_enter);
		else
			transparentimage(NULL, 215, 500, 209, 64, 0, 64, 209, 64, &button_enter);
	}
}
//绘制主界面
void PaintInterface(void) {
	BeginBatchDraw();
	cleardevice();
	putimage(0, 0, &cover2);
	//transparentimage(NULL, 30, 100, &logo01);
	transparentimage(NULL, 30, 100, &logo);
	PaintButton();

	PaintRankinglist();

	EndBatchDraw();
}