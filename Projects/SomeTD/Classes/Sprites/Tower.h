
#ifndef _TOWER_H_
#define _TOWER_H_

#include "cocos2d.h"
#include "Bullet.h"
#include "../Model/Enumeration.h"
#include "../Sprites/AllyUnit.h"
using namespace cocos2d;

//Tower class


class Tower : public CCSprite , public CCTouchDelegate
{

public:
	static Tower* create();

public:
public:
	virtual ~Tower(){}

	//重写触屏相关函数----
	virtual void onEnter();
	virtual void onExit();
	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);


public:
	void update(float dt); // execute every frame

public:
	//Menu
	void onMenuSelected(int type);
	void myInit(eTower_Terrain terrain, CCSpriteBatchNode* batchNode);
	void setMassPos(const CCPoint& pos);
private:

	void BuildTower();
	void upgradeTower(const char special);
	void showPreivew(bool isShow, eTower_Preview towerType);
	void showRange(bool isShow, eTower towerType);
	void fire();
	void firing();
	void onShoot();
	//void getNextLv(eTower)




private:
	eTower mTowerType ;
	eTower_Shooter mShooterTypeUp;
	eTower_Shooter mShooterTypeUpPart2;
	eTower_Shooter mShooterTypeDown;
	eTower_Shooter mShooterTypeDownPart2;

	// allyUnit never remove by allyManager, when dead, just insert into 
	// "waiting for bring back to life " map.
	std::vector<AllyUnit*> mSoldiers;
	CCPoint mSoldiersMassPos[3];
	int mCurAnimationIndex;
	int mCurPassedFrames;
	CCSpriteBatchNode* mBatchNode;

	/*
	*shoot when animation frame index equal this value.
	*@range [0, frameCount - 1]
	*/
	int mShootWhen;

	/*
	*change display frame every x frame
	*@default: 1
	*@must >= 1
	*/
	int mFramesInterval;

	/*
	*time use for reload, or we can see fire interval time.
	*@unit: second
	*@range [0, max)
	*/
	float mReloadTime;


	/*
	*time already use for reload.
	*@unit: second
	*@range [0, mFireInterval)
	*/
	float mReloadElapsed;


	eTower_Terrain mTerrainType;
	//eTower_Preview mPreviewType;

	//CCSequence* mShooterAnimationSequence;
	//CCSequence* mTowerAnimationSequence;
private:
	/*
	相关的精灵对象
	*/
	CCSprite* mShooter;
	CCSprite* mTerrain;
	entity_id mTargetID;
	CCSprite* mRangeSprite;
	int mAttackRange;
private:

	bool mCanFire;

public:	
	bool mMassConfirm;
	void MassCommandCancle()
	{
		mMassConfirm = false;
		this->showRange(false, Tower_barrack_LV1);

	}

};



typedef void (Tower::*SEL_MenuTouchedFunc)(int);

#define towerMenuCallFunc(func) (SEL_MenuTouchedFunc)(&func)


#endif