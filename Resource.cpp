#include "Game.h"
#include "Music.h"
IMAGE button_back2,button_rankinglist,blink, kuangkuang, shield1, shield, huifu, readygo, blood_enemy, enemy_normalb, pausetxt, pausenum, weapon_update, button_quit, button_enter, logo, logo01, cover2, p_01a, zhujizidan, yyy1, yyy2, p_01b, map1, blood, ipause, button_resume, button_back, bullet1, enemy_quicker, enemy_raider, enemy_boss, enemy_normal, enemy_guard, number, boom04, blood_red, yyy, bullet2, bullet3, bullet4, bullet5,rankinglist;
SOUND sidiaole, qijizaixian, blast0, planeshoot0;
//加载资源
void loadresourse(void)
{
	
	loadimage(&map1, _T("image\\map\\bg_hei_0.jpg"));
	loadimage(&p_01a, _T("image\\plane\\p-01a.png"));
	loadimage(&p_01b, _T("image\\plane\\p-01b.png"));
	loadimage(&blood, _T("image\\ui\\blood\\fight.png"));
	loadimage(&bullet1, _T("image\\bullet\\sshockwave.png"));
	loadimage(&bullet2, _T("image\\bullet\\long.png"));
	loadimage(&bullet3, _T("image\\bullet\\redball.png"));
	loadimage(&bullet4, _T("image\\bullet\\rhombus.png"));
	loadimage(&bullet5, _T("image\\bullet\\bossshockwave.png"));
	loadimage(&zhujizidan, _T("image\\bullet\\zhujizidan.png"));
	loadimage(&enemy_guard, _T("image\\plane\\a-01.png"));
	loadimage(&enemy_normal, _T("image\\plane\\c-05.png"));
	loadimage(&enemy_normalb, _T("image\\plane\\c-05b.png"));

	loadimage(&enemy_quicker, _T("image\\plane\\a-10b.png"));
	loadimage(&enemy_raider, _T("image\\plane\\b-01b.png"));
	loadimage(&enemy_boss, _T("image\\plane\\mini-boss00.png"));

	loadimage(&number, _T("image\\ui\\score\\fight-number.png"));
	loadimage(&boom04, _T("image\\effect\\boom04.png"));
	loadimage(&blood_red, _T("image\\ui\\blood\\blood-red.png"));
	loadimage(&blood_enemy, _T("image\\ui\\blood\\blood_enemy.png"));
	loadimage(&ipause, _T("image\\ui\\main\\pause.png"));
	loadimage(&pausetxt, _T("image\\ui\\main\\pausetxt.png"));
	loadimage(&pausenum, _T("image\\ui\\main\\pausenum.png"));
	loadimage(&kuangkuang, _T("image\\ui\\main\\kuangkuang.png"));
	loadimage(&blink, _T("image\\ui\\main\\blink.png"));
	loadimage(&rankinglist,_T("image\\ui\\score\\rankinglist.png") );
	loadimage(&button_resume, _T("image\\ui\\main\\button-resume.png"));
	loadimage(&button_back, _T("image\\ui\\main\\button-back.png"));
	loadimage(&button_back2, _T("image\\ui\\main\\button-back2.png"));
	loadimage(&readygo, _T("image\\ui\\main\\readygo.png"));
	loadimage(&cover2, _T("image\\ui\\main\\cover2.jpg"));
	loadimage(&logo, _T("image\\ui\\main\\cover-logo.png"));
	loadimage(&logo01, _T("image\\ui\\main\\cover-logo01.png"));
	loadimage(&button_quit, _T("image\\ui\\main\\button-quit.png"));
	loadimage(&button_enter, _T("image\\ui\\main\\button-enter.png"));
	loadimage(&button_rankinglist, _T("image\\ui\\main\\button-rankinlist.png"));
	loadimage(&weapon_update, _T("image\\item\\update.png"));
	loadimage(&huifu, _T("image\\item\\huifu.png"));
	loadimage(&shield, _T("image\\item\\shield.png"));
	loadimage(&shield1, _T("image\\item\\shield1.png"));
	loadsound(&qijizaixian, _T("sounds\\菅野祐悟 - 高潔なる教皇.mp3"));
	loadsound(&planeshoot0, _T("sounds\\planeshoot0.mp3"));
	loadsound(&blast0, _T("sounds\\blast0.mp3"));
	loadsound(&sidiaole, _T("sounds\\Uru - フリージア.mp3"));
}