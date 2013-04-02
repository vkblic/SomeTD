
#ifndef _TOWER_MANAGER_
#define _TOWER_MANAGER_

#include "cocos2d.h"
#include "../Model/Enumeration.h"
#include "../Model/TowerInformation.h"
#include <queue>
using namespace cocos2d;

class TowerManager 
{

public:
	~TowerManager();
	static TowerManager* sharedLevelsManager();
private:
	TowerManager();
	static TowerManager* mInstance;

};

#endif
