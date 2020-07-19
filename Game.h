#pragma once
#include <time.h>
#include <graphics.h>
#define PI 3.14159265

#define WIDTH 640
#define HEIGHT 800

#define DEFAULT -1
#define WIDTH_ME 104
#define HEIGHT_ME 120
#define WIDTH_NORMAL 112
#define HEIGHT_NORMAL 79
#define WIDTH_GUARD 159
#define HEIGHT_GUARD 212
#define WIDTH_BOSS 372
#define HEIGHT_BOSS 315
#define WIDTH_QUICKER 190
#define HEIGHT_QUICKER 142
#define WIDTH_RAIDER 126
#define HEIGHT_RAIDER 108
#define WIDTH_BULLET_ME 40
#define WIDTH_BULLET_SSHOCKWAVE 62
#define HEIGHT_BULLET_SSHOCKWAVE 92
#define WIDTH_BULLET_LONG 40
#define HEIGHT_BULLET_LONG 89
#define WIDTH_BULLET_REDBALL 61
#define HEIGHT_BULLET_REDBALL 61
#define WIDTH_BULLET_RHOMBUS 20
#define HEIGHT_BULLET_RHOMBUS 20
#define WIDTH_BULLET_BOSSSHOCKWAVE 270
#define HEIGHT_BULLET_BOSSSHOCKWAVE 160
#define WIDTH_BOOM_1 150
#define HEIGHT_BOOM_1 150
#define WIDTH_MAP_1 680
#define HEIGHT_MAP_1 1024
#define HEIGHT_NUM 32
#define WIDTH_NUM 28
#define WIDTH_BULLET_ME_1 44
#define WIDTH_BULLET_ME_2 44
#define WIDTH_BULLET_ME_3 60
#define HEIGHT_BULLET_ME 184
#define SIZE_PROP 58
#define NORMAL 0
#define UPDATE 1
#define ULTRA 2
#define BOSS 1
#define QUICKER 2
#define RAIDER 3
#define GUARD 4
#define ME 5
#define NORMALB 6
#define ATTACK 0
#define INJURE 1
#define LONG 0
#define SSHOCKWAVE 1
#define REDBALL 2
#define RHOMBUS 3
#define BOSSSHOCKWAVE 4
#define LEFTARC 0
#define RIGHTARC 1
#define STRAIGHT 2
#define STOP 3									//��ֱ�ߣ���ͣ��

typedef struct NODE {							//���С��Ϸ����������
	int x;										//��ǰx����
	int y;										//��ǰy����
	int type;									//����
	int blood;									//��ǰѪ��
	int fullblood;								//manxue
	int Num_bullet;								//�ӵ���(��ʱ����
	int x0;										//�����ӵ����ʱ���λ��
	int y0;
	//int tx;										//���������ӵ����ʱ�һ�λ��(�л���׼�һ������ӵ���
	//int ty;
	double theta;
	int direction;								//�ƶ�����
	int f_create;								//��ʼֵΪ����ʱ�̵�֡��(�л���
	int fire_on;									//ÿ����֡���𿪹ؿ�
	int fire_off;
	int ff_fire;								//�м�ֵ
	int FireSwitch;								//���𿪹�0����1��,ʵ�����ǹ�㶹������Ъ����(�л���
	int width;									//��
	int height;									//��
	int hitpoints;								//�˺�
	int movemod;								//�ƶ�ģʽ����Leftarc��Rightarc,straight����
	double speed;								//�ƶ��ٶȣ���λ:����/ms
	double slowspeed;
	struct NODE* next;
	int invincible;
	int weaponlevel;
} Node;
typedef struct PROP {
	int type;
	int x;
	int y;
	int  f_create;
	struct PROP* next;
}Prop;
typedef struct {
	int up;
	int down;
	int left;
	int right;
} DIRECTION;
typedef struct Boom {							//�������汬ը
	int x;
	int y;
	int type;
	int size;
	int f_create;									//��¼��ը��һ�̵�֡��
	struct Boom* next;
} Boom;

struct Pause {												//��ͣ���水ť����
	int i;
	int j;
	int k;
	int l;
};
struct Stage {
	int pause;
	int game;
	int mainInterface;
	int Countdown;
	int rankinglist;
	Pause Pause;
};
struct CoverButton {
	int button_blue;											//1����
	int button_green;
	int button_rankinglist;
	int button_back2;
};
struct TIME {
	clock_t Time;												//�ӿ�ʼ��һ�̿�ʼ��ʱ
	clock_t Tpause;												//��ʱͣʱ��
	clock_t Zawarudo;											//ʱͣ��һ�̵�ʱ��
	clock_t Resume;												//�ظ���ť������һ�̵�ʱ��
};
struct FRAME {
	int f_total;												//��֡��	ֻҪ������Ϸ��10ms��һ�������治���룩
	int f_zawarudo;												//������ͣʱ����֡��
	int f_resume;												//����ظ�ʱ�����֡��
	int f_pause;												//��ͣ�˶���֡
};
extern FRAME Frame;
extern TIME Tier;
extern int score;												//�÷�
typedef int SOUND;

extern Prop* prop;
extern Boom* pBoom;
extern Node* pBullet;												//�ӵ�
extern Node* pBullet_E;											//�л��ӵ�
extern Node* pEnemy;												//�л�
extern Node* pMyself;												//�һ�


extern int num[10];												//�÷�ÿһλ��,��ȫ���Է�������
extern int boss;												//�Ƿ����boss
extern IMAGE button_back2, button_rankinglist, blink, kuangkuang, shield1, huifu, shield, readygo, blood_enemy, enemy_normalb, pausetxt, pausenum, weapon_update, button_quit, button_enter, logo, logo01, cover2, p_01a, zhujizidan, yyy1, yyy2, p_01b, map1, blood, ipause, button_resume, button_back, bullet1, enemy_quicker, enemy_raider, enemy_boss, enemy_normal, enemy_guard, number, boom04, blood_red, yyy, bullet2, bullet3, bullet4, bullet5, rankinglist;
extern struct Stage stage;
extern struct CoverButton CoverButton;
extern double lct;													//��ͼ����
//��תͼƬ

void RotateImage(IMAGE* pTo, IMAGE* pFrom, double rad);
//��һ��͸��ͼ
void transparentimage(IMAGE* dstimg, int x, int y, IMAGE* srcimg);
//png͸��ͼ����
void transparentimage(IMAGE* dstimg, int xt, int yt, int wt, int ht,
	int xo, int yo, int wo, int ho, IMAGE* srcimg);
void transparentimage(IMAGE* dstimg, int x, int y, int w, int h, IMAGE* srcimg);
//�������
double distance(double x1, double y1, double x2, double y2);
//ɾ�� 0�л� 1���ӵ� 2�л��ӵ�(����Ҫ����),3 ���еĶ���
void Delete(int flag);

void CreateList(void);
void AddItem(void);
//ɾ�� 0�л� 1���ӵ� 2�л��ӵ� 3��ը(��Ҫ����)
void Delete(int flag, int x, int y);
//�Ƿ���ͣ
bool isStop(void);

void Gaming(void);
