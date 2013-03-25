//
//  Bullet.cpp
//  TileGameDemo
//
//  Created by kelyad on 02-17-2013.
//

#include "LevelsManager.h"
#include "Utility/XmlReader.h"
#include "EnemyManager.h"
using namespace cocos2d;

LevelsManager::LevelsManager()
{
	//this->mHpBatchNode = NULL;
	//this->mBatch = NULL;
	this->mIDSeed = 0;
}
LevelsManager::~LevelsManager()
{

	//this->mBatch->release();
	//this->mHpBatchNode->release();
}

LevelsManager* LevelsManager::mInstance = NULL;
LevelsManager* LevelsManager::sharedLevelsManager()
{
	if (LevelsManager::mInstance == NULL)
		LevelsManager::mInstance = new LevelsManager();
	return LevelsManager::mInstance;
}


void LevelsManager::readLevaInfo(const char* fileName, CCTMXObjectGroup* objects)
{
	XmlReader::readAllLevelInfo(mLeveInformations, fileName);
	for(auto it = mLeveInformations.begin(); it != mLeveInformations.end(); ++it)
	{
		LevelModel* level = &it->second;

		for(int i = 0; i < level->entryCount; ++i)
		{
			auto entry = this->readWayPoints(i, level->waysEveryEntry, objects);
			level->entrise.push_back(entry);
		}
	}
}







Entry LevelsManager::readWayPoints(int entryId, int waysEveryEntry, CCTMXObjectGroup* objects)
{
	Entry entry;
	entry.id = entryId;
	char buffer[64];
	sprintf(buffer, "Entry_%d", entry.id);
	auto entryPair = objects->objectNamed(buffer);
	if(entryPair == NULL)
		return entry;
	entry.pos = CCPoint(entryPair->valueForKey("x")->intValue(), entryPair->valueForKey("y")->intValue());
	int index = 0;
	for (int i = 0; i < waysEveryEntry; ++i)
	{
		std::vector<WayPointEx> way;
		while (true)
		{
			sprintf(buffer, "WayPoint_%d_%d_%d", entry.id, i, index);
			CCDictionary *temp = objects->objectNamed(buffer);
			if (temp == NULL) 
				break;
			int x = temp->valueForKey("x")->intValue();
			int y = temp->valueForKey("y")->intValue();
			way.push_back(WayPointEx(x, y, index));
			index++;
		}
		entry.ways.push_back(way);
	}

	return entry;
}

void LevelsManager::update(float dt)
{
	auto enemyManger = EnemyManager::sharedEnemyManager();
	static float timeCounter = 0;
	if(timeCounter >= 3)
	{
		auto enemy = enemyManger->addEnemy("yeti");
		enemy->run(this->mLeveInformations["demo"].entrise[0].ways[0], 15, 0);
		timeCounter = 0;
	}
	else
	{
		timeCounter += dt;
	}
}
