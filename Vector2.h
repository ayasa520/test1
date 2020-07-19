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
	//����

};
void set(Vector2* v, double fx, double fy);
//ƽ��
void translate(Vector2* v, double fx, double fy);
//�Ƿ�������
bool isZero(Vector2* v);
//�Ƿ�1����
bool isOne(Vector2* v);
//����
void scale(Vector2* v, double fx, double fy);
//��ת����ĳ������ת���ٻ��ȣ�
void rotate(Vector2* v, Vector2* point, double radians);
//��λ��
void normalize(Vector2* v);
// �����������ƶ�dis����
void forward(Vector2* v, double dis);
//���
void back(Vector2* v, double dis);
//�нǣ����ȣ�
double dot(Vector2* v, Vector2* other);
// ������ģ
double angle(Vector2* v, Vector2* other);
// ������ģƽ��
double module(Vector2* v);
//����
double modulePower2(Vector2* v);
// ����ƽ��
double distance(Vector2* v, const Vector2* other);
// ͶӰ
double distancePower2(Vector2* v, const Vector2* other);
// ˳ʱ�봹ֱ����
Vector2 projection(Vector2* v, Vector2* other);

Vector2 right(Vector2* v);
// ��ʱ�봹ֱ����
Vector2 left(Vector2* v);
