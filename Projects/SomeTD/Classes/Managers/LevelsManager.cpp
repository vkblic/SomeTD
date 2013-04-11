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
	mIsWaveRunning = false;
	mIsCurLevelCompleted = false;
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

	//read waypoints and entry information from tilemap
	for(auto it = mLeveInformations.begin(); it != mLeveInformations.end(); ++it)
	{
		LevelModel* level = &it->second;

		for(int i = 0; i < level->entryCount; ++i)
		{
			auto entry = this->readWayPoints(i, level->waysEveryEntry, objects);
			level->entrise.push_back(entry);
		}
	}

	// build wave queue

	// just for test

	mCurLevelInfo = &mLeveInformations["demo"];
	for(auto wave = mCurLevelInfo->waves.begin(); wave != mCurLevelInfo->waves.end(); ++wave)
	{
		mRemainWave.push(&(*wave));
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
	
	for (int i = 0; i < waysEveryEntry; ++i)
	{
		std::vector<WayPointEx> way;
		int index = 0;
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

static float offset = 1;
static float curWaveStartTime;
static bool test = false;
void LevelsManager::frameTrigger(float dt)
{
	// for test
	while (false)
	{
		if (test)
			return;
		EnemyManager::sharedEnemyManager()->addEnemyAndRush("marauder", mCurLevelInfo->entrise[0].pos, &mCurLevelInfo->entrise[0].ways[0] );
		test = true;
		return;
	} 

	if(mIsCurLevelCompleted)
		return;
	auto enemyManger = EnemyManager::sharedEnemyManager();
	static float timeCounter = 0;
	timeCounter += dt;
	if(timeCounter >= offset)
	{
		//start wave
		if(!mIsWaveRunning)
		{
			mIsWaveRunning = true;
			if (mRemainWave.size() == 0)
			{
				//mIsCurLevelCompleted = true;
				//CCLog("Last wave completed!");

				//CCLog("level loop for test!");
				for(auto wave = mCurLevelInfo->waves.begin(); wave != mCurLevelInfo->waves.end(); ++wave)
				{
					mRemainWave.push(&(*wave));
				}
				return;
			}
			auto wave = mRemainWave.front();
			
			for(auto enemy = (*wave).enemise.begin(); enemy != (*wave).enemise.end(); ++enemy)
			{
				mCurWaveRemainEnemy.push(&(*enemy));
			}
			mRemainWave.pop();
			curWaveStartTime = 0;
			//CCLog("Wave start %d", (*wave).id);
		}
		// let enemy rush
		else
		{
			curWaveStartTime += dt;
			auto enemyManager = EnemyManager::sharedEnemyManager();
			while (true)
			{
				if (mCurWaveRemainEnemy.size() == 0)
					break;
				auto enemy = mCurWaveRemainEnemy.front();
				if(curWaveStartTime > enemy->delay)
				{
					//CCLog("new [%s] start rush! curTime: %f, delay: %f", enemy->enemyName, curWaveStartTime, enemy->delay);
					enemyManager->addEnemyAndRush(enemy->enemyName, mCurLevelInfo->entrise[enemy->entryID].pos, &mCurLevelInfo->entrise[enemy->entryID].ways[enemy->wayID] );
					mCurWaveRemainEnemy.pop();
				}
				else
					break;
			}
			//size equal to zero means wave complete!
			if (mCurWaveRemainEnemy.size() == 0)
			{
				//CCLog("wave complted"); 
				offset = timeCounter + mCurLevelInfo->waveInterval;
				mIsWaveRunning = false;
			}
		}



		//auto enemy = enemyManger->addEnemy("yeti");
		//enemy->run(this->mLeveInformations["demo"].entrise[0].ways[0], 15, 0);
	}
	else
	{
		static float temp = 0;
		if(temp > 1)
		{
			//CCLog("next wave: %f", offset - timeCounter);
			temp = 0;
		}
		else
		{
			temp += dt;
		}
	}
}
