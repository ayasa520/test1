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
#define STOP 3									//先直走，再停下

typedef struct NODE {							//这个小游戏核心是坐标
	int x;										//当前x坐标
	int y;										//当前y坐标
	int type;									//种类
	int blood;									//当前血量
	int fullblood;								//manxue
	int Num_bullet;								//子弹数(暂时无用
	int x0;										//保存子弹射出时候的位置
	int y0;
	//int tx;										//用来保存子弹射出时我机位置(敌机瞄准我机类型子弹用
	//int ty;
	double theta;
	int direction;								//移动方向
	int f_create;								//初始值为创建时刻的帧数(敌机用
	int fire_on;									//每隔几帧开火开关开
	int fire_off;
	int ff_fire;								//中间值
	int FireSwitch;								//开火开关0不开1开,实现像机枪豌豆那样间歇性射(敌机用
	int width;									//宽
	int height;									//高
	int hitpoints;								//伤害
	int movemod;								//移动模式：有Leftarc，Rightarc,straight三种
	double speed;								//移动速度，单位:像素/ms
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
typedef struct Boom {							//用来保存爆炸
	int x;
	int y;
	int type;
	int size;
	int f_create;									//记录爆炸那一刻的帧数
	struct Boom* next;
} Boom;

struct Pause {												//暂停界面按钮开关
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
	int button_blue;											//1按下
	int button_green;
	int button_rankinglist;
	int button_back2;
};
struct TIME {
	clock_t Time;												//从开始那一刻开始计时
	clock_t Tpause;												//总时停时间
	clock_t Zawarudo;											//时停那一刻的时间
	clock_t Resume;												//回复按钮弹起那一刻的时间
};
struct FRAME {
	int f_total;												//总帧数	只要进入游戏，10ms加一（主界面不计入）
	int f_zawarudo;												//保存暂停时的总帧数
	int f_resume;												//保存回复时候的总帧数
	int f_pause;												//暂停了多少帧
};
extern FRAME Frame;
extern TIME Tier;
extern int score;												//得分
typedef int SOUND;

extern Prop* prop;
extern Boom* pBoom;
extern Node* pBullet;												//子弹
extern Node* pBullet_E;											//敌机子弹
extern Node* pEnemy;												//敌机
extern Node* pMyself;												//我机


extern int num[10];												//得分每一位数,用全局以方便清零
extern int boss;												//是否存在boss
extern IMAGE button_back2, button_rankinglist, blink, kuangkuang, shield1, huifu, shield, readygo, blood_enemy, enemy_normalb, pausetxt, pausenum, weapon_update, button_quit, button_enter, logo, logo01, cover2, p_01a, zhujizidan, yyy1, yyy2, p_01b, map1, blood, ipause, button_resume, button_back, bullet1, enemy_quicker, enemy_raider, enemy_boss, enemy_normal, enemy_guard, number, boom04, blood_red, yyy, bullet2, bullet3, bullet4, bullet5, rankinglist;
extern struct Stage stage;
extern struct CoverButton CoverButton;
extern double lct;													//地图坐标
//旋转图片

void RotateImage(IMAGE* pTo, IMAGE* pFrom, double rad);
//另一个透明图
void transparentimage(IMAGE* dstimg, int x, int y, IMAGE* srcimg);
//png透明图绘制
void transparentimage(IMAGE* dstimg, int xt, int yt, int wt, int ht,
	int xo, int yo, int wo, int ho, IMAGE* srcimg);
void transparentimage(IMAGE* dstimg, int x, int y, int w, int h, IMAGE* srcimg);
//计算距离
double distance(double x1, double y1, double x2, double y2);
//删除 0敌机 1我子弹 2敌机子弹(不需要坐标),3 所有的东西
void Delete(int flag);

void CreateList(void);
void AddItem(void);
//删除 0敌机 1我子弹 2敌机子弹 3爆炸(需要坐标)
void Delete(int flag, int x, int y);
//是否暂停
bool isStop(void);

void Gaming(void);
