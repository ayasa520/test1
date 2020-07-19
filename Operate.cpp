#include "Operate.h"
//获取键盘事件
int GetCommand(void)												//得到按键
{
	int c = 0;
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)		c |= CMD_LEFT;
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)	c |= CMD_RIGHT;
	if (GetAsyncKeyState(VK_UP) & 0x8000)		c |= CMD_UP;
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)		c |= CMD_DOWN;
	if (GetAsyncKeyState('A') & 0x8000)		c |= CMD_LEFT;
	if (GetAsyncKeyState('D') & 0x8000)	c |= CMD_RIGHT;
	if (GetAsyncKeyState('W') & 0x8000)		c |= CMD_UP;
	if (GetAsyncKeyState('S') & 0x8000)		c |= CMD_DOWN;
	if (GetAsyncKeyState(VK_LSHIFT) & 0x8000) c |= CMD_SHIFT;
	return c;
}
//鼠标消息
void MouseListener(void) {
	HWND hwnd = GetHWnd();										//获取绘图窗口句柄
	HWND hwnd_now = GetForegroundWindow();						//获取当前焦点窗口句柄
	MOUSEMSG m;
	HCURSOR hcur;
	if (stage.Countdown && Frame.f_total - Frame.f_resume >= 300) {

		stage.pause = 0;
		stage.Countdown = 0;
		Frame.f_pause += (Frame.f_total - Frame.f_zawarudo);

	}
	/*if (hwnd != hwnd_now && !stage.pause && stage.game)
	{
		stage.pause = 1;
		stage.Pause.l = 1;
		stage.Countdown = 0;
		Frame.f_zawarudo = Frame.f_total;
	}*/
	if (MouseHit() && stage.pause && stage.game) {
		m = GetMouseMsg();							//获取鼠标事件

		if (m.mkLButton && BACK_SCOPE) stage.Pause.i = 1;
		if (m.mkLButton && RESUME_SCOPE) stage.Pause.j = 1;
		if (m.uMsg == WM_LBUTTONUP) {
			if (stage.Pause.j && RESUME_SCOPE)
			{
				if (stage.Pause.l)
				{
					stage.Countdown = 1;
					Frame.f_resume = Frame.f_total;
					stage.Pause.l = 0;
				}
				stage.Pause.k = 0;
				stage.Pause.j = 0;
			}
			if (stage.Pause.i && BACK_SCOPE)
			{
				stage.Countdown = 0;
				stage.pause = stage.game = 0;
				stage.mainInterface = 1;
				stage.Pause.i = 0;

			}
		}
		else if (!BACK_SCOPE && !RESUME_SCOPE)
		{
			stage.Pause.i = stage.Pause.j = 0;
		}
	}
	if (MouseHit() && stage.game) {
		//printf("ok");
		m = GetMouseMsg();
		switch (m.uMsg) {
		case WM_MOUSEMOVE:
			//printf("x=%d y=%d\n", m.x, m.y);
			if (PAUSE_SCOPE && !stage.pause) {
				hcur = LoadCursor(NULL, IDC_HAND);
				SetClassLong(hwnd, GCL_HCURSOR, (long)hcur);
			}
			else if ((BACK_SCOPE || RESUME_SCOPE) && stage.pause)
			{
				hcur = LoadCursor(NULL, IDC_HAND);
				SetClassLong(hwnd, GCL_HCURSOR, (long)hcur);
			}
			else
			{
				hcur = LoadCursor(NULL, IDC_ARROW);
				SetClassLong(hwnd, GCL_HCURSOR, (long)hcur);
			}

			break;
		case WM_LBUTTONDOWN:
			if (PAUSE_SCOPE)
			{
				stage.pause = 1;
				stage.Pause.l = 1;
				Frame.f_zawarudo = Frame.f_total;
			}

		}
	}
	if (MouseHit() && stage.mainInterface) {
		m = GetMouseMsg();


		switch (m.uMsg)
		{
		case WM_LBUTTONDOWN:
			if (!stage.rankinglist) {
				if (QUIT_SCOPE)
					CoverButton.button_blue = 1;
				else
					CoverButton.button_blue = 0;
				if (START_SCOPE)
					CoverButton.button_green = 1;
				else
					CoverButton.button_green = 0;
				if (RANKINGLIST_SCOPE)
					CoverButton.button_rankinglist = 1;
				else
					CoverButton.button_rankinglist = 0;
			}
			else {
				if (BACK2_SCOPE)
					CoverButton.button_back2 = 1;
				else
					CoverButton.button_back2 = 0;
			}
			break;
		case WM_LBUTTONUP:
			if (!stage.rankinglist)
			{
				if (QUIT_SCOPE)
				{
					CoverButton.button_blue = 0;
					stage.mainInterface = 0;
					stage.game = 0;
				}
				else if (START_SCOPE)
				{
					CoverButton.button_green = 0;
					stage.mainInterface = 0;
					stage.game = 1;

				}
				else if (RANKINGLIST_SCOPE)
				{
					hcur = LoadCursor(NULL, IDC_ARROW);
					CoverButton.button_rankinglist = 0;
					stage.rankinglist = 1;
					SetClassLong(hwnd, GCL_HCURSOR, (long)hcur);
				}
			}
			else
			{
				if (BACK2_SCOPE)
				{
					stage.rankinglist = 0;
					CoverButton.button_back2 = 0;
				}
			}
			break;
		case WM_MOUSEMOVE:
			if (!stage.rankinglist)
			{
				if (stage.mainInterface && (START_SCOPE || QUIT_SCOPE || RANKINGLIST_SCOPE))
				{
					hcur = LoadCursor(NULL, IDC_HAND);
					SetClassLong(hwnd, GCL_HCURSOR, (long)hcur);
					if (m.mkLButton)
					{
						if (START_SCOPE)
							CoverButton.button_green = 1;
						else if (QUIT_SCOPE)
							CoverButton.button_blue = 1;
						else
							CoverButton.button_rankinglist = 1;
					}
				}
				else
				{
					hcur = LoadCursor(NULL, IDC_ARROW);
					SetClassLong(hwnd, GCL_HCURSOR, (long)hcur);
					CoverButton.button_green = 0;
					CoverButton.button_blue = 0;
					CoverButton.button_rankinglist = 0;
				}
			}
			else
			{
				if (BACK2_SCOPE)
				{
					hcur = LoadCursor(NULL, IDC_HAND);
					SetClassLong(hwnd, GCL_HCURSOR, (long)hcur);
					if (m.mkLButton)
						CoverButton.button_back2 = 1;
				}
				else
				{
					hcur = LoadCursor(NULL, IDC_ARROW);
					SetClassLong(hwnd, GCL_HCURSOR, (long)hcur);
					CoverButton.button_back2 = 0;
				}
			}
			break;
		}


	}
}