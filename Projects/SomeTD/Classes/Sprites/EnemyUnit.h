
#ifndef _ENEMY_UNIT_
#define _ENEMY_UNIT_

#include "cocos2d.h"
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

class EnemyUnit : public CCSprite , public CCTouchDelegate
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
	void update(float dt); // execute every frame

	CCPoint getControlPointAt(int index);

	CCRect getCollisionRect();

	//void run(std::vector<WayPointEx>& wayPoints);

	void run(const std::vector<WayPointEx>* wayPoints);

	void setID(int id){ this->mID = id; }
	 long getID() { return this->mID; }

	ActiveObjModel* getEnemyInfo() { return this->mEnemyInfo; }

public:
	void myInit();//自定义初始化函数


	/*
	 *
	 *
	 *
	 */
	void underAttack(int damage);

	void destory();
	void onDestoryed();
	void onArriveEndPoint();
	void targetAlert(long targetID) 
	{ 
		mTargetID = targetID;
		mCurStatus = EnemyStatus_WaitingForAttack; 
	}
	void startAttack();
	void attacking();
private:
	//void getNextLv(eTower)

	/*
	 *Set hp sprite position in enemy layer coordinate
	 *
	 */
	void setHpSpritePosition();


	
	void updateHpSpriteSize();

	//void fire(CCSprite* target);
	void onHit();

private:
	int mCurWayPointIndex;
	const std::vector<WayPointEx>* mWayPoints;
	eActiveObjTag mCurEnemyTag;
	//eTower_Preview mPreviewType;
	
	//CCSequence* mShooterAnimationSequence;
	//CCSequence* mTowerAnimationSequence;
private:
	CCSprite* mHp;
private:


	CCSpriteBatchNode* mHpBatchNode;
	ActiveObjModel* mEnemyInfo;

	//int mMaxHP;
	int mCurHP;
	long mID;
	eEnemyStatus mCurStatus;
	long mTargetID;
	CCRect mDefualtColorRect;
	float mHpBarMaxWidth;
};



//typedef void (Tower::*SEL_MenuTouchedFunc)(int);

//#define towerMenuCallFunc(func) (SEL_MenuTouchedFunc)(&func)


#endif