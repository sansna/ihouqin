// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             //  从 Windows 头文件中排除极少使用的信息
// Windows 头文件:
#include <windows.h>

#include <stdio.h>
#include <tchar.h>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

#define _IN_ 
#define _OUT_
#define _OPT_

using namespace std;

const int cnGItemNum = 1;
const int cnBItemNum = 4;
const int cnGWCCount = 4;
const int cnBWCCount = 18;
const int cnLength = 16; // 运单号长度会变化
const int cnDateLen = 25;//时间长度变
const int cnNameMLen = 30;//这个会变化
const int cnDeptLen = 32;//变长
const int cnMarkLen = 5;//不变

const int DateBenchmark = 2016 * 12 + 3;

static int g_nTotalScanned = 0;

typedef struct STRGREEN{
	char* cCode;
	STRGREEN *pNextGreen;

}strGreen,*pstrGreen;

typedef struct STRBLUE{
	char *cCode,*cName,*cDate,*cDept;
	STRBLUE *pNextBlue;

}strBlue,*pstrBlue;

typedef struct STRCHART1{
	char* cCode;//PK
	char* cName, *cDate,*cDept;
	int nMark;
	STRCHART1 *pNextChart1;

}strChart1,*pstrChart1;

typedef struct STRTRADE{
	char* cCode;
	int nMark;
	char* cDept;
	STRTRADE *pNextTrade;

}strTrade,*pstrTrade;

typedef struct STRCHART2{
	char* cName;//PK+
	char* cDate;
	pstrTrade pstrTrd;
	STRCHART2 *pNextChart2;

}strChart2,*pstrChart2;

typedef struct STRCHART0{
	char* cCode;
	STRCHART0* pNextChart0;
}strChart0, *pstrChart0;
