#ifndef _INFO_DATA_H
#define _INFO_DATA_H

#include "Enumeration.h"
#include "cocos2d.h"
#include "../Sprites/Bullet.h"
#include "../Helper/SpriteHelpers.h"
#include "../Helper/CommonHelpers.h"
/*
* Enemy ship infomation
**/
using namespace cocos2d;
struct EnemyInfoModel
{
	ENEMY_SHOW_COUNT ShowCount;
	int ShowTime; //seconds
	ENEMY_ACTION_TYPE ActionType[10];
	ATTACK_MODE AttackMode;
	int AttackSpeed; // times a second
	int HP;
	int ScoreValue;
	int HurtColorLife;
	char textureName[64];

};


/*
*bullet infomation
**/
struct WeaponInfoModel
{
public:
	static char* _TextureNameByType[2]; //there's only two texture for now
	static int _DamageByType[2];
	static int _SpeedByType[2];
public:
	int BulletSpeed; //pitch per second
	int damage; // HP decrease per hit, depends on ship
	int zOrder;
	//int 
	BULLET_TYPE BulletType;
public:	 
	static char* GetTextureName(BULLET_TYPE type)
	{
		return _TextureNameByType[type];
	}
	static int GetDamage(BULLET_TYPE type)
	{
		return _DamageByType[type];
	}

};




#endif