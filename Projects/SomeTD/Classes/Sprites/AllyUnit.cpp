//
//  Bullet.cpp
//  TileGameDemo
//
//  Created by kelyad on 02-17-2013.
//

#include "AllyUnit.h"
#include "../Managers/EnemyManager.h"
#include "../Managers/AllyManager.h"
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
		enemy->mEntityInfo = enemyInfo;
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
	ActiveEntity::myInit();
	mTargetID = non_entity;
	mTargetSearchInterval = rangedRand(5, 10);
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

} 

void AllyUnit::onEnter()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
	CCSprite::onEnter();
}

void AllyUnit::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCSprite::onExit();
}
bool AllyUnit::findTarget()
{
	ENTITY_ID id = EnemyManager::sharedEnemyManager()->getEnemyInRange(this->getPosition(), mEntityInfo->alertRange);
	if (id == non_entity)
		return false;

	// towerRange check
	if( !EnemyManager::sharedEnemyManager()->isEnemyInRange(mTowerPos, mTowerAlertRange, id))
		return false;
	mTargetID = id;
	return true;
}

bool AllyUnit::targetCheck(ENTITY_ID targetID)
{
	if (EnemyManager::sharedEnemyManager()->isEnemyInRangeAndInTowerRange(this->getPosition(), mEntityInfo->alertRange, mTowerPos, mTowerAlertRange, targetID))
	{
		mTargetID = targetID;
	}
	return false;
}

void AllyUnit::removeAttacker(ENTITY_ID attackerID)
{
	auto iter = mAttackers.find(attackerID);
	if ( iter == mAttackers.end() )
		return;
		//kkAssertMsgf(false, "[AllyUnit::removeAttacker], attacker can't find in map, id: %d", attackerID );
	mAttackers.erase(iter);
}
void AllyUnit::removeTarget()
{
	// it cause iter error remove temporary
	//AllyManager::sharedAllyManager()->sendMsg(MSG_AttackerNoAvailable, mEntityID, mTargetID);
	mTargetID = non_entity;
}

void AllyUnit::enterMoveToTarget()
{
	AllyManager::sharedAllyManager()->sendMsg(MSG_RequestPosition, this->mEntityID, this->mTargetID);
	AllyManager::sharedAllyManager()->sendMsg(MSG_StopMoving, this->mEntityID, this->mTargetID);

	this->runAction(CCAnimate::create(this->mEntityInfo->animations[ActiveObjTag_MoveRightLeft]));
}

bool AllyUnit::onMovingToTarget( float dt )
{
	// let enemy stop running 
	// note: the pos is not the center point of collision rect!
	// 1. get distance color(collision) rect of ally

	//CCRect targetCollisionRect = enemy->getCollisionRect();
	if (!mPreTargetCollisionRect.equals(mTargetCollisionRect) )
	{

		CCRect CollisionRect = this->getCollisionRect();

		CCPoint destColorRectLeftTop;
		if(mTargetCollisionRect.getMidX() > CollisionRect.getMidX())
		{
			// move to left of the target
			destColorRectLeftTop.x = mTargetCollisionRect.getMinX() - mDefualtColorRect.size.width;
		}
		else
		{
			// move to right of the target
			destColorRectLeftTop.x = mTargetCollisionRect.getMaxX();
		}
		destColorRectLeftTop.y = mTargetCollisionRect.getMinY() + mDefualtColorRect.size.height;

		CCPoint destSpriteRectLeftTop = CCPoint(
			destColorRectLeftTop.x - mDefualtColorRect.origin.x,
			destColorRectLeftTop.y + mDefualtColorRect.origin.y
			);
		CCSize size = this->getContentSize();
		mDestinationPos = CCPoint(
			destSpriteRectLeftTop.x + size.width / 2,
			destSpriteRectLeftTop.y - size.height / 2 + rangedRand(0, 5)
			);
	}

	return onMoving(dt, mDestinationPos);
}

bool AllyUnit::onMoving( float dt, const CCPoint& destPos ) 
{
	CCPoint pos = this->getPosition();
	if(abs(pos.x - destPos.x) < 2 && abs(pos.y - destPos.y) < 2 )
	{
		this->setPosition(destPos);
		return true;
	}

	// calculate 'move by' vector
	ccVertex2F toNewTarget = vertex2( destPos.x - pos.x, destPos.y - pos.y );
	ccVertex2F temp = vertex2FNormalization( toNewTarget );
	ccVertex2F toNewPos = vertex2FMul( temp, dt * this->mEntityInfo->speed * 5 );

	CCPoint newPos = CCPoint( pos.x + toNewPos.x, pos.y + toNewPos.y );



	this->setPosition(newPos);
	//auto pos = this->getPosition();
	//ccVertex2F toNewPos = vertex2( mDestinationPos.x - pos.x, mDestinationPos.y - pos.y);
	float z = sqrtf(toNewPos.y * toNewPos.y + toNewPos.x * toNewPos.x);
	float cosF = (float)toNewPos.x / z;
	if( cosF < 0 )
		this->setFlipX( true );
	else
		this->setFlipX( false );
	return false;
}

void AllyUnit::exitMoveToTarget()
{
	this->stopAllActions();	
}

