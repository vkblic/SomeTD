
#ifndef _ALLY_MANAGER_
#define _ALLY_MANAGER_

#include "cocos2d.h"
#include "../Sprites/AllyUnit.h"
#include "../Model/Enumeration.h"
#include "../Model/Models.h"
#include "../MessagePump/MsgObject.h"
using namespace cocos2d;

class AllyManager 
{

public:
	~AllyManager();
	static AllyManager* sharedAllyManager();
private:
	AllyManager();
	static AllyManager* mInstance;

public:
	/*
	 *get the nearness enemy unit in range 
	 *
	 *@param	pos: the centre point to calculate range.
	 *			rangeRadius: radius of the calculation range.
	 *@return	a valid enemy id if there has a enemy in range, 
	 *@			if not, the value is -1
	 */
	 ENTITY_ID getObjInRange( const CCPoint&  pos, int rangeRadius );

	/*
	 *add a enemy node to manager, manager have responsibility to 
	 *retain or release it 
	 *
	 *@param	plFrameName: enemy node pointer
	 *@return	a valid enemy node pointer	 
	 */
	AllyUnit* addAlly(const char* name, const CCPoint& pos, const CCPoint&  towerPos);




	/*
	 *remove a enemy node from enemy map, add it to removed map for
	 *future use
	 *
	 *@param	enemyID: a valid enemyID
	 */
	void removeAllyByID( ENTITY_ID id );

	/*
	 *remove enemy node from removed map, add it to unused vector for
	 *next frame erase.
	 *
	 *@param	enemyID: a valid enemyID
	 */
	void eraseAllyByID( ENTITY_ID id);

	void setObjectLayer( CCNode* layer );

	bool isOjbectInRange( const CCPoint&  pos, int rangeRadius,  ENTITY_ID enemyID );

	/*
	 *get the obj unit by ID 
	 *
	 *@param	id: the object ID.
	 *@return	a valid object pointer, if it's available
	 *@			if not(destroyed of out of screen), the value NULL
	 */
	AllyUnit* getAvailableObject( ENTITY_ID id );


	/*
	 *read allies information from file to activeOjbect map
	*
	 */
	void readAlliesInfo( const char* fileName );


	void frameTrigger(float dt);


// fsm
public:

	void fsmTranslater( const MsgBase& msg, AllyUnit* ally);
	void changeState( AllyUnit* unit, ActiveObj_States state );
	void sendMsg( MsgName name, ENTITY_ID senderID, ENTITY_ID receiverID );
	void sendDamageMsg( ENTITY_ID senderID, ENTITY_ID receiverID, int damage );
	void sendCollisionRecMsg(ENTITY_ID senderID, ENTITY_ID receiverID, CCRect rect);
private:
	void clearUnusedAllies();
	CCSpriteBatchNode* getBatchNode( const char* textureSetName );
private:
	std::map<std::string, ActiveObjModel> mAllyInfo;

	std::map<std::string, CCSpriteBatchNode*> mBatchNodes;
	std::map<ENTITY_ID, AllyUnit*> mAllies;
	std::map<ENTITY_ID, AllyUnit*> mRemovedAllies;
	std::vector<AllyUnit*> mUnusedAllies;
	std::vector<WayPoint> mWayPoints;
	CCNode* mAllyLayer;
	
	//CCSpriteBatchNode* mBatch;

	//CCSpriteBatchNode* mHpBatchNode;

	 ENTITY_ID mIDSeed;
};

#endif
