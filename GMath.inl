#ifndef __GMATH_INL__
#define __GMATH_INL__
static const double PI = 3.1415926535897932;
static const double r2d = 180 / PI;
static const double d2r = PI / 180;

inline double radians2degrees(double radians) {
	return radians * r2d;
}
inline double degrees2radians(double degrees) {
	return degrees * d2r;
}
#endif //__GMATH_INL__