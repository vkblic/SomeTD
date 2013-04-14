//
//  Bullet.cpp
//  TileGameDemo
//
//  Created by kelyad on 02-17-2013.
//

#include "EnemyUnit.h"
#include "../Managers/EnemyManager.h"
#include "../Managers/AllyManager.h"
#include "../Helper/CommonHelpers.h"
#include <math.h>
using namespace cocos2d;
EnemyUnit* EnemyUnit::create(ActiveObjModel* enemyInfo, CCSpriteBatchNode* hpBatchNode)
{

	//CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pszSpriteFrameName);
	EnemyUnit *enemy = new EnemyUnit();
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
EnemyUnit::~EnemyUnit()
{
}

void EnemyUnit::myInit()
{

	mCurWayPointIndex = 0;
	ActiveEntity::myInit();

	//mHp = CCSprite::create("hp.png");
	//mDefualtColorRect = this->getColorRect();
	//mCurHP = this->mEnemyInfo->hp;
	//mHp->setAnchorPoint(CCPoint(0,0));
	//mHpBatchNode->addChild(this->mHp);
	//mHpBarMaxWidth = mDefualtColorRect.size.width > HP_BAR_WIDTH ? HP_BAR_WIDTH : mDefualtColorRect.size.width * 0.8;
	//this->updateHpSpriteSize();
	//this->setHpSpritePosition();
	//this->addChild(hpC);

}

bool EnemyUnit::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	return false;
}

void EnemyUnit::ccTouchMoved(CCTouch* touch, CCEvent* event)
{


}

void EnemyUnit::ccTouchEnded(CCTouch* touch, CCEvent* event)
{


	//CCLog("%s","精灵33~~~ccTouchEnded");
} 

//---SpriteClassModel 起始结束的生命周期函数----
void EnemyUnit::onEnter()
{
	//注册监听   1.dele类，2.优先级，3.YES为阻碍其他类的move 和 end

	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
	CCSprite::onEnter();
}

void EnemyUnit::onExit()
{
	//移除监听
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCSprite::onExit();
}


/*void updatebak(float dt)
{
if(mCurStatus == EnemyStatus_WaitingForAttack || mCurStatus == EnemyStatus_Attacking)
{
if( mCurEnemyTag != ActiveObjTag_Stoped && mCurEnemyTag != ActiveObjTag_Attack)
{
mCurEnemyTag = ActiveObjTag_Stoped;
this->stopAllActions();
}
return;
}
CCPoint targetPos = mWayPoints->at(mCurWayPointIndex).pos;
CCPoint pos = this->getPosition();
ccVertex2F toNewTarget = vertex2( targetPos.x - pos.x, targetPos.y - pos.y);
ccVertex2F temp = vertex2FNormalization(toNewTarget);
ccVertex2F toNewPos = vertex2FMul(temp, dt * mEntityInfo->speed);

CCPoint newPos = CCPoint(pos.x + toNewPos.x, pos.y + toNewPos.y);
this->setPosition(newPos);

//float angleRadians = asinf((float)toNewPos.y / sqrtf(toNewPos.y * toNewPos.y + toNewPos.x * toNewPos.x));
float z = sqrtf(toNewPos.y * toNewPos.y + toNewPos.x * toNewPos.x);
float sinF = (float)toNewPos.y / z ;
float sin1_2Pi = sqrt(2) / 2;

this->setFlipX(false);
if(sinF > sin1_2Pi  )
{
//this->stopAllActions();
if (mCurEnemyTag != ActiveObjTag_MoveUp)
{
this->stopAllActions();
this->runAction(CCAnimate::create(this->mEntityInfo->animations[ActiveObjTag_MoveUp]));
//CCLog("EnmeyTag_MoveUp");
//CCLog("%f",sinF);
mCurEnemyTag = ActiveObjTag_MoveUp;
}
}
else if(sinF >= -1 && sinF < -0.8)
{
if (mCurEnemyTag != ActiveObjTag_MoveDown)
{
this->stopAllActions();
this->runAction(CCAnimate::create(this->mEntityInfo->animations[ActiveObjTag_MoveDown]));
//CCLog("EnmeyTag_MoveDown");
//CCLog("%f",sinF);
mCurEnemyTag = ActiveObjTag_MoveDown;
}
}
else
{
float cosF = (float)toNewPos.x / z;
//CCLog("cos: %f sin: %f",cosF, sinF);
if(cosF < 0)
{
this->setFlipX(true);
//CCLog("EnmeyTag_MoveLeft");
}
else
{

//CCLog("EnmeyTag_MoveRight");
}
if (mCurEnemyTag != ActiveObjTag_MoveRightLeft)
{
this->stopAllActions();
this->runAction(CCAnimate::create(this->mEntityInfo->animations[ActiveObjTag_MoveRightLeft]));
mCurEnemyTag = ActiveObjTag_MoveRightLeft;

}
//float aCosF = acosf((float)toNewPos.x / sqrtf(toNewPos.y * toNewPos.y + toNewPos.x * toNewPos.x));

}

//float angleDegrees = CC_RADIANS_TO_DEGREES(angleRadians);
//float cocosAngle = -1 * angleDegrees;
//
//static float t = 0;
//if(t > 1)
//{
//	CCLog("%f", angleRadians);
//	CCLog("%f", angleDegrees);
//	t = 0;
//}
//else
//{
//	t += dt;
//}
//
//this->setRotation(cocosAngle);



if (abs(targetPos.x - newPos.x) < 2 && abs(targetPos.y - newPos.y) < 2 )
{
++mCurWayPointIndex;
if(mCurWayPointIndex == mWayPoints->size())
{
this->onArriveEndPoint();
return;
}
}
// update postion of hp bar
this->setHpSpritePosition();


}*/


