//
//  Bullet.cpp
//  TileGameDemo
//
//  Created by kelyad on 02-17-2013.
//

#include "AlliesManager.h"
#include "../Helper/CommonHelpers.h"
#include "../Helper/SpriteHelpers.h"
#include "Utility/XmlReader.h"
using namespace cocos2d;

AllyManager::AllyManager()
{
	this->mAllyLayer = NULL;
	//this->mHpBatchNode = NULL;
	//this->mBatch = NULL;
	this->mIDSeed = 0;
}
AllyManager::~AllyManager()
{
	for(auto it = this->mAllies.begin(); it != this->mAllies.end(); ++it)
	{
		it->second->release();
		//this->mBatch->removeChild(it->second, true);
		it->second->getParent()->removeChild(it->second, true);
		CCLog("EnemyManager::clearUnusedEnemise: retainCount: %d", it->second->retainCount());
	}
	this->mAllies.clear();

	for(auto it = this->mBatchNodes.begin(); it != this->mBatchNodes.end(); ++it)
	{
		it->second->release();
		it->second->getParent()->removeChild(it->second, true);
	}

	this->mAllyLayer->release();
	//this->mBatch->release();
	//this->mHpBatchNode->release();
}

AllyManager* AllyManager::mInstance = NULL;
AllyManager* AllyManager::sharedAllyManager()
{
	if (AllyManager::mInstance == NULL)
		AllyManager::mInstance = new AllyManager();
	return AllyManager::mInstance;
}

void AllyManager::setObjectLayer(CCNode* layer)
{
	this->mAllyLayer = layer;
}

void AllyManager::readAlliesInfo(const char* fileName)
{
	XmlReader::readActiveObjectInfoFromFile(this->mAllyInfo, fileName);
}






#pragma region Range checker

long AllyManager::getObjInRange(CCPoint pos, int rangeRadius)
{

	for(auto it = this->mAllies.begin();it != this->mAllies.end(); ++it)
	{
		if (isRectAndCircleCollided(pos, rangeRadius, it->second->getCollisionRect()))
		{
			CCPoint targetPos = it->second->getPosition();
			CCSize targetSize = it->second->getContentSize();
			CCRect rect = it->second->getCollisionRect();
			//CCLog("New target in range.");
			//CCLog("target: {{%f, %f}, {%f, %f}}", targetPos.x, targetPos.y, targetSize.width, targetSize.height);
			//CCLog("collisionRect Old: {{%f, %f}, {%f, %f}}",rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);
			//CCLog("tower: pos(%f, %f)", pos.x, pos.y );
			return it->first;
		}
	}
	return -1;
}

bool AllyManager::isOjbectInRange(CCPoint pos, int rangeRadius,  long id)
{
	auto it = this->mAllies.find(id);

	// enemy already dead
	if (it == this->mAllies.end())
		return false;

	if (isRectAndCircleCollided(pos, rangeRadius, it->second->getCollisionRect()))
		return true;
	CCPoint targetPos = it->second->getPosition();
	CCSize targetSize = it->second->getContentSize();
	//CCLog("\ntarget out of range.");
	//CCLog("target: pos(%f, %f), width: %f, height: %f", targetPos.x, targetPos.y, targetSize.width, targetSize.height);
	//CCLog("tower: pos(%f, %f)", pos.x, pos.y );
	return false;
}

#pragma endregion


#pragma region enemy node

AllyUnit* AllyManager::addAlly(const char* enemyName, CCPoint pos)
{

	auto allyInfo = this->mAllyInfo.find(enemyName);
	ActiveObjModel* temp = &(*allyInfo).second;

	// dealing with batch node
	auto batch = this->getBatchNode(temp->textureSet);
	auto hpBatch = this->getBatchNode("hp.png");

	auto ally = AllyUnit::create(temp, hpBatch);
	//CCLog("EnemyManager::addEnemy: retainCount: %d", enemy->retainCount());
	this->mAllies.insert(std::pair< long, AllyUnit*>(this->mIDSeed, ally));
	batch->addChild(ally);
	ally->setID(this->mIDSeed++);
	ally->setPosition(pos);
	return ally;
}

AllyUnit* AllyManager::addAllyAndGetReadyForFight(const char* enemyName, CCPoint pos)
{
	auto allyInfo = this->mAllyInfo.find(enemyName);
	ActiveObjModel* temp = &(*allyInfo).second;

	// dealing with batch node
	auto batch = this->getBatchNode(temp->textureSet);
	auto hpBatch = this->getBatchNode("hp.png");

	auto ally = AllyUnit::create(temp, hpBatch);
	//CCLog("EnemyManager::addEnemy: retainCount: %d", enemy->retainCount());
	this->mAllies.insert(std::pair< long, AllyUnit*>(this->mIDSeed, ally));
	batch->addChild(ally);
	ally->setID(this->mIDSeed++);
	ally->setPosition(pos);
	ally->run();
	return ally;
}


CCSpriteBatchNode* AllyManager::getBatchNode( const char* textureSetName )
{

	auto it = this->mBatchNodes.find(textureSetName);
	CCSpriteBatchNode* batch;
	if(it == this->mBatchNodes.end())
	{
		batch = CCSpriteBatchNode::create(textureSetName);
		this->mBatchNodes.insert(
			std::map<std::string, CCSpriteBatchNode*>::value_type(
			textureSetName, 
			batch
			)
			);
		this->mAllyLayer->addChild(batch);
	}
	else
	{
		batch = (*it).second;
	}
	return batch;
}



void AllyManager::removeAllyByID( long id)
{
	auto it = this->mAllies.find(id);
	if(it == this->mAllies.end())
		CCAssert(false, "must find id in map! there must be some error some where!");

	this->mRemovedAllies.insert(std::map< long, AllyUnit*>::value_type(id, it->second));

	this->mAllies.erase(it);
}

void AllyManager::eraseAllyByID( long id)
{
	auto it = this->mRemovedAllies.find(id);
	if(it == this->mRemovedAllies.end())
		CCAssert(false, "must find id in map! there must be some error some where!");

	this->mUnusedAllies.push_back(it->second);
	this->mRemovedAllies.erase(it);
}



void AllyManager::clearUnusedEnemise()
{
	for(auto it = this->mUnusedAllies.begin(); it != this->mUnusedAllies.end(); ++it)
	{
		auto node = (*it);
		//node->release();
		//CCLog("EnemyManager::clearUnusedEnemise: retainCount: %d", node->retainCount());
		auto batch = (*this->mBatchNodes.find(node->getEnemyInfo()->textureSet)).second;
		batch->removeChild(node, true);
	}
	this->mUnusedAllies.clear();
}

AllyUnit* AllyManager::getAvailableObject( long id)
{
	auto it = this->mAllies.find(id);
	if (it == this->mAllies.end())
		return NULL;
	return it->second;
}

#pragma endregion



void AllyManager::update(float dt)
{
	this->clearUnusedEnemise();
}
