
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
	 entity_id getObjInRange( CCPoint pos, int rangeRadius );

	/*
	 *add a enemy node to manager, manager have responsibility to 
	 *retain or release it 
	 *
	 *@param	plFrameName: enemy node pointer
	 *@return	a valid enemy node pointer	 
	 */
	AllyUnit* addAlly(const char* name, CCPoint pos);




	/*
	 *remove a enemy node from enemy map, add it to removed map for
	 *future use
	 *
	 *@param	enemyID: a valid enemyID
	 */
	void removeAllyByID( entity_id id );

	/*
	 *remove enemy node from removed map, add it to unused vector for
	 *next frame erase.
	 *
	 *@param	enemyID: a valid enemyID
	 */
	void eraseAllyByID( entity_id id);

	void setObjectLayer( CCNode* layer );

	bool isOjbectInRange( CCPoint pos, int rangeRadius,  entity_id enemyID );

	/*
	 *get the obj unit by ID 
	 *
	 *@param	id: the object ID.
	 *@return	a valid object pointer, if it's available
	 *@			if not(destroyed of out of screen), the value NULL
	 */
	AllyUnit* getAvailableObject( entity_id id );


	/*
	 *read allies information from file to activeOjbect map
	*
	 */
	void readAlliesInfo( const char* fileName );


	void frameTrigger(float dt);


// fsm
public:

	void fsmTranslater( const MsgObject& msg, AllyUnit* ally);
	void changeState( AllyUnit* unit, ActiveObj_States state );
	void sendMsg( MsgName name, entity_id senderID, entity_id receiverID );
	void sendDamageMsg( entity_id senderID, entity_id receiverID, int damage );
	void sendCollisionRecMsg(entity_id senderID, entity_id receiverID, CCRect rect);
private:
	void clearUnusedAllies();
	CCSpriteBatchNode* getBatchNode( const char* textureSetName );
private:
	std::map<std::string, ActiveObjModel> mAllyInfo;

	std::map<std::string, CCSpriteBatchNode*> mBatchNodes;
	std::map<entity_id, AllyUnit*> mAllies;
	std::map<entity_id, AllyUnit*> mRemovedAllies;
	std::vector<AllyUnit*> mUnusedAllies;
	std::vector<WayPoint> mWayPoints;
	CCNode* mAllyLayer;
	
	//CCSpriteBatchNode* mBatch;

	//CCSpriteBatchNode* mHpBatchNode;

	 entity_id mIDSeed;
};

#endif
