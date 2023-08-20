#ifndef __Z1C_H__
#define __Z1C_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <Windows.h>
#include "Z1_BaseMacro.h"


#define ROOTPATH_CVIMG				"..\\Resource\\CVImg"
#define ROOTPATH_CVIMG_BGO			"..\\Resource\\CVImg\\BGO"
#define ROOTPATH_CVIMG_TARGET		"..\\Caches\\zScreencap.png"
#define ROOTPATH_PHONESCREENCAP		"/sdcard/z1Caches/zScreencap.png"


typedef void (*ZArrayCreate)(void* pArray, void* vpData);


enum ZARRAYTYPE
{
	ZHEAD,
	ZVOID,
	ZSHORT,
	ZINT,
	ZLONG,
	ZSTRING,
};

struct _tZArray
{
	unsigned int unCount;
	void* vpData;
	ZARRAYTYPE emType;
	struct _tZArray* ptHeadNode;
	struct _tZArray* ptTailNode;
	struct _tZArray* ptNext;
	ZArrayCreate append;
};

typedef struct _tZArray ZARRAY, * LPZARRAY;

void ZCreateArray(LPZARRAY* ppArray, ZARRAYTYPE emType);
void ZCreateArrayNextNode(void* pArray, void* vpData);
void ZCreateArrayFn(LPZARRAY pArray);


#endif // __Z1C_H__
