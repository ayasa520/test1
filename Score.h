#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NON_CONFORMING_SWPRINTFS

#include <locale.h>
#include <wchar.h>
#include <stdio.h>
#include "Music.h"
#include "Resource.h"

bool Examine(wchar_t* name);
int getLogcount(FILE* fp);
void swap(struct PlayerScore* p1, struct PlayerScore* p2);
int sortLog(struct PlayerScore* p, int n);
void addNewlog(void);
void ReadLog(void);
int saveScore();
