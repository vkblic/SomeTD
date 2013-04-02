//
//  Bullet.cpp
//  TileGameDemo
//
//  Created by kelyad on 02-17-2013.
//

#include "AllyUnit.h"
#include "../Managers/EnemyManager.h"
#include "../Managers/AlliesManager.h"
#include "../Helper/CommonHelpers.h"
#include <math.h>
using namespace cocos2d;
AllyUnit* AllyUnit::create(ActiveObjModel* enemyInfo, CCSpriteBatchNode* hpBatchNode)
{

	//CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pszSpriteFrameName);
	AllyUnit *enemy = new AllyUnit();
	if (enemy && enemy->initWithSpriteFrame(enemyInfo->defaultFrame))//
	{
		enemy->mHpBatchNode = hpBatchNode;
		enemy->mAllyInfo = enemyInfo;
		enemy->myInit();
		//tower->loadResource();
		enemy->autorelease();
		//CCLog("Enemy node retainCount:  %d", enemy->retainCount());
		return enemy;
	}
	CC_SAFE_DELETE(enemy);
	return NULL;
}
AllyUnit::~AllyUnit()
{
}

void AllyUnit::myInit()
{

	mDefualtColorRect = this->getColorRect();
	mHp = CCSprite::create("hp.png");
	mCurWayPointIndex = 0;
	mTargetID = -1;
	mCurHP = this->mAllyInfo->hp;
	mHp->setAnchorPoint(CCPoint(0,0));
	mHpBatchNode->addChild(this->mHp);
	mHpBarMaxWidth = mDefualtColorRect.size.width > HP_BAR_WIDTH ? HP_BAR_WIDTH : mDefualtColorRect.size.width * 0.8;
	this->updateHpSpriteSize();
	this->setHpSpritePosition();
	//this->addChild(hpC);

}

bool AllyUnit::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	return false;
}

void AllyUnit::ccTouchMoved(CCTouch* touch, CCEvent* event)
{


}

void AllyUnit::ccTouchEnded(CCTouch* touch, CCEvent* event)
{


	//CCLog("%s","精灵33~~~ccTouchEnded");
} 

//---SpriteClassModel 起始结束的生命周期函数----
void AllyUnit::onEnter()
{
	//注册监听   1.dele类，2.优先级，3.YES为阻碍其他类的move 和 end

	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
	CCSprite::onEnter();
}

void AllyUnit::onExit()
{
	//移除监听
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCSprite::onExit();
}


void AllyUnit::update(float dt)
{

	// update postion of hp bar
	this->setHpSpritePosition();

	auto enemyManager = EnemyManager::sharedEnemyManager();

	if(mCurStatus == AllyStatus_Moving || mCurStatus == AllyStatus_MovingToTarget)
	{
		return;
	}

	if(!enemyManager->isEnemyInRange(this->getPosition(), mAllyInfo->alertRange, mTargetID))
	{
		long id = enemyManager->getEnemyInRange(this->getPosition(), mAllyInfo->alertRange);
		if(id != -1)
		{
			mTargetID = id;
			auto enemy = enemyManager->getAvailableEnemy(mTargetID);
			enemy->targetAlert(this->mID);
			// let enemy stop running 
			// note: the pos is not the center point of collision rect!
			// 1. get distance color(collision) rect of ally

			CCRect targetCollisionRect = enemy->getCollisionRect();
			CCRect CollisionRect = this->getCollisionRect();

			CCPoint distColorRectLeftTop;
			if(targetCollisionRect.getMidX() > CollisionRect.getMidX())
			{
				// move to left of the target
				distColorRectLeftTop.x = targetCollisionRect.getMinX() - mDefualtColorRect.size.width;
			}
			else
			{
				// move to right of the target
				distColorRectLeftTop.x = targetCollisionRect.getMaxX();
			}
			distColorRectLeftTop.y = targetCollisionRect.getMinY() + mDefualtColorRect.size.height;

			CCPoint distSpriteRectLeftTop = CCPoint(
				distColorRectLeftTop.x - mDefualtColorRect.origin.x,
				distColorRectLeftTop.y + mDefualtColorRect.origin.y
			);
			CCSize size = this->getContentSize();
			CCPoint distPos = CCPoint(
				distSpriteRectLeftTop.x + size.width / 2,
				distSpriteRectLeftTop.y - size.height / 2
			);

			// start move to animation
			CCSequence* sequence = CCSequence::create(
				CCMoveTo::create(1, distPos ),
				CCCallFunc::create(this, callfunc_selector(AllyUnit::startAttack)),
				NULL
				);
			this->runAction(sequence);
			this->runAction(CCAnimate::create(this->mAllyInfo->animations[ActiveObjTag_MoveRightLeft]));
			mCurStatus = AllyStatus_MovingToTarget;



			//set direction
			// note: there can't just use collisionRect centre point to decide direction.
			// because the center of sprite is not the centre of collisionRect
			auto pos = this->getPosition();
			ccVertex2F toNewPos = vertex2( distPos.x - pos.x, distPos.y - pos.y);
			float z = sqrtf(toNewPos.y * toNewPos.y + toNewPos.x * toNewPos.x);
			float cosF = (float)toNewPos.x / z;
			if(cosF < 0)
				this->setFlipX(true);
			else
				this->setFlipX(false);

		}
	}
	if(mTargetID == -1)
		return;







}

