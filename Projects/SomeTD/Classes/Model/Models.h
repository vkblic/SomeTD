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

#pragma region ActiveObject

enum eActiveObjTag
{
	ActiveObjTag_Stoped,
	ActiveObjTag_Default,
	ActiveObjTag_MoveUp,
	ActiveObjTag_MoveDown,
	ActiveObjTag_MoveRightLeft,
	ActiveObjTag_Dead,
	ActiveObjTag_Attack,

	ActiveObjTag_Max
};

typedef enum
{ 
	STATE_NULL,
	STATE_Idle,
	STATE_Moving,
	STATE_Stoped,
	STATE_MovingWithAttack,
	STATE_MovingToTarget,
	STATE_Attacking,
	STATE_Dead,


	STATE_MAX
} ActiveObj_States;



typedef struct ActiveObjModel
{
	ActiveObjModel()
	{
		this->name[0] = '\0';
		this->textureSet[0] = '\0';
		this->plist[0] = '\0';
		this->animations.resize(ActiveObjTag_Max);
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
	int alertRange;
	/*
	 *tiles per seconds
	 */
	float speed;

	CCPoint pos;
}*pEnemyModel;

#pragma endregion


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
