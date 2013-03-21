//
//  Bullet.cpp
//  TileGameDemo
//
//  Created by kelyad on 02-17-2013.
//

#include "Enemy.h"
#include "../Managers/EnemyManager.h"
#include "../Helper/CommonHelpers.h"
#include "../Model/TowerInformation.h"
using namespace cocos2d;
Enemy* Enemy::create(const char* pszSpriteFrameName, CCSpriteBatchNode* hpBatchNode)
{
	
	CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pszSpriteFrameName);
	Enemy *enemy = new Enemy();
	if (enemy && enemy->initWithSpriteFrame(pFrame))//备注1
	{
		enemy->mHpBatchNode = hpBatchNode;
		enemy->myInit();
		//tower->loadResource();
		enemy->autorelease();
		//CCLog("Enemy node retainCount:  %d", enemy->retainCount());
		return enemy;
	}
	CC_SAFE_DELETE(enemy);
	return NULL;
}
Enemy::~Enemy()
{
	this->mHpBatchNode->removeChild(this->mHp, true);
}

void Enemy::myInit()
{

	this->mHp = CCSprite::create("hp.png");
	this->mHp->setAnchorPoint(CCPoint(0,0));

	this->mMaxHP = 100;
	this->mCurHP = 100;
	
	this->mHpBatchNode->addChild(this->mHp);
	this->updateHpSpriteSize();
	this->setHpSpritePosition();

	//this->addChild(hpC);

}

bool Enemy::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	bool isTouched = isSpriteTouched(this, touch);
	return isTouched;
}

void Enemy::ccTouchMoved(CCTouch* touch, CCEvent* event)
{

	
}

void Enemy::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	

	//CCLog("%s","精灵33~~~ccTouchEnded");
} 

//---SpriteClassModel 起始结束的生命周期函数----
void Enemy::onEnter()
{
	//注册监听   1.dele类，2.优先级，3.YES为阻碍其他类的move 和 end

	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
	CCSprite::onEnter();
}

void Enemy::onExit()
{
	//移除监听
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCSprite::onExit();
}

void Enemy::update(float dt)
{
	this->setHpSpritePosition();
}




void Enemy::fire(CCSprite* target)
{
	
}

void Enemy::onShoot(CCNode* shooter)
{
	
}

CCRect Enemy::getCollisionRect()
{
	CCPoint pos = this->getPosition();
	auto size = this->getContentSize();
	return CCRect(pos.x, pos.y, size.width * 0.8, size.height * 0.8);
}

void Enemy::setHpSpritePosition()
{
	CCSize enemySize = this->getContentSize();
	CCPoint pos = this->getPosition();
	
	auto newPos = CCPoint(pos.x - enemySize.width / 2, pos.y + enemySize.height / 2 );
	this->mHp->setPosition(newPos);

}
void Enemy::updateHpSpriteSize()
{
	//CCAssert(hp >= 0 && hp <= this->mMaxHP, "hp percent value of enemy node is not allow!");
	//this->mCurHP = hp;
	if (this->mCurHP < 0)
	{
		this->mHp->setVisible(false);
	}
	float precentOfHp = (float)this->mCurHP / (float)this->mMaxHP;

	CCSize enemySize = this->getContentSize();
	CCSize sizeHp =  this->mHp->getContentSize();
	float scaleX = enemySize.width / sizeHp.width * precentOfHp;
	CCLog("scaleX%f",scaleX);
	//CCLog("Enemy hp: scaleX: %f, scaleY: %f", scaleX, scaleY);
	this->mHp->setScaleX(scaleX);
}

void Enemy::underAttack(int damage)
{
	this->mCurHP -= damage;
	this->updateHpSpriteSize();
	if(this->mCurHP < 0)
	{
		this->onDestoryed();
		return;
	}
}

void Enemy::onDestoryed()
{
	EnemyManager::sharedEnemyManager()->removeEnemy(this->mID);
}


void Enemy::FollowPath(CCNode* sender)
{
	//Enemy* temp = (Enemy*)sender;
	static int offset = 1;
	int count = this->mWayPoints.size();
	if (this->_wayPointIndex >= count)
	{
		offset = -1;
		this->_wayPointIndex -= 2;
	}
	if(this->_wayPointIndex < 0)
	{
		this->_wayPointIndex += 2;
		offset= 1;
	}
	CCSequence *sequence = CCSequence::create(
		CCMoveTo::create(1, this->mWayPoints.at(this->_wayPointIndex).pos),
		CCCallFuncN::create(this, callfuncN_selector(Enemy::FollowPath)),
		NULL
		);
	this->_wayPointIndex += offset;
	//this->_player->stopAllActions();
	this->runAction(sequence);

}

void Enemy::run(std::vector<WayPoint>& wayPoints)
{
	this->_wayPointIndex = 0;
	for(auto it = wayPoints.begin(); it != wayPoints.end(); it++)
	{
		WayPoint temp = (*it);
		temp.pos.x = temp.pos.x + (float)rand() / 1000;
		temp.pos.y = temp.pos.y + (float)rand() / 500;
		this->mWayPoints.push_back(temp);
	}

	this->runAction(CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName("yeti_move")));

	CCSequence *sequence = CCSequence::create( 
		CCMoveTo::create(1, this->mWayPoints.at(this->_wayPointIndex++).pos),
		CCCallFuncN::create(this, callfuncN_selector(Enemy::FollowPath)), 
		NULL
		);

	this->runAction(sequence);
	this->scheduleUpdate();
}
void Enemy::run(std::vector<WayPoint>& wayPoints, float duration, float tension) 
{   
	// not like vector<T>, 
	// capacity of CCPointArray::create() is no use for now
	auto pointArray = CCPointArray::create(wayPoints.size());

	for(auto it = wayPoints.begin(); it != wayPoints.end(); ++it)
	{
		CCPoint temp = (*it).pos;
		//temp.x = temp.x + (float)rand() / 1000;
		//temp.y = temp.y + (float)rand() / 500;
		pointArray->addControlPoint(temp);
	}
	this->runAction(CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName("yeti_move")));
	this->runAction(CCCardinalSplineTo::create(duration, pointArray, tension));
	this->scheduleUpdate();
}