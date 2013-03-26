// 
//  Enumeration.h
//  MyMoonWarriors
//
//  By Kelyad on 11/04/2012
//

#ifndef _MODELS_
#define _MODELS_
#include "cocos2d.h"
using namespace cocos2d;

enum eEnmeyTag
{
	EnemyTag_Default,
	EnmeyTag_MoveUp,
	EnmeyTag_MoveDown,
	EnmeyTag_MoveRight,
	EnmeyTag_MoveLeft,
	EnmeyTag_MoveLeftUp,
	EnmeyTag_MoveLeftDown,
	EnmeyTag_MoveRightUp,
	EnmeyTag_MoveRightDown,
	EnemyTag_Dead,
	EnemyTag_Attack,

	EnmeyTag_Max
};

typedef struct EnemyModel
{
	EnemyModel()
	{
		this->name[0] = '\0';
		this->textureSet[0] = '\0';
		this->plist[0] = '\0';
		this->animations.resize(EnmeyTag_Max);
	}
	char name[128];
	char textureSet[36];
	char plist[36];
	CCSpriteFrame* defaultFrame;
	std::vector<CCAnimation*> animations;

//informations
	int hp;
	int physicalDefend;
	int magicDefend;
	int physicalAttack;
	int magicAttack;

	/*
	 *tiles per seconds
	 */
	float speed;

	CCPoint pos;
}*pEnemyModel;


#pragma region Level

typedef struct WaveEnemyModel
{
	char enemyName[128];
	float delay;
	int wayID;
	int entryID;
}*pWaveEnemyModel;

typedef struct WaveModel
{
	int id;
	std::vector<WaveEnemyModel> enemise;
}*pWaveModel;

typedef struct WayPointEx
{
	WayPointEx(int x, int y, int id)
	{
		this->pos.x = x;
		this->pos.y = y;
		this->wayPointID = id;
	}
	CCPoint pos;
	int wayPointID;
}*pWayPointEx;

typedef struct Entry 
{
	CCPoint pos;
	int id;
	std::vector<std::vector<WayPointEx>> ways;
}*pEntry;



typedef struct LevelModel
{
	LevelModel()
	{
		this->name[0] = '\0';
		this->mapFile[0] = '\0';
	}

	char name[64];
	char mapFile[64];
	int waveCount;
	float waveInterval;
	int entryCount;
	int	waysEveryEntry;
	std::vector<WaveModel> waves;
	std::vector<Entry> entrise;
}*pLevelModel;






#pragma endregion
#endif
