//
//  Bullet.cpp
//  TileGameDemo
//
//  Created by kelyad on 02-17-2013.
//

#include "EnemyManager.h"
#include "../Helper/CommonHelpers.h"
#include "../Helper/SpriteHelpers.h"
using namespace cocos2d;

EnemyManager::EnemyManager()
{
	mEnemyLayer = NULL;
	this->mBatch = NULL;
}


EnemyManager* EnemyManager::mInstance = NULL;
EnemyManager* EnemyManager::sharedEnemyManager()
{
	if (EnemyManager::mInstance == NULL)
		EnemyManager::mInstance = new EnemyManager();
	return EnemyManager::mInstance;
}

void EnemyManager::setEnemyLayer(CCNode* layer)
{
	this->mEnemyLayer = layer;
}

Enemy* EnemyManager::getEnemyInRange(CCPoint& pos, int rangeRadius)
{

	for(auto it = this->mEnemies.begin();it != this->mEnemies.end(); ++it)
	{
		if (isRectAndCircleCollided(pos, rangeRadius, (*it)->getCollisionRect()))
		{
			CCPoint targetPos = (*it)->getPosition();
			CCSize targetSize = (*it)->getContentSize();

			CCLog("New target in range.");
			CCLog("target: pos(%f, %f), width: %f, height: %f", targetPos.x, targetPos.y, targetSize.width, targetSize.height);
			CCLog("tower: pos(%f, %f)", pos.x, pos.y );
			return (*it);
		}
	}
	return NULL;
}

bool EnemyManager::isEnemyInRange(CCPoint& pos, int rangeRadius, Enemy* enemy)
{
	if (isRectAndCircleCollided(pos, rangeRadius, enemy->getCollisionRect()))
		return true;
	CCPoint targetPos = enemy->getPosition();
	CCSize targetSize = enemy->getContentSize();
	CCLog("\ntarget out of range.");
	CCLog("target: pos(%f, %f), width: %f, height: %f", targetPos.x, targetPos.y, targetSize.width, targetSize.height);
	CCLog("tower: pos(%f, %f)", pos.x, pos.y );
	isRectAndCircleCollided(pos, rangeRadius, enemy->getCollisionRect());
	return false;
}



void EnemyManager::addEnemy(Enemy* enemy)
{
	if(this->mBatch == NULL)
	{
		this->mBatch = CCSpriteBatchNode::create("yeti.png");
		this->mEnemyLayer->addChild(this->mBatch);
	}
	this->mBatch->addChild(enemy);
	enemy->retain();
	this->mEnemies.push_back(enemy);
}

void EnemyManager::runEnemiseOneByOne(float dt)
{
	for(auto it = this->mEnemies.begin();it != this->mEnemies.end(); ++it)
	{
		(*it)->run(this->mWayPoints, 10, 0);
	}
}

void EnemyManager::readWayPoints(CCTMXObjectGroup* objects)
{


	//WayPoints
	//this->_wayPoints = new std::vector<WayPoint>();
	//this->_wayPointIndex = 0;
	int index = 0;
	char name[] = "WayPoint00";
	while (true)
	{
		index++;
		if(index < 10)
		{
			name[9] = (char)(index + 48);
		}
		else
		{
			name[8] = (char) (index / 10) + 48;
			name[9] = (char) (index % 10) + 48;
		}
		CCDictionary *temp = objects->objectNamed(name);
		if (temp == NULL) 
			break;
		int x = temp->valueForKey("x")->intValue();
		int y = temp->valueForKey("y")->intValue();
		this->mWayPoints.push_back(IDS_Create_WayPoint(x, y));

	}

}