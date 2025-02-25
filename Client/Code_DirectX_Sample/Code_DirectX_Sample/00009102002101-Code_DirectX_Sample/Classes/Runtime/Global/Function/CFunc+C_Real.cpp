#include "CFunc+C_Real.h"

/****************************
*			float			*
****************************/
bool IsLess(float a_fLhs, float a_fRhs)
{
	return a_fLhs < a_fRhs - FLT_EPSILON;
}

bool IsLessEquals(float a_fLhs, float a_fRhs)
{
	return IsLess(a_fLhs, a_fRhs) || IsEquals(a_fLhs, a_fRhs);
}

bool IsGreat(float a_fLhs, float a_fRhs)
{
	return a_fLhs > a_fRhs + FLT_EPSILON;
}

bool IsGreatEquals(float a_fLhs, float a_fRhs)
{
	return IsGreat(a_fLhs, a_fRhs) || IsEquals(a_fLhs, a_fRhs);
}

bool IsEquals(float a_fLhs, float a_fRhs)
{
	return a_fLhs >= a_fRhs - FLT_EPSILON && a_fLhs <= a_fRhs + FLT_EPSILON;
}

/****************************
*			Double			*
****************************/
bool IsLess(double a_dblLhs, double a_dblRhs)
{
	return a_dblLhs < a_dblRhs - DBL_EPSILON;
}

bool IsLessEquals(double a_dblLhs, double a_dblRhs)
{
	return IsLess(a_dblLhs, a_dblRhs) || IsEquals(a_dblLhs, a_dblRhs);
}

bool IsGreat(double a_dblLhs, double a_dblRhs)
{
	return a_dblLhs > a_dblRhs + DBL_EPSILON;
}

bool IsGreatEquals(double a_dblLhs, double a_dblRhs)
{
	return IsGreat(a_dblLhs, a_dblRhs) || IsEquals(a_dblLhs, a_dblRhs);
}

bool IsEquals(double a_dblLhs, double a_dblRhs)
{
	return a_dblLhs >= a_dblRhs - DBL_EPSILON && a_dblLhs <= a_dblRhs + DBL_EPSILON;
}
