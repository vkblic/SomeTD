//
//  Bullet.cpp
//  TileGameDemo
//
//  Created by kelyad on 02-17-2013.
//

#include "EnemyManager.h"
#include "../Helper/CommonHelpers.h"
#include "../Helper/SpriteHelpers.h"
#include "Utility/XmlReader.h"
using namespace cocos2d;

EnemyManager::EnemyManager()
{
	this->mEnemyLayer = NULL;
	//this->mHpBatchNode = NULL;
	//this->mBatch = NULL;
	this->mIDSeed = 0;
}
EnemyManager::~EnemyManager()
{
	for(auto it = this->mEnemies.begin(); it != this->mEnemies.end(); ++it)
	{
		it->second->release();
		//this->mBatch->removeChild(it->second, true);
		it->second->getParent()->removeChild(it->second, true);
		CCLog("EnemyManager::clearUnusedEnemise: retainCount: %d", it->second->retainCount());
	}
	this->mEnemies.clear();

	for(auto it = this->mBatchNodes.begin(); it != this->mBatchNodes.end(); ++it)
	{
		it->second->release();
		it->second->getParent()->removeChild(it->second, true);
	}

	this->mEnemyLayer->release();
	//this->mBatch->release();
	//this->mHpBatchNode->release();
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

void EnemyManager::readEnemyInfo(const char* fileName)
{
	XmlReader::readAllEnemyInfo(this->mEnemyInfo, fileName);
}






#pragma region Range checker

unsigned long EnemyManager::getEnemyInRange(CCPoint pos, int rangeRadius)
{

	for(auto it = this->mEnemies.begin();it != this->mEnemies.end(); ++it)
	{
		if (isRectAndCircleCollided(pos, rangeRadius, it->second->getCollisionRect()))
		{
			CCPoint targetPos = it->second->getPosition();
			CCSize targetSize = it->second->getContentSize();
			CCRect rect = it->second->getCollisionRect();
			CCLog("New target in range.");
			CCLog("target: {{%f, %f}, {%f, %f}}", targetPos.x, targetPos.y, targetSize.width, targetSize.height);
			CCLog("collisionRect Old: {{%f, %f}, {%f, %f}}",rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);
			CCLog("tower: pos(%f, %f)", pos.x, pos.y );
			return it->first;
		}
	}
	return -1;
}

bool EnemyManager::isEnemyInRange(CCPoint pos, int rangeRadius, unsigned long enemyID)
{
	auto it = this->mEnemies.find(enemyID);

	// enemy already dead
	if (it == this->mEnemies.end())
		return false;

	if (isRectAndCircleCollided(pos, rangeRadius, it->second->getCollisionRect()))
		return true;
	CCPoint targetPos = it->second->getPosition();
	CCSize targetSize = it->second->getContentSize();
	CCLog("\ntarget out of range.");
	CCLog("target: pos(%f, %f), width: %f, height: %f", targetPos.x, targetPos.y, targetSize.width, targetSize.height);
	CCLog("tower: pos(%f, %f)", pos.x, pos.y );
	return false;
}

#pragma endregion


#pragma region enemy node

Enemy* EnemyManager::addEnemy(const char* enemyName)
{

	auto enemyInfo = this->mEnemyInfo.find(enemyName);
	EnemyModel* temp = &(*enemyInfo).second;

	auto it = this->mBatchNodes.find(temp->textureSet);
	CCSpriteBatchNode* batch;
	if(it == this->mBatchNodes.end())
	{
		batch = CCSpriteBatchNode::create(temp->textureSet);
		this->mBatchNodes.insert(
			std::map<std::string, CCSpriteBatchNode*>::value_type(
			temp->textureSet, 
			batch
			)
			);
		this->mEnemyLayer->addChild(batch);
	}
	else
	{
		batch = (*it).second;
	}

	it = this->mBatchNodes.find("hp.png");
	CCSpriteBatchNode* hpBatch;
	if(it == this->mBatchNodes.end())
	{
		hpBatch = CCSpriteBatchNode::create("hp.png");
		this->mBatchNodes.insert(std::map<std::string, CCSpriteBatchNode*>::value_type(
			"hp.png", 
			hpBatch)
			);
		this->mEnemyLayer->addChild(hpBatch);
	}
	else
	{
		hpBatch = (*it).second;
	}


	auto enemy = Enemy::create(temp, hpBatch);
	//CCLog("EnemyManager::addEnemy: retainCount: %d", enemy->retainCount());
	this->mEnemies.insert(std::pair<unsigned long, Enemy*>(this->mIDSeed, enemy));
	batch->addChild(enemy);
	enemy->setID(this->mIDSeed++);
	return enemy;
}

void EnemyManager::removeEnemy(unsigned long enemyID)
{
	auto it = this->mEnemies.find(enemyID);
	if(it == this->mEnemies.end())
		CCAssert(false, "must find id in map! there must be some error some where!");

	this->mRemovedEnemies.insert(std::map<unsigned long, Enemy*>::value_type(enemyID, it->second));

	this->mEnemies.erase(it);
}

void EnemyManager::eraseEnemy(unsigned long enemyID)
{
	auto it = this->mRemovedEnemies.find(enemyID);
	if(it == this->mRemovedEnemies.end())
		CCAssert(false, "must find id in map! there must be some error some where!");

	this->mUnusedEnemy.push_back(it->second);
	this->mRemovedEnemies.erase(it);
}



void EnemyManager::clearUnusedEnemise()
{
	for(auto it = this->mUnusedEnemy.begin(); it != this->mUnusedEnemy.end(); ++it)
	{
		auto node = (*it);
		//node->release();
		//CCLog("EnemyManager::clearUnusedEnemise: retainCount: %d", node->retainCount());
		auto batch = (*this->mBatchNodes.find(node->getEnemyInfo()->textureSet)).second;
		batch->removeChild(node, true);
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

#pragma endregion



void EnemyManager::update(float dt)
{
	this->clearUnusedEnemise();
}
