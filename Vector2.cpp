#pragma once
#include "Vector2.h"
void set(Vector2* v,double fx, double fy) {
	v->x = fx;
	v->y = fy;
}
void translate(Vector2* v,double fx, double fy) {
	v->x += fx;
	v->y += fy;
}
bool isZero(Vector2* v) {
	return _IS_DOUBLE_ZERO(v->x) && _IS_DOUBLE_ZERO(v->y);
}
bool isOne(Vector2* v) {
	return _IS_DOUBLE_ZERO(v->x - 1) && _IS_DOUBLE_ZERO(v->y - 1);
}
void scale(Vector2* v, double fx, double fy) {
	v->x = v->x * fx;
	v->y = v->y * fy;
}
void rotate(Vector2* v, Vector2* point, double radians) {
	double sinRadians = sin(radians);
	double cosRadians = cos(radians);

	if (isZero(point)) {
		double tempX = v->x * cosRadians - v->y * sinRadians;
		v->y = v->y * cosRadians + v->x * sinRadians;
		v->x = tempX;
	}
	else {
		double tempX = v->x - (*point).x;
		double tempY = v->y - (*point).y;

		v->x = tempX * cosRadians - tempY * sinRadians + (*point).x;
		v->y = tempY * cosRadians + tempX * sinRadians + (*point).y;
	}

}
void normalize(Vector2* v ) {
	double len = v->x * v->x + v->y * v->y;
	if (len == 1) {
		return;
	}
	double n = sqrt(len);
	if (_IS_DOUBLE_ZERO(n)) {
		return;
	}
	n = 1 / n;
	v->x *= n;
	v->y *= n;
}
void forward(Vector2* v, double dis)
{
	static Vector2 vec;
	vec.x = v->x;
	vec.y = v->y;
	normalize(&vec);
	vec.x *= dis;
	vec.y *= dis;
	v->x += vec.x;
	v->y += vec.y;
}
void back(Vector2* v, double dis)
{
	static Vector2 vec;
	vec.x = v->x;
	vec.y = v->y;
	normalize(&vec);
	vec.x *= dis;
	vec.y *= dis;
	v->x -= vec.x;
	v->y -= vec.y;
}
double dot(Vector2* v, Vector2* other) {
	return v->x * other->x + v->y * other->y;
}
double angle(Vector2* v, Vector2* other) {
	static Vector2* v1 = (Vector2*)malloc(sizeof(Vector2));
	static Vector2* v2 = (Vector2*)malloc(sizeof(Vector2));
	set(v1, v->x, v->y);
	v2 = other;
	normalize(v1);
	normalize(v2);
	double cosRadians = dot(v1,v2);

	// 使用三维向量叉乘处理正负问题
	// A(src->x,src->y,1) B(dest->x,dest->y,1)
	// z = x1y2-y1x2
	double z = v->x * other->y - v->y * other->x;
	return z >= 0 ? acos(cosRadians) : -acos(cosRadians);
}
double module(Vector2* v ) {
	return sqrt(v->x * v->x + v->y * v->y);
}
double modulePower2(Vector2* v ) {
	return  v->x * v->x + v->y * v->y;
}
double distance(Vector2* v, const Vector2* other)
{
	double dx = other->x - v->x;
	double dy = other->y - v->y;
	return sqrt(dx * dx + dy * dy);
}
double distancePower2(Vector2* v, const Vector2* other)
{
	double dx = other->x - v->x;
	double dy = other->y - v->y;
	return  dx * dx + dy * dy;
}
Vector2 projection(Vector2* v, Vector2* other)
{
	Vector2 vn;

	double len2 = modulePower2(other);
	len2 = 1 / len2;
	double tmp = (v->x * other->x + v->y * other->y) * len2;
	set(&vn,other->x * tmp, other->y * tmp);
	return vn;
}
Vector2 right(Vector2* v ) {
	 Vector2 vn;
	set(&vn, v->y, -v-> x);
	return vn;
}
Vector2 left(Vector2* v)
{
	Vector2 vn ;
	set(&vn,-v->y, v->x);
	return vn;
}
