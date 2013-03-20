
#ifndef _ENEMY_MANAGER_
#define _ENEMY_MANAGER_

#include "cocos2d.h"
#include "../Sprites/Enemy.h"
#include "../Model/Enumeration.h"
using namespace cocos2d;

class EnemyManager 
{

public:
	~EnemyManager();
	static EnemyManager* sharedEnemyManager();
public:
	/*
	 *get the nearness enemy unit in range 
	 *
	 *@param	pos: the centre point to calculate range.
	 *			rangeRadius: radius of the calculation range.
	 *@return	a valid sprite pointer to a valid sprite object, 
	 *@			if there has a enemy in range, if not, the value 
	 *@			is NULL
	 */
	Enemy* getEnemyInRange(CCPoint& pos, int rangeRadius);

	/*
	 *add a enemy node to manager, manager have responsibility to 
	 *retain or release it 
	 *
	 *@param	enemy: enemy node pointer
	 */
	void addEnemy(Enemy* enemy);

	void setEnemyLayer(CCNode* layer);

	bool isEnemyInRange(CCPoint& pos, int rangeRadius, Enemy* enemy);

	void runEnemiseOneByOne(float dt);

	void readWayPoints(CCTMXObjectGroup* objects);
private:
	EnemyManager();
	static EnemyManager* mInstance;

private:
	std::vector<Enemy*> mEnemies;
	std::vector<WayPoint> mWayPoints;
	CCNode* mEnemyLayer;
	CCSpriteBatchNode* mBatch;
};

#endif
