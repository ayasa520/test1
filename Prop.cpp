#include "Prop.h"

void Addprop(int flag) {
	Prop* p;
	switch (flag) {
	case WEAPON_UPDATE:
		p = (Prop*)malloc(sizeof(Prop));
		p->type = WEAPON_UPDATE;
		p->x = rand() % (WIDTH - SIZE_PROP);
		p->f_create = Frame.f_total - Frame.f_pause;
		p->y = -SIZE_PROP;
		p->next = prop->next;
		prop->next = p;
		break;
	case SHIELD:
		p = (Prop*)malloc(sizeof(Prop));
		p->type = SHIELD;
		p->x = rand() % (WIDTH - SIZE_PROP);
		p->f_create = Frame.f_total - Frame.f_pause;
		p->y = -SIZE_PROP;
		p->next = prop->next;
		prop->next = p;
		break;

	case HEALTHPOT:
		p = (Prop*)malloc(sizeof(Prop));
		p->type = HEALTHPOT;
		p->x = rand() % (WIDTH - SIZE_PROP);
		p->f_create = Frame.f_total - Frame.f_pause;
		p->y = -SIZE_PROP;
		p->next = prop->next;
		prop->next = p;
		break;
		/*case BOMB:
			prop1->type = BOMB;
			prop1->x = rand() % (WIDTH - 198);
			prop1->y = -HEIGHT_BOMB;
		case BOMBS:
			prop1->type = BOMBS;
			prop1->x = rand() % (WIDTH - 198);
			prop1->y = -HEIGHT_BOMBS;*/
	}

}
void Move_prop(void) {
	Prop* p = prop->next;
	while (p != NULL) {
		int frameDifference = Frame.f_total - Frame.f_pause - p->f_create;
		switch (p->type) {
			/*case SHIELD:case HEALTHPOT:case BOMB:case BOMBS:*/
		case WEAPON_UPDATE:case SHIELD:case HEALTHPOT:

			p->y = frameDifference * 0.4;
			break;
		}
		p = p->next;
	}
}
void Paint_prop(void)
{
	int FDC = Frame.f_total - Frame.f_pause;
	Prop* p = prop->next;
	while (p != NULL)
	{
		switch (p->type)
		{
		case WEAPON_UPDATE:
		{
			int dif = FDC - p->f_create;
			static int i = 0;
			if (dif % 10 == 0)
			{
				i += 1;
				if (i == 13)
					i = 0;
			}
			transparentimage(NULL, p->x, p->y, 109, 64, 109 * i, 0, 109, 64, &weapon_update);

			//printf("\n道具的%d %d", p->x, p->y);
			break;
		}
		case SHIELD:
		{
			int dif = FDC - p->f_create;
			static int i = 0;
			if (dif % 10 == 0)
			{
				i += 1;
				if (i == 19)
					i = 0;
			}
			transparentimage(NULL, p->x, p->y, 56, 60, 84 * (i % 10), 60 * (i / 10), 56, 60, &shield);

			//printf("\n道具的%d %d", p->x, p->y);
			break;
		}
		case HEALTHPOT:
			transparentimage(NULL, p->x, p->y,SIZE_PROP,SIZE_PROP,30,45,SIZE_PROP,SIZE_PROP ,&huifu);
			break;
		}
		p = p->next;
	}
}
void DeletePropB(int x, int y)
{
	Prop* p = prop->next;
	Prop* ptr = prop;


	while (p != NULL)
	{
		if (p->x == x && p->y == y)
		{
			ptr->next = p->next;
			free(p);
			p = nullptr;
		}
		else
			ptr = p;
		p = ptr->next;
	}
}
void DeletePropA(void)
{
	Prop* p = prop->next;
	Prop* ptr = prop;
	while (p != NULL)
	{
		ptr->next = p->next;
		free(p);
		p = nullptr;
		p = ptr->next;
	}

}
void Get_prop(void) {
	Prop* p = prop->next;
	while (p != NULL) {
		if (p->x >= pMyself->x - SIZE_PROP / 2 &&
			p->x <= pMyself->x + SIZE_PROP / 2 &&
			p->y >= pMyself->y - SIZE_PROP/2  && p->y <= pMyself->y + HEIGHT_ME+SIZE_PROP/2)
		{
			switch (p->type) {
			case WEAPON_UPDATE:
				pMyself->weaponlevel += 1;
				break;
			case SHIELD:
				pMyself->invincible = Frame.f_total - Frame.f_pause;
				break;
			case HEALTHPOT:
				pMyself->blood += 50;
				if (pMyself->blood > 300) {
					pMyself->blood = 300;
				}
				break;
				/*
					case BOMB:
						Damage(20);
					case BOMBS:
						Damage(100);*/
			}
			DeletePropB(p->x, p->y);
			p = prop->next;
		}
		else
			p = p->next;
	}
}