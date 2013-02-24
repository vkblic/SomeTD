
#ifndef _SPRITE_HELPERS_H_
#define _SPRITE_HELPERS_H_
#include "cocos2d.h"
using namespace cocos2d;
static CCAnimation* addAnimationWithFramesToCache(const char* textureFileName, const char* aniamtionName, int startIndex, int count, float delay, bool restoreOriginalFrame, int loopCount = -1)  
{  
	CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();  

	CCArray* framesArray = CCArray::createWithCapacity(count);  
	int bufferLen = strlen(textureFileName) + 10;
	char *buffer = new char[bufferLen];
	CCSpriteFrame* preFrame;
	for(int i = 1; i <= count; i++)  
	{
		sprintf_s(buffer, bufferLen, "%s_%.4d.png", textureFileName, i);
		CCSpriteFrame* frame = cache->spriteFrameByName(buffer); 
		if(frame == NULL)
			frame = preFrame;
		framesArray->addObject(frame);
		preFrame = frame;
	}  


	CCAnimation* animation = CCAnimation::createWithSpriteFrames(framesArray);
	animation->setLoops(loopCount);
	animation->setRestoreOriginalFrame(restoreOriginalFrame);
	animation->setDelayPerUnit(delay);

	auto animationCache = CCAnimationCache::sharedAnimationCache();
	animationCache->addAnimation(animation, aniamtionName);
	delete buffer;
	return animation;
}  

#endif