void AllyUnit::frameListener(float dt)
{
	switch (mState)
	{
	case STATE_Idle:
		{
			// not search every frame to improve performance
			if( mTargetSearchInterval-- > 0 )
				break;
			if(this->findTarget())
				AllyManager::sharedAllyManager()->sendMsg(MSG_FoundTarget, mEntityID, mEntityID);
			else
				mTargetSearchInterval = rangedRand(5, 10);
		}
		break;
	case STATE_MovingToTarget:
		{
			// if reach attacking pos, the return value is true.
			if(this->onMovingToTarget(dt))
			{
				// get target location
				//this->changeState(ally, STATE_Attacking);
				AllyManager::sharedAllyManager()->sendMsg(MSG_InAttackPosition, mEntityID, mEntityID);
			}
			// update postion of hp bar
			this->setHpSpritePosition();
		}
		break;
	case STATE_Moving:
		{
			// if reach mass point, the return value is true.
			if(this->onMoving(dt, mMassPos))
			{
				// get target location
				//this->changeState(ally, STATE_Attacking);
				AllyManager::sharedAllyManager()->sendMsg(MSG_InPostion, mEntityID, mEntityID);
			}


			// update postion of hp bar
			this->setHpSpritePosition();

		}
		break;

	default:
		break;
	}
}

void AllyUnit::enterAttacking()
{
	AllyManager::sharedAllyManager()->sendMsg(MSG_InAttackPosition, mEntityID, mTargetID);
	// set direction
	if (this->getCollisionRect().getMidX() > mTargetCollisionRect.getMidX())
	{
		this->setFlipX(true);
	}
	else
	{
		this->setFlipX(false);
	}
	this->attacking();
}

void AllyUnit::attacking()
{
	CCSequence* sequence = CCSequence::createWithTwoActions(
		CCAnimate::create(this->mEntityInfo->animations[ActiveObjTag_Attack])
		,CCCallFunc::create(this, callfunc_selector(AllyUnit::onHitTarget))
		);
	this->runAction(sequence);

}


void AllyUnit::onHitTarget()
{
	this->stopAllActions();
	if(mState != STATE_Attacking)
		return;
	AllyManager::sharedAllyManager()->sendDamageMsg(mEntityID, mTargetID, mEntityInfo->physicalAttack);

	// enemy may be dead after damage!
	// this is important
	if(mState != STATE_Attacking)
		return;
	this->attacking();
}

void AllyUnit::exitAttacing()
{
	// prevent [onHitTarget] execute when attacking animation end!
	
	this->stopAllActions();
	CCLog("[AllyUnit::exitAttacing()]");
	this->setDisplayFrame(mEntityInfo->defaultFrame);
}

void AllyUnit::sendNonAvailableMsg()
{
	//send not avialable msg
	auto allyManager = AllyManager::sharedAllyManager();
	if (mTargetID != non_entity)
	{
		CCLog("Ally send [MSG_AttackerNoAvailable]: attacker: %d, Target: %d", mEntityID, mTargetID);
		allyManager->sendMsg(MSG_AttackerNoAvailable, mEntityID, mTargetID);
	}
	for(auto iter = mAttackers.begin(); iter != mAttackers.end(); ++iter)
	{
		CCLog("Ally send [MSG_TargetNotAvailable]: Target: %d, attacker: %d", mEntityID, iter->first);
		allyManager->sendMsg(MSG_TargetNotAvailable, mEntityID, iter->first);
	}

	auto attacker = mAttackers.find(mTargetID);
	if (attacker != mAttackers.end())
	{
		mAttackers.erase(attacker);
	}
}



void AllyUnit::moveToMassPos()
{
	//need refactor
	this->sendNonAvailableMsg();


	this->moveBackToMassPos();

	CCLog("{AllyUnit::moveToMassPos}");

	// start moving animation
	//this->runAction(CCAnimate::create(this->mEntityInfo->animations[ActiveObjTag_MoveRightLeft]));

}

void AllyUnit::onExitMoving()
{
	this->stopAllActions();
	this->setDisplayFrame(mEntityInfo->defaultFrame);
}

void AllyUnit::underAttack(int damage, ENTITY_ID attackerID, CCRect rect)
{
	mAttackers.insert(std::pair<ENTITY_ID, CCRect>(attackerID, rect));
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
	this->sendNonAvailableMsg();
	this->stopAllActions();
	CCSequence* sequence = CCSequence::createWithTwoActions(
		CCAnimate::create(this->mEntityInfo->animations[ActiveObjTag_Dead])
		,CCCallFunc::create(this, callfunc_selector(AllyUnit::onDestoryed))
		);
	this->runAction(sequence);
	AllyManager::sharedAllyManager()->removeAllyByID(mEntityID);
	//AllyManager::sharedAllyManager()->broadcaseDeadMsg(mEntityID);
}

void AllyUnit::onDestoryed()
{
	// add to EnemyManager's remove queue
	AllyManager::sharedAllyManager()->eraseAllyByID(this->mEntityID);

	// remove hp sprite
	//this->mHp->release();
	this->mHpBatchNode->removeChild(this->mHp, true);
}