void AllyUnit::startAttack()
{
	auto enemy  = EnemyManager::sharedEnemyManager()->getAvailableEnemy(mTargetID);
	if(enemy == NULL)
	{
		mCurStatus = AllyStatus_Waiting;
		mTargetID = -1;
	}
	else
	{
		// set direction
		if (this->getCollisionRect().getMidX() > enemy->getCollisionRect().getMidX())
		{
			this->setFlipX(true);
			enemy->setFlipX(false);
		}
		else
		{
			this->setFlipX(false);
			enemy->setFlipX(true);
		}
		enemy->startAttack();
		this->attacking();
	}
	//EnemyManager::sharedEnemyManager()->removeEnemy(this->mID);
	// add to EnemyManager's remove queue
	//EnemyManager::sharedEnemyManager()->eraseEnemy(this->mID);

	// remove hp sprite
	//this->mHp->release();
	//this->mHpBatchNode->removeChild(this->mHp, true);
}
void AllyUnit::attacking()
{
	this->stopAllActions();
	mCurStatus = AllyStatus_Attack;
	CCSequence* sequence = CCSequence::createWithTwoActions(
		CCAnimate::create(this->mAllyInfo->animations[ActiveObjTag_Attack])
		,CCCallFunc::create(this, callfunc_selector(AllyUnit::onHit))
		);
	this->runAction(sequence);

}


void AllyUnit::onHit()
{
	auto target = EnemyManager::sharedEnemyManager()->getAvailableEnemy(mTargetID);

	if(target != NULL)
	{
		target->underAttack(mAllyInfo->physicalAttack);
		target = EnemyManager::sharedEnemyManager()->getAvailableEnemy(mTargetID);
	}
	if(target == NULL)
	{
		mCurStatus = AllyStatus_Waiting;
		mTargetID = -1;
		this->setDisplayFrame(mAllyInfo->defaultFrame);
	}
	else
	{
		this->attacking();
	}

}

void AllyUnit::run() 
{   
	mCurStatus = AllyStatus_Waiting;
	this->scheduleUpdate();
}

void AllyUnit::moveTo(const CCPoint& distPos)
{
	mCurStatus = AllyStatus_Moving;
	CCPoint pos = this->getPosition();
	CCSequence* sequence = CCSequence::create(
		CCMoveTo::create(1, distPos ),
		CCCallFunc::create(this, callfunc_selector(AllyUnit::onInPosition)),
		NULL
		);
	this->runAction(sequence);
	this->runAction(CCAnimate::create(this->mAllyInfo->animations[ActiveObjTag_MoveRightLeft]));

	//set direction
	ccVertex2F toNewPos = vertex2( distPos.x - pos.x, distPos.y - pos.y);
	float z = sqrtf(toNewPos.y * toNewPos.y + toNewPos.x * toNewPos.x);
	float cosF = (float)toNewPos.x / z;
	if(cosF < 0)
		this->setFlipX(true);
	else
		this->setFlipX(false);

}

