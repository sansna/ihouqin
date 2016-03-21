#include "stdafx.h"
#ifndef ACCRATIODLL_H
#define ACCRATIODLL_H

#ifdef DLL_EXPORTS
#define ACCRATIODLL_API __declspec(dllexport)
#else
#define ACCRATIODLL_API __declspec(dllimport)
#endif

extern "C"{
	ACCRATIODLL_API int AR(string);
	ACCRATIODLL_API string TFILE_NAME_GEN(int);
	ACCRATIODLL_API int FILE_NAME_INT(char*);
	ACCRATIODLL_API string WSTR_TO_UTF8(const wchar_t*,int);
};

#endif