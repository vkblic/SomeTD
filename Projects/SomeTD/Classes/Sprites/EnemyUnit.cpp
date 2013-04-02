//
//  Bullet.cpp
//  TileGameDemo
//
//  Created by kelyad on 02-17-2013.
//

#include "EnemyUnit.h"
#include "../Managers/EnemyManager.h"
#include "../Managers/AlliesManager.h"
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
		enemy->mEnemyInfo = enemyInfo;
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

	mHp = CCSprite::create("hp.png");
	mCurWayPointIndex = 0;
	mDefualtColorRect = this->getColorRect();
	mCurHP = this->mEnemyInfo->hp;
	mHp->setAnchorPoint(CCPoint(0,0));
	mHpBatchNode->addChild(this->mHp);
	mHpBarMaxWidth = mDefualtColorRect.size.width > HP_BAR_WIDTH ? HP_BAR_WIDTH : mDefualtColorRect.size.width * 0.8;
	this->updateHpSpriteSize();
	this->setHpSpritePosition();
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

static CCPoint ccCardinalSplineAt(CCPoint &p0, CCPoint &p1, CCPoint &p2, CCPoint &p3, float tension, float t)
{
	float t2 = t * t;
	float t3 = t2 * t;

	/*
	* Formula: s(-ttt + 2tt - t)P1 + s(-ttt + tt)P2 + (2ttt - 3tt + 1)P2 + s(ttt - 2tt + t)P3 + (-2ttt + 3tt)P3 + s(ttt - tt)P4
	*/
	float s = (1 - tension) / 2;

	float b1 = s * ((-t3 + (2 * t2)) - t);                      // s(-t3 + 2 t2 - t)P1
	float b2 = s * (-t3 + t2) + (2 * t3 - 3 * t2 + 1);          // s(-t3 + t2)P2 + (2 t3 - 3 t2 + 1)P2
	float b3 = s * (t3 - 2 * t2 + t) + (-2 * t3 + 3 * t2);      // s(t3 - 2 t2 + t)P3 + (-2 t3 + 3 t2)P3
	float b4 = s * (t3 - t2);                                   // s(t3 - t2)P4

	float x = (p0.x*b1 + p1.x*b2 + p2.x*b3 + p3.x*b4);
	float y = (p0.y*b1 + p1.y*b2 + p2.y*b3 + p3.y*b4);

	return ccp(x,y);
}

void EnemyUnit::update(float dt)
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
	ccVertex2F toNewPos = vertex2FMul(temp, dt * mEnemyInfo->speed);

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
			this->runAction(CCAnimate::create(this->mEnemyInfo->animations[ActiveObjTag_MoveUp]));
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
			this->runAction(CCAnimate::create(this->mEnemyInfo->animations[ActiveObjTag_MoveDown]));
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
			this->runAction(CCAnimate::create(this->mEnemyInfo->animations[ActiveObjTag_MoveRightLeft]));
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


}

CCPoint EnemyUnit::getControlPointAt(int index)
{
	//index = MIN(mWayPoints->size() - 1, MAX(index, 0));
	//return mWayPoints[index];
	return CCPoint();
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
	this->runAction(CCAnimate::create(this->mEnemyInfo->animations[ActiveObjTag_Default]));
	//CCSequence* sequence = CCSequence::createWithTwoActions(
	//	CCCardinalSplineTo::create(mEnemyInfo->speed, pointArray, 0)
	//	,CCCallFunc::create(this, callfunc_selector(Enemy::onArriveEndPoint))
	//	);
	//this->runAction(sequence);
	this->scheduleUpdate();
	mCurStatus = EnemyStatus_Moving;
}

void EnemyUnit::startAttack()
{

	//CCLog("EnemyUnit::startAttack()");
	mCurEnemyTag = ActiveObjTag_Attack;
	mCurStatus = EnemyStatus_Attacking;

	auto target  = AllyManager::sharedAllyManager()->getAvailableObject(mTargetID);
	if(target == NULL)
	{
		mCurStatus = EnemyStatus_Moving;
		mCurEnemyTag = ActiveObjTag_Stoped;
		mTargetID = -1;
	}
	else
	{
		this->attacking();
	}
}

void EnemyUnit::attacking()
{
	CCSequence* sequence = CCSequence::createWithTwoActions(
		CCAnimate::create(this->mEnemyInfo->animations[ActiveObjTag_Attack]),
		CCCallFunc::create(this, callfunc_selector(EnemyUnit::onHit))
		);

	this->runAction(sequence);
}


void EnemyUnit::onHit()
{
	//CCLog("EnemyUnit::onHit()");
	auto allyManager = AllyManager::sharedAllyManager();
	auto target = allyManager->getAvailableObject(mTargetID);
	if(target != NULL)
	{
		target->underAttack(mEnemyInfo->physicalAttack);
		target = allyManager->getAvailableObject(mTargetID);
	}
	if(target == NULL)
	{
		mCurEnemyTag = ActiveObjTag_Stoped;
		mCurStatus = EnemyStatus_Moving;
		mTargetID = -1;
	}
	else
	{
		this->startAttack();
	}
}

CCRect EnemyUnit::getCollisionRect()
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

void EnemyUnit::setHpSpritePosition()
{
	//CCSize enemySize = this->getContentSize();
	//CCPoint pos = this->getPosition();
	CCRect collisionRect = this->getCollisionRect();

	auto newPos = CCPoint(collisionRect.getMinX() + (collisionRect.size.width - mHpBarMaxWidth) / 2, collisionRect.getMaxY() + 2);
	this->mHp->setPosition(newPos);

}
void EnemyUnit::updateHpSpriteSize()
{
	//CCAssert(hp >= 0 && hp <= this->mMaxHP, "hp percent value of enemy node is not allow!");
	//this->mCurHP = hp;
	if (this->mCurHP <= 0)
	{
		this->mHp->setVisible(false);
	}
	float precentOfHp = (float)this->mCurHP / (float)this->mEnemyInfo->hp;

	//CCSize enemySize = this->getColorRect().size;
	CCSize sizeHp =  this->mHp->getContentSize();

	float scaleX = mHpBarMaxWidth / sizeHp.width * precentOfHp;
	//CCLog("scaleX%f",scaleX);
	//CCLog("Enemy hp: scaleX: %f, scaleY: %f", scaleX, scaleY);
	this->mHp->setScaleX(scaleX);
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
		CCAnimate::create(this->mEnemyInfo->animations[ActiveObjTag_Dead])
		,CCCallFunc::create(this, callfunc_selector(EnemyUnit::onDestoryed))
		);
	this->runAction(sequence);
	EnemyManager::sharedEnemyManager()->removeEnemy(this->mID);

}
void EnemyUnit::onDestoryed()
{
	// add to EnemyManager's remove queue
	EnemyManager::sharedEnemyManager()->eraseEnemy(this->mID);

	// remove hp sprite
	//this->mHp->release();
	this->mHpBatchNode->removeChild(this->mHp, true);
}
void EnemyUnit::onArriveEndPoint()
{
	this->unscheduleUpdate();
	this->stopAllActions();
	EnemyManager::sharedEnemyManager()->removeEnemy(this->mID);
	// add to EnemyManager's remove queue
	EnemyManager::sharedEnemyManager()->eraseEnemy(this->mID);

	// remove hp sprite
	//this->mHp->release();
	this->mHpBatchNode->removeChild(this->mHp, true);
}

