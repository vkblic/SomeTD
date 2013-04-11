
#ifndef _LEVELS_MANAGER_
#define _LEVELS_MANAGER_

#include "cocos2d.h"
#include "../Model/Enumeration.h"
#include "../Model/Models.h"
#include <queue>
using namespace cocos2d;

class LevelsManager 
{

public:
	~LevelsManager();
	static LevelsManager* sharedLevelsManager();
private:
	LevelsManager();
	static LevelsManager* mInstance;

private:
	Entry readWayPoints(int entryId, int waysEveryEntry, CCTMXObjectGroup* objects);

public:

	void readLevaInfo(const char* fileName, CCTMXObjectGroup* objects);

	void frameTrigger(float dt);

private:
	void clearUnusedEnemise();
private:
	std::map<std::string, LevelModel> mLeveInformations;
	LevelModel* mCurLevelInfo;
	std::queue<WaveModel*> mRemainWave;
	std::queue<WaveEnemyModel*> mCurWaveRemainEnemy;
	bool mIsWaveRunning;
	bool mIsCurLevelCompleted;
	//CCSpriteBatchNode* mBatch;

	//CCSpriteBatchNode* mHpBatchNode;

};

#endif
