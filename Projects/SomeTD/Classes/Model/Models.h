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





#endif
