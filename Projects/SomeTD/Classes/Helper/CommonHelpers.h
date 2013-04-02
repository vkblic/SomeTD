#ifndef __COMMONHELPERS_H__
#define __COMMONHELPERS_H__
#include "cocos2d.h"
#include "../Model/Enumeration.h"
using namespace cocos2d;


// ccVertex helper 
static inline ccVertex2F vertex2FAdd(const ccVertex2F& v1, const ccVertex2F& v2)
{
	ccVertex2F v = {v1.x + v2.x, v1.y + v2.y};
	return v;
}

static inline ccVertex2F vertex2FMul(ccVertex2F& v1, float m)
{
	ccVertex2F v = { (v1).x * m, (v1).y = (v1).y * m };
	return v;
}
static inline float vertex2FLen(const ccVertex2F& v)
{
	return sqrt(pow(v.x, 2) + pow(v.y, 2));
}

static inline ccVertex2F vertex2FNormalization(const ccVertex2F& v1)
{
	float len = vertex2FLen(v1);
	ccVertex2F v = {v1.x / len, v1.y / len};
	return v;
}




#endif