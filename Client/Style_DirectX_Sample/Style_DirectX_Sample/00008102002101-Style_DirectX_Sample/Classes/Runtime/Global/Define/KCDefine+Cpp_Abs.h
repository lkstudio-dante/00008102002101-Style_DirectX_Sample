#pragma once
#pragma warning(disable: 4005)

#define _CRT_SECURE_NO_WARNINGS

#include "KCDefine+C_Abs.h"

#include <iostream>
#include <cassert>
#include <string>

#include <chrono>
#include <memory>
#include <filesystem>
#include <functional>
#include <algorithm>

#include <vector>
#include <unordered_map>

// 컬렉션
#define STD_VECTOR(TYPE)					std::vector<TYPE>
#define STD_UNORDERED_MAP(KEY, VAL)			std::unordered_map<KEY, VAL>

// 메모리
#define SAFE_DELETE(TARGET)					if((TARGET) != nullptr) { delete (TARGET); (TARGET) = nullptr; }
#define SAFE_DELETE_ARRAY(TARGET)			if((TARGET) != nullptr) { delete[] (TARGET); (TARGET) = nullptr; }

// 접근자 {
#define GET_MANAGER_TIME()			(CManager_Time::GetInst())

#define GETTER(TYPE_DATA, NAME_FUNC, NAME_VAR)			inline virtual TYPE_DATA Get##NAME_FUNC(void) const { return NAME_VAR; }
#define SETTER(TYPE_DATA, NAME_FUNC, NAME_VAR)			inline virtual void Set##NAME_FUNC(TYPE_DATA a_tVal) { NAME_VAR = a_tVal; }

#define GETTER_SETTER(TYPE_DATA, NAME_FUNC, NAME_VAR)			\
GETTER(TYPE_DATA, NAME_FUNC, NAME_VAR)							\
SETTER(TYPE_DATA, NAME_FUNC, NAME_VAR)

#define GETTER_PROPERTY(TYPE_DATA, NAME_FUNC, NAME_VAR)			\
private:														\
TYPE_DATA NAME_VAR;												\
public:															\
GETTER(TYPE_DATA, NAME_FUNC, NAME_VAR)

#define GETTER_PROPERTY_WITH_INIT(TYPE_DATA, NAME_FUNC, NAME_VAR, VAL)			\
private:																		\
TYPE_DATA NAME_VAR = VAL;														\
public:																			\
GETTER(TYPE_DATA, NAME_FUNC, NAME_VAR)

#define GETTER_SETTER_PROPERTY(TYPE_DATA, NAME_FUNC, NAME_VAR)			\
private:																\
TYPE_DATA NAME_VAR;														\
public:																	\
GETTER_SETTER(TYPE_DATA, NAME_FUNC, NAME_VAR)

#define GETTER_SETTER_PROPERTY_WITH_INIT(TYPE_DATA, NAME_FUNC, NAME_VAR, VAL)			\
private:																				\
TYPE_DATA NAME_VAR = VAL;																\
public:																					\
GETTER_SETTER(TYPE_DATA, NAME_FUNC, NAME_VAR)
// 접근자 }

// 싱글턴
#define SINGLETON(TYPE_CLS)					\
protected:									\
TYPE_CLS(void);								\
virtual ~TYPE_CLS(void);					\
public:										\
static TYPE_CLS* GetInst(void)				\
{											\
	static TYPE_CLS oInst;					\
	return &oInst;							\
}
