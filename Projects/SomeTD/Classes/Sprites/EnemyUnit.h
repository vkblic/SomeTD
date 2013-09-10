
#ifndef _ENEMY_UNIT_
#define _ENEMY_UNIT_

#include "cocos2d.h"
#include "ActiveEntity.h"
#include "../Model/Enumeration.h"
#include "../Model/Models.h"
using namespace cocos2d;

//Tower class
enum eEnemyStatus
{
	EnemyStatus_Moving,
	EnemyStatus_WaitingForAttack,
	EnemyStatus_Attacking
};



class EnemyUnit : public ActiveEntity , public CCTouchDelegate
{

public:
	static EnemyUnit* create(ActiveObjModel* enemyInfo, CCSpriteBatchNode* hpBatchNode);

public:
public:
	virtual ~EnemyUnit();

	//重写触屏相关函数----
	virtual void onEnter();
	virtual void onExit();
	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);


public:
	void frameListener(float dt); // execute every frame

	void run(const std::vector<WayPointEx>* wayPoints);



public:
	void myInit();//自定义初始化函数
	void underAttack(int damage, ENTITY_ID attackerID, CCRect rect);
	void underAttack(int damage);
	void destory();
	void onDestoryed();
	void onArriveEndPoint();


	void addAttacker(ENTITY_ID attackerID, CCRect rect);
	void removeAttacker(ENTITY_ID attackerID);
	void removeTarget();
	void setTarget(ENTITY_ID targetID) {mTargetID = targetID;}
	ENTITY_ID getTarget(){return mTargetID;}
	void setTargetCollisionRect( const CCRect& rect ) 
	{
		this->mTargetCollisionRect = rect;
	}
	//void targetAlert(entity_id targetID) 
	//{ 
	//	mTargetID = targetID;
	//	//mCurStatus = EnemyStatus_WaitingForAttack; 
	//}
	//void startAttack();
	//void onHit();

public:
	// attacking
	void enterAttacking();
	void onAttacking();
	void onHitTarget();
	void exitAttacing();

	// moving
	void enterMoving();
	bool movingUpdate(float dt);
	void exitMoving();
	void sendMovingmsg();

	// when dead
	void sendDeadMsg();


	//stoped
	bool isTargetNoAvailable(ENTITY_ID attackerId);

protected:
	int mCurWayPointIndex;
	const std::vector<WayPointEx>* mWayPoints;
	eActiveObjTag mCurEnemyTag;

protected:

	//eEnemyStatus mCurStatus;
	ENTITY_ID mTargetID;
	CCRect mTargetCollisionRect;
	std::map<ENTITY_ID, CCRect> mAttackers;
};



//typedef void (Tower::*SEL_MenuTouchedFunc)(int);

//#define towerMenuCallFunc(func) (SEL_MenuTouchedFunc)(&func)


#endif