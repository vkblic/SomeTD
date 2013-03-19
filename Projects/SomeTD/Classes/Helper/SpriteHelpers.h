
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
	for(int i = startIndex; i <= count; i++)  
	{
		sprintf(buffer, "%s_%.4d.png", textureFileName, i);
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

static CCRect GetTouchableRect(CCNode* node)
{
	CCSize size = node->getContentSize();
	CCPoint pos = node->getPosition();

	CCRect rect = CCRect(pos.x - size.width / 2, pos.y - size.height / 2, size.width, size.height);
	return rect;
}


static bool isSpriteTouched(cocos2d::CCSprite* sprite, cocos2d::CCTouch* touch)
{
	CCPoint touchPointInNodeSpace = sprite->convertTouchToNodeSpace(touch);
	CCSize size = sprite->getContentSize();
	CCRect rect = CCRect(0, 0, size.width, size.height);
	bool isTouched = rect.containsPoint(touchPointInNodeSpace);
	return isTouched;
}

static bool isRectAndCircleCollided(CCPoint& circleCentre, float radius, CCRect& rect)
{
	
	float distanceX = abs(circleCentre.x - rect.origin.x);
	float distanceY = abs(circleCentre.y - rect.origin.y);
	float halfW = rect.size.width / 2;
	float halfH = rect.size.height / 2;


	if (distanceX > (halfW + radius)) { return false; }
	if (distanceY > (halfH + radius)) { return false; }

	if (distanceX <= halfW) { return true; }
	if (distanceY <= halfH) { return true; }

	float distance = (distanceX - halfW)*(distanceX - halfW) + (distanceY-halfH)*(distanceY-halfH);

	return (distance <= radius * radius);
}


#endif
