#pragma once
#pragma warning(disable: 4005)

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <ctype.h>
#include <time.h>
#include <math.h>
#include <float.h>

#include "KCDefine+C_File.h"

// 메모리
#define SAFE_FREE(TARGET)			if((TARGET) != nullptr) { free((TARGET)); (TARGET) = nullptr; }
#define SAFE_CLOSE(TARGET)			if((TARGET) != nullptr) { fclose((TARGET)); (TARGET) = nullptr; }

// 기타 {
static const int G_ID_INVALID = -1;
static const int G_IDX_INVALID = ::G_ID_INVALID;
static const int G_KEY_INVALID = ::G_ID_INVALID;

static const int G_COMPARE_LESS = -1;
static const int G_COMPARE_GREAT = 1;
static const int G_COMPARE_EQUALS = 0;

static const char G_STR_EMPTY[] = "";
static const char G_TOKEN_PATH[] = "/";
// 기타 }
