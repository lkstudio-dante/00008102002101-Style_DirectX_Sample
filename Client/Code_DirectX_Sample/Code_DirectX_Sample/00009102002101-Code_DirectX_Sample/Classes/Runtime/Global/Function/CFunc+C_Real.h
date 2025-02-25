#pragma once

#include "../Define/KCDefine+C_Abs.h"

/****************************
*			float			*
****************************/
/** 작음 여부를 검사한다 */
bool IsLess(float a_fLhs, float a_fRhs);

/** 작거나 같음 여부를 검사한다 */
bool IsLessEquals(float a_fLhs, float a_fRhs);

/** 큼 여부를 검사한다 */
bool IsGreat(float a_fLhs, float a_fRhs);

/** 크거나 같음 여부를 검사한다 */
bool IsGreatEquals(float a_fLhs, float a_fRhs);

/** 같음 여부를 검사한다 */
bool IsEquals(float a_fLhs, float a_fRhs);

/****************************
*			Double			*
****************************/
/** 작음 여부를 검사한다 */
bool IsLess(double a_dblLhs, double a_dblRhs);

/** 작거나 같음 여부를 검사한다 */
bool IsLessEquals(double a_dblLhs, double a_dblRhs);

/** 큼 여부를 검사한다 */
bool IsGreat(double a_dblLhs, double a_dblRhs);

/** 크거나 같음 여부를 검사한다 */
bool IsGreatEquals(double a_dblLhs, double a_dblRhs);

/** 같음 여부를 검사한다 */
bool IsEquals(double a_dblLhs, double a_dblRhs);
