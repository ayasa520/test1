#include "Score.h"
struct PlayerScore {
	wchar_t name[6];
	int score;
};
int size = sizeof(struct PlayerScore);

//检查输入的名字是否符合规范
bool Examine(wchar_t* name)
{
	int i;
	int isSpace = 0;
	if (name[0] == L'\0')
		return 0;
	for (i = 0; i < (int)wcslen(name); i++)
	{
		if (name[i] == L' ')
		{
			isSpace = 1;
			break;
		}
	}
	return !isSpace;
}
//获取当前记录条数
int getLogcount(FILE* fp)
{
	int begin, end, logcount;
	fseek(fp, 0L, SEEK_SET);
	begin = ftell(fp);
	fseek(fp, size, SEEK_END);
	end = ftell(fp);
	logcount = (end - begin) / size - 1;
	return logcount;
}
//交换
void swap(struct PlayerScore* p1, struct PlayerScore* p2)
{
	struct PlayerScore p3 = *p1;
	*p1 = *p2;
	*p2 = p3;
}
//对记录文件排序，最多保留10条记录
int sortLog(struct PlayerScore* p, int n)
{
	FILE* fp = fopen("score.cs", "wb");
	int i, j;
	int cnt;
	int index = 0;
	for (i = 0; i < n; i++)
	{
		index = i;
		for (j = i + 1; j < n; j++)
			if (p[j].score > p[i].score)
				index = j;
		swap(p + index, p + i);
	}
	cnt = n >= 10 ? 10 : n;
	if (fwrite(p, size, cnt, fp) == 0)
	{
		//MessageBoxW(NULL, L"写入记录失败！！\n", L"警告", MB_OK);
		//exit(0);
	}
	fclose(fp);

	return cnt;
}
//新加一条记录
void addNewlog(void) {
	FILE* fp;
	struct PlayerScore PS;
	if ((fp = fopen("score.cs", "ab")) == NULL)
	{
		MessageBoxW(NULL, L"打开失败！！\n", L"警告", MB_OK);
		exit(0);
	}
	InputBox(PS.name, 6, L"请输入您的名字(支持中文)");
	while (!Examine(PS.name))
	{
		MessageBoxW(NULL, L"输入为空或含有空格！！", L"ERROR", MB_OK);
		InputBox(PS.name, 6, L"请输入您的名字(支持中文)");
	}
	PS.score = score;
	fwrite(&PS, size, 1, fp);
	fclose(fp);
}
//读取记录并显示在绘图窗口
void ReadLog(void)
{

	LOGFONT f;
	gettextstyle(&f);						// 获取当前字体设置
	f.lfHeight = 40;						// 设置字体高度为 40
	f.lfQuality = PROOF_QUALITY;			// 设置输出效果 
	_tcscpy(f.lfFaceName, L"微软雅黑");	// 设置字体为“微软雅黑”(高版本 VC 推荐使用 _tcscpy_s 函数)

	settextstyle(&f);						// 设置字体样式
	setlocale(LC_ALL, ".936");
	FILE* fp;
	struct PlayerScore* PS;
	int i = 0;
	if ((fp = fopen("score.cs", "rb")) == NULL)
	{
		MessageBoxW(NULL, L"打开失败！！\n", L"警告", MB_OK);
		exit(0);
	}
	int count = getLogcount(fp);
	PS = (struct PlayerScore*)malloc(count * size);
	rewind(fp);
	//while (!feof(fp))
	if (fread(&(PS[i++]), size, count, fp) == 0)
	{
		//MessageBoxW(NULL, L"记录为空\n", L"提示", MB_OK);
		
	}
	fclose(fp);
	count = sortLog(PS, count);

	for (int i = 0; i < count; i++)
	{
		wchar_t s[10];
		if (swprintf(s, L"%d", PS[i].score) < 0)
		{
			//MessageBoxW(NULL, L"写入记录失败！！\n", L"警告", MB_OK);
		}//将得分写入s字符数组
		setbkmode(TRANSPARENT);					//字体透明背景色
		outtextxy(120, 160+50 * i, PS[i].name);	//在绘图窗口显示名字
		outtextxy(400, 160+50 * i, s);			//在绘图窗口显示分数
	}

}

int saveScore()
{
	stopsound(0);
	playsound(3, 1);

	addNewlog();
	Sleep(2000);
	stopsound(3);
	return 1;
}