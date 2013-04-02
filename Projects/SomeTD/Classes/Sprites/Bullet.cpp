//
//  Bullet.cpp
//  TileGameDemo
//
//  Created by kelyad on 02-17-2013.
//

#include "Bullet.h"
#include "../Helper/CommonHelpers.h"
#include "../Managers/EnemyManager.h"
using namespace cocos2d;
Bullet* Bullet::create()
{
	Bullet *bullte = new Bullet();

	if (bullte && bullte->init())//±¸×¢1
	{
		bullte->autorelease();
		return bullte;
	}
	CC_SAFE_DELETE(bullte);
	return NULL;

}



void Bullet::reuse(float speed, EnemyUnit* target, CCSpriteFrame* frame)
{
	this->mSpeed = speed;
	this->mTargetID = target->getID();
	this->mTargetPos = target->getPosition();
	this->mTargetCollisionRect = target->getCollisionRect();
	//this->mTargetPos
	this->scheduleUpdate();
	this->setVisible(true);
	this->setDisplayFrame(frame);
}

void Bullet::playHitAnimation()
{
	this->unscheduleUpdate();

	CCSequence* sequence = CCSequence::createWithTwoActions(
		CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName("magebolt_boom")),
		CCCallFunc::create(this, callfunc_selector(Bullet::destory))
		);
	this->runAction(sequence);
}
void Bullet::onMove(CCPoint pos, CCPoint targetPos, float dt)
{
	ccVertex2F toNewTarget = vertex2( targetPos.x - pos.x, targetPos.y - pos.y);
	ccVertex2F temp = vertex2FNormalization(toNewTarget);
	ccVertex2F toNewPos = vertex2FMul(temp, dt * this->mSpeed * 5);

	CCPoint newPos = CCPoint(pos.x + toNewPos.x, pos.y + toNewPos.y);
	this->setPosition(newPos);

	float angleRadians = atanf((float)toNewPos.y / (float)toNewPos.x);
	float angleDegrees = CC_RADIANS_TO_DEGREES(angleRadians);
	float cocosAngle = -1 * angleDegrees + 180;
	this->setRotation(cocosAngle);
}
void Bullet::update(float dt)
{
	if(this->mTargetID == -1)
	{
		if(this->hitChecker())
		{
			this->playHitAnimation();
		}
		else
		{
			this->onMove(this->getPosition(), this->mTargetPos,  dt);
		}
	}
	else
	{
		EnemyUnit* target = EnemyManager::sharedEnemyManager()->getAvailableEnemy(this->mTargetID);
		// if target already dead
		if(target == NULL)
		{
			this->mTargetID = -1;
			if(this->hitChecker())
			{
				this->playHitAnimation();
			}
			else
			{
				this->onMove(this->getPosition(), this->mTargetPos,  dt);
			}
		}
		else
		{
			this->mTargetCollisionRect = target->getCollisionRect();
			this->mTargetPos = target->getPosition();
			if(this->hitChecker())
			{
				target->underAttack(30);
				this->playHitAnimation();
			}
			else
			{
				this->onMove(this->getPosition(), this->mTargetPos,  dt);
			}
		}
	}

	//CCSpriteFrameCache.addSpriteFrame()
	// this->setPosition(ccpAdd(this->getPosition(), ccpMult(mVelocity, dt)));
}
bool Bullet::hitChecker()
{
	//Enemy* target = EnemyManager::sharedEnemyManager()->getAvailableEnemy(this->mTargetID);
	//if(target == NULL)
	//{
	//	CCLog("Bullet::isHit() target non detected! targetID: %d", this->mTargetID);
	//	this->mTargetID = -1;
	//	return true;
	//}
	
	CCRect targetCollisionRect = CCRect(this->mTargetPos.x - 3, mTargetPos.y -3, 6, 6);

	CCPoint pos = this->getPosition();
	CCRect collisionRect  = CCRect(pos.x - 10, pos.y - 10, 20, 20);
	if(!targetCollisionRect.intersectsRect(collisionRect))
		return false;

	//CCLog("Bullet::isHit() hit target !", this->mTargetID);
	return true;
}
void Bullet::destory()
{
	this->setVisible(false);
	//this->release();
}

CCRect Bullet::getCollisionRect()
{
	CCPoint pos = this->getPosition();
	return CCRect(pos.x, pos.y, 6, 6);
}



