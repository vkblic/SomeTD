
#ifndef _ALLY_UNIT_
#define _ALLY_UNIT_

#include "ActiveEntity.h"
#include "../Model/Enumeration.h"
#include "../Model/Models.h"
using namespace cocos2d;

//Tower class
enum eAllyStatus
{
	AllyStatus_Moving,
	AllyStatus_MovingToTarget,
	AllyStatus_Attack,
	AllyStatus_Waiting
};

class AllyUnit : public ActiveEntity , public CCTouchDelegate
{

public:
	static AllyUnit* create(ActiveObjModel* enemyInfo, CCSpriteBatchNode* hpBatchNode);

public:
public:
	virtual ~AllyUnit();

	virtual void onEnter();
	virtual void onExit();
	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);


public:
	void frameListener(float dt); // execute every frame

	void removeAttacker(entity_id attackerID);
	//void run(std::vector<WayPointEx>& wayPoints);



public:
	void myInit();


	bool targetIs(entity_id targetID) { return mTargetID == targetID; }
	/*
	*
	*
	*
	*/
	//void run() {mState = STATE_Idle;}
	void moveToMassPos();
	void onInPosition();
	//void attacking();
	//void onHit();


public: 
	// idle
	bool findTarget();
	bool targetCheck( entity_id targetID );
	void onEnterIdle()
	{
		mTargetID = non_entity;
	}

	// moveToTarget
	void enterMoveToTarget();
	bool onMovingToTarget( float dt );

	bool onMoveTo( float dt, const CCPoint& destPos ) ;

	void setTargetCollisionRect( const CCRect& rect ) 
	{
		this->mTargetCollisionRect = rect;
	}

	void exitMoveToTarget();

	// attacking
	void enterAttacking();
	void attacking();
	void onHitTarget();
	void exitAttacing();

	//be injured
	void underAttack( int damage, entity_id attackerID, CCRect rect );

	//dead
	void destory();
	void onDestoryed();

	//msg
	void sendDeadMsg();

private:



	//int mMaxHP;
	entity_id mTargetID;
	CCRect mTargetCollisionRect;
	CCRect mPreTargetCollisionRect;
	CCPoint mDestinationPos;
	std::map<entity_id, CCRect> mAttackers;

	// other
	int mTargetSearchInterval;

	//temp
private:
	CCPoint mTowerPos;
	int mTowerAlertRange;
	CCPoint mMassPos;
public:
	void setTowerPos( const CCPoint& towerPos ) { mTowerPos = towerPos; }
	void setTowerAlertRange( int range ) { mTowerAlertRange = range; }
	void setMassPos( const CCPoint& massPos ) { mMassPos = massPos; }

};



//typedef void (Tower::*SEL_MenuTouchedFunc)(int);

//#define towerMenuCallFunc(func) (SEL_MenuTouchedFunc)(&func)


#endif