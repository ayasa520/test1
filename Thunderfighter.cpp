#include "Game.h"
#include "Resource.h"
#include "Interface.h"

int main()
{
	MessageBoxA(NULL, "�˳�������˹رհ�ť����ʹ����Ϸ�ڵ��˳�\n"
		"������:cs", "��Ҫ��ʾ!", MB_OK);
	initgraph(WIDTH, HEIGHT, NOCLOSE);
	loadresourse();												//������Դ
	stage.mainInterface = 1;
	while (TRUE)
	{
		Interface();											//����
		Gaming();												//��Ϸ����
		if (stage.game == 0 && stage.mainInterface == 0)
			return 0;

	}
}
