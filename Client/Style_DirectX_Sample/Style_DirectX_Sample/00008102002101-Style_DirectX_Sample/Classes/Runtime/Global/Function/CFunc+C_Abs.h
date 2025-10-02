#pragma once

#include "../Define/KCDefine+C_Abs.h"
#include "CFunc+C_Real.h"

#if !defined MIN
#define MIN(LHS, RHS)			(((LHS) <= (RHS)) ? (LHS) : (RHS))
#endif // #if !defined MIN

#if !defined MAX
#define MAX(LHS, RHS)			(((LHS) >= (RHS)) ? (LHS) : (RHS))
#endif // #if !defined MAX

#if !defined SWAP
#define SWAP(TYPE_DATA, LHS, RHS)			{ TYPE_DATA _VAR_TEMP_ = (LHS); (LHS) = (RHS); (RHS) = _VAR_TEMP_; }
#endif // #if !defined SWAP
