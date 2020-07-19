#include "Game.h"
#include "Resource.h"
#include "Interface.h"

int main()
{
	MessageBoxA(NULL, "此程序禁用了关闭按钮，请使用游戏内的退出\n"
		"制作者:cs", "重要提示!", MB_OK);
	initgraph(WIDTH, HEIGHT, NOCLOSE);
	loadresourse();												//加载资源
	stage.mainInterface = 1;
	while (TRUE)
	{
		Interface();											//界面
		Gaming();												//游戏部分
		if (stage.game == 0 && stage.mainInterface == 0)
			return 0;

	}
}