void EnemyUnit::frameListener(float dt)
{

	switch (mState)
	{
	case STATE_Moving:
		{
			// if reach end point, the return value is true.
			if(this->movingUpdate(dt))
				return;

			// send location info
			this->sendMovingmsg();

			// update postion of hp bar
			this->setHpSpritePosition();
		}
		break;

	default:
		break;
	}

}

void EnemyUnit::run(const std::vector<WayPointEx>* wayPoints) 
{   
	// not like vector<T>, 
	// capacity of CCPointArray::create() is no use for now
	auto pointArray = CCPointArray::create(wayPoints->size());
	//this->setFlipX(true);
	mWayPoints = wayPoints;
	for(auto it = wayPoints->begin(); it != wayPoints->end(); ++it)
	{
		CCPoint temp = (*it).pos;
		//temp.x = temp.x + (float)rand() / 1000;
		//temp.y = temp.y + (float)rand() / 500;
		pointArray->addControlPoint(temp);
	}
	mCurEnemyTag = ActiveObjTag_Default;
	this->runAction(CCAnimate::create(this->mEntityInfo->animations[ActiveObjTag_Default]));
	//CCSequence* sequence = CCSequence::createWithTwoActions(
	//	CCCardinalSplineTo::create(mEnemyInfo->speed, pointArray, 0)
	//	,CCCallFunc::create(this, callfunc_selector(Enemy::onArriveEndPoint))
	//	);
	//this->runAction(sequence);
	mState = STATE_Moving;
}

void EnemyUnit::enterAttacking()
{
	//temporary deal with the situation: when no attacking hit before dead, dead msg to target send fail.
	AllyManager::sharedAllyManager()->sendDamageMsg(this->mEntityID, this->mTargetID, 0);
	// set direction
	if (this->getCollisionRect().getMidX() > mTargetCollisionRect.getMidX())
	{
		this->setFlipX(true);
	}
	else
	{
		this->setFlipX(false);
	}
	this->onAttacking();
}

void EnemyUnit::onAttacking()
{
	CCSequence* sequence = CCSequence::createWithTwoActions(
		CCAnimate::create(this->mEntityInfo->animations[ActiveObjTag_Attack])
		,CCCallFunc::create(this, callfunc_selector(EnemyUnit::onHitTarget))
		);
	this->runAction(sequence);

}

void EnemyUnit::onHitTarget()
{
	AllyManager::sharedAllyManager()->sendDamageMsg(this->mEntityID, this->mTargetID, this->mEntityInfo->physicalAttack);
	if(mState != STATE_Attacking)
		return;
	this->onAttacking();
}

void EnemyUnit::exitAttacing()
{
	this->setDisplayFrame(mEntityInfo->defaultFrame);
}

// move
void EnemyUnit::enterMoving()
{
	mCurEnemyTag = ActiveObjTag_Stoped;
	
}

void EnemyUnit::exitMoving()
{
	this->stopAllActions();
	this->setDisplayFrame(mEntityInfo->defaultFrame);
}

