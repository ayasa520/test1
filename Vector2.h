#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <float.h>
#include <math.h>
#include "Shoot.h"
#define _IS_DOUBLE_ZERO(val) (fabs(val)<DBL_EPSILON)
struct Vector2
{
	union {
		struct
		{
			double x, y;
		};
		double v[2];
	};
	//设置

};
void set(Vector2* v, double fx, double fy);
//平移
void translate(Vector2* v, double fx, double fy);
//是否零向量
bool isZero(Vector2* v);
//是否1向量
bool isOne(Vector2* v);
//缩放
void scale(Vector2* v, double fx, double fy);
//旋转（绕某个点旋转多少弧度）
void rotate(Vector2* v, Vector2* point, double radians);
//单位化
void normalize(Vector2* v);
// 向向量方向移动dis距离
void forward(Vector2* v, double dis);
//点乘
void back(Vector2* v, double dis);
//夹角（弧度）
double dot(Vector2* v, Vector2* other);
// 向量的模
double angle(Vector2* v, Vector2* other);
// 向量的模平方
double module(Vector2* v);
//距离
double modulePower2(Vector2* v);
// 距离平方
double distance(Vector2* v, const Vector2* other);
// 投影
double distancePower2(Vector2* v, const Vector2* other);
// 顺时针垂直向量
Vector2 projection(Vector2* v, Vector2* other);

Vector2 right(Vector2* v);
// 逆时针垂直向量
Vector2 left(Vector2* v);
