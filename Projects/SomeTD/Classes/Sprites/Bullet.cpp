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
		//bullte->myInit(speed, targetID);
		bullte->autorelease();
		//CCLog("Bullet::create: %d", bullte->retainCount());
		return bullte;
	}
	CC_SAFE_DELETE(bullte);
	return NULL;

}

void Bullet::myInit(float speed, unsigned long targetID)
{
// 	this->mSpeed = speed;
// 	this->mTargetID = targetID;
// 	Enemy* target = EnemyManager::sharedEnemyManager()->getAvailableEnemy(targetID);
// 	
// 	if(target == NULL)
// 	{
// 		this->mTargetID = -1;
// 		return;
// 	}
// 	CCLog("Bullet::myInit() new target: %d", this->mTargetID);
}

void Bullet::reuse(float speed,unsigned long targetID, CCSpriteFrame* frame)
{
	this->mSpeed = speed;
	this->mTargetID = targetID;
	//this->mTargetPos
	this->scheduleUpdate();
	this->setVisible(true);
	this->setDisplayFrame(frame);
}



void Bullet::update(float dt)
{
	//if ()
	//{
	//	this->unscheduleUpdate();
	//	this->release();
	//}
	//CCPoint pos = this->getPosition();
	//pos.y -= this->mBulletInfo->BulletSpeed * dt;
	//this->setPositionY(pos.y);
	if(this->mTargetID == -1 || this->isHit())
	{
		this->unscheduleUpdate();
		//this->destory();
		CCLog("Bullet::update() hit", this->mTargetID);

		CCSequence* sequence = CCSequence::createWithTwoActions(
			CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName("magebolt_boom")),
			CCCallFunc::create(this, callfunc_selector(Bullet::destory))
			);
		this->runAction(sequence);
	}
	else
	{
		//CCLog("Bullet::update() moving!", this->_target);
		Enemy* target = EnemyManager::sharedEnemyManager()->getAvailableEnemy(this->mTargetID);
		if(target == NULL)
		{
			this->mTargetID = -1;
			return;
		}


		CCPoint pos = this->getPosition();
		CCPoint targetPosNew = target->getPosition();
		//ccVertex2F toOldTarget = vertex2( this->_targetLastPosition.x - pos.x, this->_targetLastPosition.y - pos.y );

		ccVertex2F toNewTarget = vertex2( targetPosNew.x - pos.x, targetPosNew.y - pos.y);
		ccVertex2F temp = vertex2FNormalization(toNewTarget);
		ccVertex2F toNewPos = vertex2FMul(temp, dt * this->mSpeed * 5);

		//sprintf_s(temp,255, "%-08.4f",dt);
		//CCLog(temp);
		CCPoint newPos = CCPoint(pos.x + toNewPos.x, pos.y + toNewPos.y);
		this->setPosition(newPos);

		float angleRadians = atanf((float)toNewPos.y / (float)toNewPos.x);
		float angleDegrees = CC_RADIANS_TO_DEGREES(angleRadians);
		float cocosAngle = -1 * angleDegrees + 180;
		this->setRotation(cocosAngle);

	}
	//CCSpriteFrameCache.addSpriteFrame()
	// this->setPosition(ccpAdd(this->getPosition(), ccpMult(mVelocity, dt)));
}
bool Bullet::isHit()
{
	Enemy* target = EnemyManager::sharedEnemyManager()->getAvailableEnemy(this->mTargetID);
	if(target == NULL)
	{
		CCLog("Bullet::isHit() target non detected! targetID: %d", this->mTargetID);
		this->mTargetID = -1;
		return true;
	}
	CCPoint targetPos = target->getPosition();
	CCRect targetCollisionRect = CCRect(targetPos.x - 3, targetPos.y -3, 6, 6);

	CCPoint pos = this->getPosition();
	CCRect collisionRect  = CCRect(pos.x - 3, pos.y - 3, 6, 6);
	if(!targetCollisionRect.intersectsRect(collisionRect))
		return false;
	target->underAttack(10);

	CCLog("Bullet::isHit() hit target !", this->mTargetID);
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



