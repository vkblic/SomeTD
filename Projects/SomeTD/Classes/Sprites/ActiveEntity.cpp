//
//  Bullet.cpp
//  TileGameDemo
//
//  Created by kelyad on 02-17-2013.
//

#include "ActiveEntity.h"
#include "../Managers/EnemyManager.h"
#include "../Managers/AllyManager.h"
#include "../Helper/CommonHelpers.h"
#include <math.h>
using namespace cocos2d;
ActiveEntity* ActiveEntity::create(ActiveObjModel* entityInfo, CCSpriteBatchNode* hpBatchNode)
{

	//CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pszSpriteFrameName);
	ActiveEntity *entity = new ActiveEntity();
	if (entity && entity->initWithSpriteFrame(entityInfo->defaultFrame))//
	{
		entity->mHpBatchNode = hpBatchNode;
		entity->mEntityInfo = entityInfo;
		entity->myInit();
		//tower->loadResource();
		entity->autorelease();
		//CCLog("Enemy node retainCount:  %d", enemy->retainCount());
		return entity;
	}
	CC_SAFE_DELETE(entity);
	return NULL;
}

void ActiveEntity::myInit()
{
	mHp = CCSprite::create("hp.png");
	mDefualtColorRect = this->getColorRect();
	mCurHP = this->mEntityInfo->hp;
	mHp->setAnchorPoint(CCPoint(0,0));
	mHpBatchNode->addChild(this->mHp);
	mHpBarMaxWidth = mDefualtColorRect.size.width > HP_BAR_WIDTH ? HP_BAR_WIDTH : mDefualtColorRect.size.width * 0.8;
	mState = STATE_NULL;

	this->updateHpSpriteSize();
	this->setHpSpritePosition();
}

CCRect ActiveEntity::getCollisionRect()
{
	//auto colorRect = this->getColorRect();
	CCPoint pos = this->getPosition();
	auto size = this->getContentSize();

	/* calculate detail
	 *	left_bottom_X = pos.x - size.width / 2
	 *	left_bottom_Y = pos.y - size.height / 2
	 *	left_bottom_ColorRect_X = colorRect.origin.x
	 *	left_bottom_ColorRect_Y = size.height - colorRect.size.height - colorRect.origin.y
 	 *  final_X =  left_bottom_X + left_bottom_ColorRect_X
	 *	final_Y =  left_bottom_Y + left_bottom_ColorRect_Y*/

	float x = pos.x - size.width / 2 + mDefualtColorRect.getMinX();
	float y = pos.y + size.height / 2 - mDefualtColorRect.getMaxY();

	//CCRect old(pos.x, pos.y, size.width, size.height);

	//CCLog("colorRect: {{%f, %f}, {%f, %f}}",colorRect.origin.x, colorRect.origin.y, colorRect.size.width, colorRect.size.height);
	//CCLog("collisionRect Old: {{%f, %f}, {%f, %f}}",old.origin.x, old.origin.y, old.size.width, old.size.height);
	//CCLog("collisionRect New: {{%f, %f}, {%f, %f}}",x, y, colorRect.size.width, colorRect.size.height);
	return CCRect(x, y, mDefualtColorRect.size.width, mDefualtColorRect.size.height);
}

void ActiveEntity::setHpSpritePosition()
{
	//CCSize enemySize = this->getContentSize();
	//CCPoint pos = this->getPosition();
	CCRect collisionRect = this->getCollisionRect();

	auto newPos = CCPoint(collisionRect.getMinX() + (collisionRect.size.width - mHpBarMaxWidth) / 2, collisionRect.getMaxY() + 2);
	this->mHp->setPosition(newPos);

}
void ActiveEntity::updateHpSpriteSize()
{
	//CCAssert(hp >= 0 && hp <= this->mMaxHP, "hp percent value of enemy node is not allow!");
	//this->mCurHP = hp;
	if (this->mCurHP <= 0)
	{
		this->mHp->setVisible(false);
	}
	float precentOfHp = (float)this->mCurHP / (float)this->mEntityInfo->hp;

	//CCSize enemySize = this->getColorRect().size;
	CCSize sizeHp =  this->mHp->getContentSize();

	float scaleX = mHpBarMaxWidth / sizeHp.width * precentOfHp;
	//CCLog("scaleX%f",scaleX);
	//CCLog("Enemy hp: scaleX: %f, scaleY: %f", scaleX, scaleY);
	this->mHp->setScaleX(scaleX);
}

