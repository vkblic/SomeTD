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
	this->mEnemyLayer = NULL;
	this->mHpBatchNode = NULL;
	this->mBatch = NULL;
	this->mIDSeed = 0;
}
EnemyManager::~EnemyManager()
{
	for(auto it = this->mEnemies.begin(); it != this->mEnemies.end(); ++it)
	{
		it->second->release();
		this->mBatch->removeChild(it->second, true);
		CCLog("EnemyManager::clearUnusedEnemise: retainCount: %d", it->second->retainCount());
	}
	this->mEnemies.clear();
	this->mEnemyLayer->release();
	this->mBatch->release();
	this->mHpBatchNode->release();
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

#pragma region Range checker

unsigned long EnemyManager::getEnemyInRange(CCPoint& pos, int rangeRadius)
{

	for(auto it = this->mEnemies.begin();it != this->mEnemies.end(); ++it)
	{
		if (isRectAndCircleCollided(pos, rangeRadius, it->second->getCollisionRect()))
		{
			CCPoint targetPos = it->second->getPosition();
			CCSize targetSize = it->second->getContentSize();

			CCLog("New target in range.");
			CCLog("target: pos(%f, %f), width: %f, height: %f", targetPos.x, targetPos.y, targetSize.width, targetSize.height);
			CCLog("tower: pos(%f, %f)", pos.x, pos.y );
			return it->first;
		}
	}
	return -1;
}

bool EnemyManager::isEnemyInRange(CCPoint& pos, int rangeRadius, unsigned long enemyID)
{
	auto it = this->mEnemies.find(enemyID);
	if (it == this->mEnemies.end())
		return false;

	if (isRectAndCircleCollided(pos, rangeRadius, it->second->getCollisionRect()))
		return true;
	CCPoint targetPos = it->second->getPosition();
	CCSize targetSize = it->second->getContentSize();
	CCLog("\ntarget out of range.");
	CCLog("target: pos(%f, %f), width: %f, height: %f", targetPos.x, targetPos.y, targetSize.width, targetSize.height);
	CCLog("tower: pos(%f, %f)", pos.x, pos.y );
	isRectAndCircleCollided(pos, rangeRadius, it->second->getCollisionRect());
	return false;
}

#pragma endregion


#pragma region enemy node

unsigned long EnemyManager::addEnemy(const char* plFrameName)
{
	if(this->mBatch == NULL)
	{
		this->mBatch = CCSpriteBatchNode::create("yeti.png");
		this->mEnemyLayer->addChild(this->mBatch);
	}
	if(this->mHpBatchNode == NULL)
	{
		this->mHpBatchNode = CCSpriteBatchNode::create("hp.png");
		this->mEnemyLayer->addChild(this->mHpBatchNode);
	}
	auto enemy = Enemy::create(plFrameName, this->mHpBatchNode);
	this->mBatch->addChild(enemy);
	CCLog("EnemyManager::addEnemy: retainCount: %d", enemy->retainCount());
	auto pair = std::pair<unsigned long, Enemy*>(this->mIDSeed, enemy);
	enemy->setID(this->mIDSeed++);
	this->mEnemies.insert(pair);
	return enemy->getID();
}

void EnemyManager::removeEnemy(unsigned long enemyID)
{
	auto it = this->mEnemies.find(enemyID);
	if(it == this->mEnemies.end())
		CCAssert(false, "must find id in map! there must be some error some where!");
	this->mUnusedEnemy.push_back(it->second);
	this->mEnemies.erase(it);
}

void EnemyManager::clearUnusedEnemise()
{
	for(auto it = this->mUnusedEnemy.begin(); it != this->mUnusedEnemy.end(); ++it)
	{
		auto node = (*it);
		node->release();
		//CCLog("EnemyManager::clearUnusedEnemise: retainCount: %d", node->retainCount());
		this->mBatch->removeChild(node, true);
	}
	this->mUnusedEnemy.clear();
}

Enemy* EnemyManager::getAvailableEnemy(unsigned long enemyID)
{
	auto it = this->mEnemies.find(enemyID);
	if (it == this->mEnemies.end())
		return NULL;
	return it->second;
}

#pragma endregion enemy node



void EnemyManager::runEnemiseOneByOne(float dt)
{
	for(auto it = this->mEnemies.begin();it != this->mEnemies.end(); ++it)
	{
		it->second->run(this->mWayPoints, 30, 0);
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
		index++;
	}

}

void EnemyManager::update(float dt)
{
	static float timeCounter = 0;
	if(timeCounter >= 5)
	{
		auto id = this->addEnemy("yeti_0001.png");
		auto it = this->mEnemies.find(id);
		(*it).second->run(this->mWayPoints, 15, 0);
		timeCounter = 0;
	}
	else
	{
		timeCounter += dt;
	}
	this->clearUnusedEnemise();
}
