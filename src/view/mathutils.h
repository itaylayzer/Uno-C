#ifndef _INC_MATH_UTILS
#define _INC_MATH_UTILS

float lerp(float a, float b, float f);
float fmax(float x, float y);
float fmin(float x, float y);
float fclamp(float val, float _min, float _max);
float fabs(float val);
int max(int a, int b);
int min(int a, int b);
int clamp(int val, int _min, int _max);
short sabs(short val);
#endif