
#ifndef _SPRITE_HELPERS_H_
#define _SPRITE_HELPERS_H_
#include "cocos2d.h"
#include "../Model/Enumeration.h"
using namespace cocos2d;
static CCAnimation* addAnimationWithFramesToCache(const char* textureFileName, const char* tag, int startIndex, int endIndex, float framesInterval, bool restoreOriginalFrame, int loopCount = -1)  
{  
	CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();  

	CCArray* framesArray = CCArray::createWithCapacity(endIndex);  
	//int bufferLen = strlen(textureFileName) + 10;
	char buffer[128] ;
	CCSpriteFrame* preFrame;
	for(int i = startIndex; i <= endIndex; i++)  
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
	animation->setDelayPerUnit(framesInterval * SECOND_PER_FRAME);

	auto animationCache = CCAnimationCache::sharedAnimationCache();
	sprintf(buffer, "%s_%s", textureFileName, tag);

	animationCache->addAnimation(animation, buffer);
	//delete buffer;
	return animation;
}  

static void buildAnimationFrameArray(std::vector<CCSpriteFrame*>** arr, const char* textureFileName, int startIndex, int endIndex)
{
	CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();  
	std::vector<CCSpriteFrame*>* tempArray = new std::vector<CCSpriteFrame*>();
	char buffer[256];
	for(int i = startIndex; i <= endIndex; i++)  
	{
		sprintf(buffer, "%s_%.4d.png", textureFileName, i);
		CCSpriteFrame* frame = cache->spriteFrameByName(buffer); 
		if(frame == NULL)
			frame = nullptr;
		tempArray->push_back(frame);
	}  
	(*arr) = tempArray;
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
	
	float distanceX = abs(circleCentre.x - rect.getMidX());
	float distanceY = abs(circleCentre.y - rect.getMidY());
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
