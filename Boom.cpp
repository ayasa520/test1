
#include "Boom.h"

//爆炸链表
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
//绘制爆炸
void Paint_Boom(void)
{

	Boom* p = pBoom->next;
	while (p != NULL)
	{
		int frameDifference = Frame.f_total - Frame.f_pause - p->f_create;
		switch (p->type)
		{
			//普通敌机
		case NORMAL:case NORMALB:case GUARD:

			transparentimage(NULL, p->x, p->y, p->size+ 20,p->size+ 20, frameDifference / 6 * 300, 0, 300, 300, &boom04);

			if (frameDifference>= 70)
			{
				Delete(3, p->x, p->y);
				//删除后,应该让他指向第二个结点否则报错,由于break后已经有->next,这里指向pBoom
				p = pBoom;
			}
			break;
		}

		p = p->next;
	}
}