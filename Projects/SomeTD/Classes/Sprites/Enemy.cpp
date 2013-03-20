//
//  Bullet.cpp
//  TileGameDemo
//
//  Created by kelyad on 02-17-2013.
//

#include "Enemy.h"
#include "../Helper/CommonHelpers.h"
#include "../Model/TowerInformation.h"
using namespace cocos2d;
Enemy* Enemy::create(const char* pszSpriteFrameName)
{
	
	CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pszSpriteFrameName);
	Enemy *enemy = new Enemy();
	if (enemy && enemy->initWithSpriteFrame(pFrame))//备注1
	{
		//tower->loadResource();
		enemy->autorelease();
		CCLog("Enemy: %d", enemy->retainCount());
		return enemy;
	}
	CC_SAFE_DELETE(enemy);
	return NULL;

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

void Enemy::loadResource(eTower_Terrain terrain)
{
	
}


void Enemy::update(float dt)
{
	
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
}