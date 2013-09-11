
#ifndef _ENEMY_MANAGER_
#define _ENEMY_MANAGER_

#include "cocos2d.h"
#include "../Sprites/EnemyUnit.h"
#include "../Model/Enumeration.h"
#include "../Model/Models.h"
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
	 ENTITY_ID getEnemyInRange(CCPoint pos, int rangeRadius);

	/*
	 *add a enemy node to manager, manager have responsibility to 
	 *retain or release it 
	 *
	 *@param	plFrameName: enemy node pointer
	 *@return	a valid enemy node pointer	 */
	EnemyUnit* addEnemy(const char* name, CCPoint entry);

		/*
	 *add a enemy node to manager, manager have responsibility to 
	 *retain or release it 
	 *
	 *@param	plFrameName: enemy node pointer
	 *@return	a valid enemy node pointer	 */
	void addEnemyAndRush(const char* name, CCPoint entry, const std::vector<WayPointEx>* wayPoints);




	/*
	 *remove a enemy node from enemy map, add it to removed map for
	 *future use
	 *
	 *@param	enemyID: a valid enemyID
	 */
	void removeEnemy( ENTITY_ID enemyID);

	/*
	 *remove enemy node from removed map, add it to unused vector for
	 *next frame erase.
	 *
	 *@param	enemyID: a valid enemyID
	 */
	void eraseEnemy( ENTITY_ID enemyID);

	void frameTrigger(float dt);

	void setEnemyLayer(CCNode* layer);

	bool isEnemyInRange(CCPoint pos, int rangeRadius,  ENTITY_ID enemyID);



	bool isEnemyInRangeAndInTowerRange(CCPoint pos, int rangeRadius, CCPoint towerPos, int towerRangeRadius, ENTITY_ID enemyID);

	/*
	 *get the nearness enemy unit in range 
	 *
	 *@param	pos: the centre point to calculate range.
	 *			rangeRadius: radius of the calculation range.
	 *@return	a valid enemy object pointer, if it's available
	 *@			if not(destroyed of out of screen), the value NULL
	 */
	EnemyUnit* getAvailableEnemy( ENTITY_ID enemyID);

	void readEnemyInfo(const char* fileName);
	// fsm
public:

	void fsmTranslater( const MsgBase& msg, EnemyUnit* enemy);
	void changeState( EnemyUnit* unit, ActiveObj_States state );
	void sendMsg( MsgName name, ENTITY_ID senderID, ENTITY_ID receiverID );
	void sendDelayedMsg(MsgName name, int delay, ENTITY_ID senderID, ENTITY_ID receiverID );
	void sendCollisionRecMsg(ENTITY_ID senderID, ENTITY_ID receiverID, CCRect rect);
	void sendDamageMsg( ENTITY_ID senderID, ENTITY_ID receiverID, int damage );

	//void broadcaseDeadMsg( entity_id senderID );

private:
	void clearUnusedEnemise();
private:
	std::map<std::string, ActiveObjModel> mEnemyInfo;

	std::map<std::string, CCSpriteBatchNode*> mBatchNodes;
	std::map< ENTITY_ID, EnemyUnit*> mEnemies;
	std::map< ENTITY_ID, EnemyUnit*> mRemovedEnemies;
	std::vector<EnemyUnit*> mUnusedEnemy;
	std::vector<WayPoint> mWayPoints;
	CCNode* mEnemyLayer;
	
	//CCSpriteBatchNode* mBatch;

	//CCSpriteBatchNode* mHpBatchNode;

	 //long mIDSeed;
};

#endif