bool EnemyUnit::movingUpdate(float dt)
{
	CCPoint targetPos = mWayPoints->at(mCurWayPointIndex).pos;
	CCPoint pos = this->getPosition();
	ccVertex2F toNewTarget = vertex2( targetPos.x - pos.x, targetPos.y - pos.y);
	ccVertex2F temp = vertex2FNormalization(toNewTarget);
	ccVertex2F toNewPos = vertex2FMul(temp, dt * mEntityInfo->speed);

	CCPoint newPos = CCPoint(pos.x + toNewPos.x, pos.y + toNewPos.y);
	this->setPosition(newPos);

	if (abs(targetPos.x - newPos.x) < 2 && abs(targetPos.y - newPos.y) < 2 )
	{
		++mCurWayPointIndex;
		if(mCurWayPointIndex == mWayPoints->size())
		{
			EnemyManager::sharedEnemyManager()->sendDelayedMsg(MSG_ArriveEndPoint, 1, mEntityID, mEntityID);
			//this->onArriveEndPoint();
			return true;
		}
	}

	// change animation when direction changed
	float z = sqrtf(toNewPos.y * toNewPos.y + toNewPos.x * toNewPos.x);
	float sinF = (float)toNewPos.y / z ;
	float sin1_2Pi = sqrt(2) / 2;

	this->setFlipX(false);
	if(sinF > sin1_2Pi  )
	{
		if (mCurEnemyTag != ActiveObjTag_MoveUp)
		{
			this->stopAllActions();
			this->runAction(CCAnimate::create(this->mEntityInfo->animations[ActiveObjTag_MoveUp]));
			//CCLog("EnmeyTag_MoveUp");
			//CCLog("%f",sinF);
			mCurEnemyTag = ActiveObjTag_MoveUp;
		}
	}
	else if(sinF >= -1 && sinF < -0.8)
	{
		if (mCurEnemyTag != ActiveObjTag_MoveDown)
		{
			this->stopAllActions();
			this->runAction(CCAnimate::create(this->mEntityInfo->animations[ActiveObjTag_MoveDown]));
			//CCLog("EnmeyTag_MoveDown");
			//CCLog("%f",sinF);
			mCurEnemyTag = ActiveObjTag_MoveDown;
		}
	}
	else
	{
		float cosF = (float)toNewPos.x / z;
		//CCLog("cos: %f sin: %f",cosF, sinF);
		this->setFlipX(cosF < 0 ? true : false);
		//CCLog(cosF < 0 ? "EnmeyTag_MoveLeft" : "EnmeyTag_MoveRight");
		if (mCurEnemyTag != ActiveObjTag_MoveRightLeft)
		{
			this->stopAllActions();
			this->runAction(CCAnimate::create(this->mEntityInfo->animations[ActiveObjTag_MoveRightLeft]));
			mCurEnemyTag = ActiveObjTag_MoveRightLeft;

		}
	}

	return false;
}

void EnemyUnit::sendMovingmsg()
{
	for(auto iter = mAttackers.begin(); iter != mAttackers.end(); ++iter)
	{
		EnemyManager::sharedEnemyManager()->sendCollisionRecMsg(mEntityID, iter->first, this->getCollisionRect());
	}
}


bool EnemyUnit::isTargetNoAvailable(entity_id attackerId)
{
	if (mTargetID == attackerId)
		return true;
	return false;
}

void EnemyUnit::removeAttacker(entity_id attackerID)
{
	auto iter = mAttackers.find(attackerID);
	if ( iter == mAttackers.end() )
		kkAssertMsgf(false, "[EnemyUnit::removeAttacker], attacker can't find in map, id: %d", attackerID );
	mAttackers.erase(iter);
}

void EnemyUnit::addAttacker(entity_id attackerID, CCRect rect)
{
	CCLog("[ EnemyUnit::addAttacker]: attacker: %d before: %d", attackerID, mAttackers.size());
	mAttackers.insert(std::pair<entity_id, CCRect>(attackerID, rect));
	CCLog("[ EnemyUnit::addAttacker]: attacker: %d after: %d", attackerID, mAttackers.size());
}



void EnemyUnit::underAttack(int damage, entity_id attackerID, CCRect rect)
{
	addAttacker(attackerID, rect);
	this->underAttack(damage);
}
void EnemyUnit::underAttack(int damage)
{
	this->mCurHP -= damage;
	this->updateHpSpriteSize();
	if(this->mCurHP <= 0)
	{
		this->destory();
		return;
	}
}



void EnemyUnit::destory()
{
	this->unscheduleUpdate();
	this->stopAllActions();
	CCSequence* sequence = CCSequence::createWithTwoActions(
		CCAnimate::create(this->mEntityInfo->animations[ActiveObjTag_Dead])
		,CCCallFunc::create(this, callfunc_selector(EnemyUnit::onDestoryed))
		);
	this->runAction(sequence);
	EnemyManager::sharedEnemyManager()->removeEnemy(this->mEntityID);
	this->sendDeadMsg();

}

void EnemyUnit::sendDeadMsg()
{
	//send not avialable msg
	auto enemyManager = EnemyManager::sharedEnemyManager();
	enemyManager->sendMsg(MSG_AttackerNoAvailable, mEntityID, mTargetID);

	CCLog("attackerCount: %d", mAttackers.size());
	for(auto iter = mAttackers.begin(); iter != mAttackers.end(); ++iter)
	{
		CCLog("Target: %d, attacker: %d", mEntityID, iter->first);
		enemyManager->sendMsg(MSG_TargetNotAvailable, mEntityID, iter->first);
	}

}

void EnemyUnit::onDestoryed()
{
	// add to EnemyManager's remove queue
	EnemyManager::sharedEnemyManager()->eraseEnemy(this->mEntityID);

	// remove hp sprite
	//this->mHp->release();
	this->mHpBatchNode->removeChild(this->mHp, true);
}
void EnemyUnit::onArriveEndPoint()
{
	//this->unscheduleUpdate();
	this->stopAllActions();
	EnemyManager::sharedEnemyManager()->removeEnemy(this->mEntityID);
	// add to EnemyManager's remove queue
	EnemyManager::sharedEnemyManager()->eraseEnemy(this->mEntityID);
	//sendDeadMsg();
	// remove hp sprite
	//this->mHp->release();
	this->mHpBatchNode->removeChild(this->mHp, true);
}

