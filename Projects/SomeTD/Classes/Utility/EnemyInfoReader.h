#ifndef _ENEMY_INFO_READER_
#define _ENEMY_INFO_READER_


#include "cocos2d.h"
#include "../Model/Models.h"
class EnemyInfoReader
{
public:
	static bool readAllEnemyInfo(std::map<std::string, EnemyModel>& enemyInfoMap, const char* fileName);
};
#endif