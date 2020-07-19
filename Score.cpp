#include "Score.h"
struct PlayerScore {
	wchar_t name[6];
	int score;
};
int size = sizeof(struct PlayerScore);

//�������������Ƿ���Ϲ淶
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
//��ȡ��ǰ��¼����
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
//����
void swap(struct PlayerScore* p1, struct PlayerScore* p2)
{
	struct PlayerScore p3 = *p1;
	*p1 = *p2;
	*p2 = p3;
}
//�Լ�¼�ļ�������ౣ��10����¼
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
		//MessageBoxW(NULL, L"д���¼ʧ�ܣ���\n", L"����", MB_OK);
		//exit(0);
	}
	fclose(fp);

	return cnt;
}
//�¼�һ����¼
void addNewlog(void) {
	FILE* fp;
	struct PlayerScore PS;
	if ((fp = fopen("score.cs", "ab")) == NULL)
	{
		MessageBoxW(NULL, L"��ʧ�ܣ���\n", L"����", MB_OK);
		exit(0);
	}
	InputBox(PS.name, 6, L"��������������(֧������)");
	while (!Examine(PS.name))
	{
		MessageBoxW(NULL, L"����Ϊ�ջ��пո񣡣�", L"ERROR", MB_OK);
		InputBox(PS.name, 6, L"��������������(֧������)");
	}
	PS.score = score;
	fwrite(&PS, size, 1, fp);
	fclose(fp);
}
//��ȡ��¼����ʾ�ڻ�ͼ����
void ReadLog(void)
{

	LOGFONT f;
	gettextstyle(&f);						// ��ȡ��ǰ��������
	f.lfHeight = 40;						// ��������߶�Ϊ 40
	f.lfQuality = PROOF_QUALITY;			// �������Ч�� 
	_tcscpy(f.lfFaceName, L"΢���ź�");	// ��������Ϊ��΢���źڡ�(�߰汾 VC �Ƽ�ʹ�� _tcscpy_s ����)

	settextstyle(&f);						// ����������ʽ
	setlocale(LC_ALL, ".936");
	FILE* fp;
	struct PlayerScore* PS;
	int i = 0;
	if ((fp = fopen("score.cs", "rb")) == NULL)
	{
		MessageBoxW(NULL, L"��ʧ�ܣ���\n", L"����", MB_OK);
		exit(0);
	}
	int count = getLogcount(fp);
	PS = (struct PlayerScore*)malloc(count * size);
	rewind(fp);
	//while (!feof(fp))
	if (fread(&(PS[i++]), size, count, fp) == 0)
	{
		//MessageBoxW(NULL, L"��¼Ϊ��\n", L"��ʾ", MB_OK);
		
	}
	fclose(fp);
	count = sortLog(PS, count);

	for (int i = 0; i < count; i++)
	{
		wchar_t s[10];
		if (swprintf(s, L"%d", PS[i].score) < 0)
		{
			//MessageBoxW(NULL, L"д���¼ʧ�ܣ���\n", L"����", MB_OK);
		}//���÷�д��s�ַ�����
		setbkmode(TRANSPARENT);					//����͸������ɫ
		outtextxy(120, 160+50 * i, PS[i].name);	//�ڻ�ͼ������ʾ����
		outtextxy(400, 160+50 * i, s);			//�ڻ�ͼ������ʾ����
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