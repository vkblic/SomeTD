
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
private:
	EnemyManager();
	static EnemyManager* mInstance;

public:
	/*
	 *get the nearness enemy unit in range 
	 *
	 *@param	pos: the centre point to calculate range.
	 *			rangeRadius: radius of the calculation range.
	 *@return	a valid enemy id if there has a enemy in range, 
	 *@			if not, the value is -1
	 */
	unsigned long getEnemyInRange(CCPoint pos, int rangeRadius);

	/*
	 *add a enemy node to manager, manager have responsibility to 
	 *retain or release it 
	 *
	 *@param	enemy: enemy node pointer
	 *@return	a valid enemyID
	 */
	unsigned long addEnemy(const char* plFrameName);

	void removeEnemy(unsigned long enemyID);

	void update(float dt);

	void setEnemyLayer(CCNode* layer);

	bool isEnemyInRange(CCPoint pos, int rangeRadius, unsigned long enemyID);

	/*
	 *get the nearness enemy unit in range 
	 *
	 *@param	pos: the centre point to calculate range.
	 *			rangeRadius: radius of the calculation range.
	 *@return	a valid enemy object pointer, if it's available
	 *@			if not(destroyed of out of screen), the value NULL
	 */
	Enemy* getAvailableEnemy(unsigned long enemyID);

	void runEnemiseOneByOne(float dt);

	void readWayPoints(CCTMXObjectGroup* objects);
private:
	void clearUnusedEnemise();
private:
	std::map<unsigned long, Enemy*> mEnemies;
	std::vector<Enemy*> mUnusedEnemy;
	std::vector<WayPoint> mWayPoints;
	CCNode* mEnemyLayer;
	
	CCSpriteBatchNode* mBatch;

	CCSpriteBatchNode* mHpBatchNode;

	unsigned long mIDSeed;
};

#endif
