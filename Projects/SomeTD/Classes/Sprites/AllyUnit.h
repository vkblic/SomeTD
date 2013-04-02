
#ifndef _ALLY_UNIT_
#define _ALLY_UNIT_

#include "cocos2d.h"
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

class AllyUnit : public CCSprite , public CCTouchDelegate
{

public:
	static AllyUnit* create(ActiveObjModel* enemyInfo, CCSpriteBatchNode* hpBatchNode);

public:
public:
	virtual ~AllyUnit();

	//重写触屏相关函数----
	virtual void onEnter();
	virtual void onExit();
	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);


public:
	void update(float dt); // execute every frame

	CCRect getCollisionRect();

	//void run(std::vector<WayPointEx>& wayPoints);

	void run();
	void moveTo(const CCPoint& distPos);
	void onInPosition();
	void setID(int id){ this->mID = id; }
	 long getID() { return this->mID; }

	ActiveObjModel* getEnemyInfo() { return this->mAllyInfo; }

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
	void startAttack();
	void attacking();
	void onHit();
private:
	//void getNextLv(eTower)

	/*
	 *Set hp sprite position in enemy layer coordinate
	 *
	 */
	void setHpSpritePosition();


	
	void updateHpSpriteSize();


private:
	int mCurWayPointIndex;
	const std::vector<WayPointEx>* mWayPoints;
	eActiveObjTag mCurActiveObjTag;
	//eTower_Preview mPreviewType;
	
	//CCSequence* mShooterAnimationSequence;
	//CCSequence* mTowerAnimationSequence;
private:
	CCSprite* mHp;
	CCSpriteBatchNode* mHpBatchNode;
	ActiveObjModel* mAllyInfo;

	//int mMaxHP;
	int mCurHP;
	long mID;
	long mTargetID;
	eAllyStatus mCurStatus;
	CCRect mDefualtColorRect;
	float mHpBarMaxWidth;
};



//typedef void (Tower::*SEL_MenuTouchedFunc)(int);

//#define towerMenuCallFunc(func) (SEL_MenuTouchedFunc)(&func)


#endif