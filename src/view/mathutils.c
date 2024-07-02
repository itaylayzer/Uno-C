#include "mathutils.h"

float lerp(float a, float b, float f)
{
    return a * (1.0 - f) + (b * f);
}
float fmax(float x, float y)
{
    return x > y ? x : y;
}
float fmin(float x, float y)
{
    return x > y ? y : x;
}
float fclamp(float val, float _min, float _max)
{
    return fmax(fmin(val, _max), _min);
}
float fabs(float val)
{
    return val * (val < 0 ? -1 : 1);
}

int max(int a, int b)
{
    return a > b ? a : b;
}
int min(int a, int b)
{
    return a > b ? b : a;
}
int clamp(int val, int _min, int _max)
{
    return max(min(val, _max), _min);
}

short sabs(short val)
{
    return ((val > 0) * 2 - 1) * val;
}