void AllyUnit::onInPosition()
{
	this->stopAllActions();
	mCurStatus = AllyStatus_Waiting;
}

CCRect AllyUnit::getCollisionRect()
{
	//auto colorRect = this->getColorRect();
	CCPoint pos = this->getPosition();
	auto size = this->getContentSize();

	//left_bottom_X = pos.x - size.width / 2
	//left_bottom_Y = pos.y - size.height / 2
	//left_bottom_ColorRect_X = colorRect.origin.x
	//left_bottom_ColorRect_Y = size.height - colorRect.size.height - colorRect.origin.y
	// final_X =  left_bottom_X + left_bottom_ColorRect_X
	// final_Y =  left_bottom_Y + left_bottom_ColorRect_Y

	float x = pos.x - size.width / 2 + mDefualtColorRect.getMinX();
	float y = pos.y + size.height / 2 - mDefualtColorRect.getMaxY();

	//CCRect old(pos.x, pos.y, size.width, size.height);

	//CCLog("colorRect: {{%f, %f}, {%f, %f}}",colorRect.origin.x, colorRect.origin.y, colorRect.size.width, colorRect.size.height);
	//CCLog("collisionRect Old: {{%f, %f}, {%f, %f}}",old.origin.x, old.origin.y, old.size.width, old.size.height);
	//CCLog("collisionRect New: {{%f, %f}, {%f, %f}}",x, y, colorRect.size.width, colorRect.size.height);
	return CCRect(x, y, mDefualtColorRect.size.width, mDefualtColorRect.size.height);
}

void AllyUnit::setHpSpritePosition()
{
	//CCSize enemySize = this->getContentSize();
	//CCPoint pos = this->getPosition();
	CCRect collisionRect = this->getCollisionRect();

	auto newPos = CCPoint(collisionRect.getMinX() + (collisionRect.size.width - mHpBarMaxWidth) / 2, collisionRect.getMaxY() + 2);
	this->mHp->setPosition(newPos);

}

void AllyUnit::updateHpSpriteSize()
{
	//CCAssert(hp >= 0 && hp <= this->mMaxHP, "hp percent value of enemy node is not allow!");
	//this->mCurHP = hp;
	if (this->mCurHP <= 0)
	{
		this->mHp->setVisible(false);
	}
	float precentOfHp = (float)this->mCurHP / (float)this->mAllyInfo->hp;

	//CCSize enemySize = this->getColorRect().size;
	CCSize sizeHp =  this->mHp->getContentSize();

	float scaleX = mHpBarMaxWidth / sizeHp.width * precentOfHp;
	//CCLog("scaleX%f",scaleX);
	//CCLog("Enemy hp: scaleX: %f, scaleY: %f", scaleX, scaleY);
	this->mHp->setScaleX(scaleX);
}

void AllyUnit::underAttack(int damage)
{
	this->mCurHP -= damage;
	this->updateHpSpriteSize();
	if(this->mCurHP <= 0)
	{
		this->destory();
		return;
	}
}

void AllyUnit::destory()
{
	this->unscheduleUpdate();
	this->stopAllActions();
	CCSequence* sequence = CCSequence::createWithTwoActions(
		CCAnimate::create(this->mAllyInfo->animations[ActiveObjTag_Dead])
		,CCCallFunc::create(this, callfunc_selector(AllyUnit::onDestoryed))
		);
	this->runAction(sequence);
	AllyManager::sharedAllyManager()->removeAllyByID(this->mID);

}

void AllyUnit::onDestoryed()
{
	// add to EnemyManager's remove queue
	AllyManager::sharedAllyManager()->eraseAllyByID(this->mID);

	// remove hp sprite
	//this->mHp->release();
	this->mHpBatchNode->removeChild(this->mHp, true);
}

