
#include "Boom.h"

//��ը����
void AddNodeboom(int x, int y, int type,int size) {
	Boom* pNew = (Boom*)malloc(sizeof(Boom));
	pNew->next = pBoom->next;
	pNew->size = size;
	pNew->x = x;
	pNew->y = y;
	pNew->type = type;
	pNew->f_create = Frame.f_total-Frame.f_pause;
	pBoom->next = pNew;

}
//���Ʊ�ը
void Paint_Boom(void)
{

	Boom* p = pBoom->next;
	while (p != NULL)
	{
		int frameDifference = Frame.f_total - Frame.f_pause - p->f_create;
		switch (p->type)
		{
			//��ͨ�л�
		case NORMAL:case NORMALB:case GUARD:

			transparentimage(NULL, p->x, p->y, p->size+ 20,p->size+ 20, frameDifference / 6 * 300, 0, 300, 300, &boom04);

			if (frameDifference>= 70)
			{
				Delete(3, p->x, p->y);
				//ɾ����,Ӧ������ָ��ڶ��������򱨴�,����break���Ѿ���->next,����ָ��pBoom
				p = pBoom;
			}
			break;
		}

		p = p->next;
	}
}