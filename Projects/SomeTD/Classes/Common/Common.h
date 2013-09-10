// 
//  Enumeration.h
//  MyMoonWarriors
//
//  By Kelyad on 11/04/2012
//

#ifndef _COMMON_H_
#define _COMMON_H_

#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include "cocos2d.h"

using namespace cocos2d;
#define EnumStr(e) #e

#define assertMsg(a, b) assert(a && b)

typedef unsigned __int64 uint64;
typedef unsigned int uint32;
typedef unsigned short uint16;
typedef unsigned char uint8;

// id seed
typedef uint64 ENTITY_ID;
const ENTITY_ID nonEntity = -1;
#define non_entity nonEntity

inline void kkAssertMsg(bool cond, const char* msg)
{
	if (cond)
		return;
	CCLog(msg);
	assertMsg(cond, msg);
}


const int MAX_LOG_LEN = 16*1024;
inline void kkAssertMsgf(bool cond, const char * pszFormat, ...)
{
	if (cond)
		return;
	char szBuf[MAX_LOG_LEN];

	va_list ap;
	va_start(ap, pszFormat);
	//vsnprintf_l(szBuf, MAX_LOG_LEN, MAX_LOG_LEN, pszFormat, ap);
	vsnprintf(szBuf, MAX_LOG_LEN, pszFormat, ap);
	va_end(ap);
	kkAssertMsg(cond, szBuf);
}




//rand

inline int rangedRand(int range_min, int range_max)
{
	int r = (double)rand() / (RAND_MAX + 1) * (range_max - range_min)
		+ range_min;
	return r;
}


#endif
