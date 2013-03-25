#ifndef _ENEMY_INFO_READER_
#define _ENEMY_INFO_READER_


#include "cocos2d.h"
#include "../Model/Models.h"
class XmlReader
{
public:
	static bool readAllEnemyInfo(std::map<std::string, EnemyModel>& enemyInfoMap, const char* fileName);
	static bool readAllLevelInfo(std::map<std::string, LevelModel>& levelInfoMap, const char* fileName);
};
#endif