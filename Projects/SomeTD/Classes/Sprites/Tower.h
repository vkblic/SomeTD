
#ifndef _TOWER_H_
#define _TOWER_H_

#include "cocos2d.h"
#include "Bullet.h"
#include "../Model/Enumeration.h"
#include "../Sprites/Enemy.h"
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
	void onFired();
	void fire();
	void onShoot(CCNode* shooter);

public:
	//Menu
	void onMenuSelected(int type);
	void myInit(eTower_Terrain terrain);//自定义初始化函数

private:

	void BuildTower();
	void upgradeTower();
	void showPreivew(bool isShow, eTower_Preview towerType);
	void showRange(bool isShow);
	//void getNextLv(eTower)

private:
	eTower mTowerType ;
	eTower_Shooter mShooterTypeUp;
	eTower_Shooter mShooterTypeUpPart2;
	eTower_Shooter mShooterTypeDown;
	eTower_Shooter mShooterTypeDownPart2;
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
	Enemy* mTarget;
	CCSprite* mRange;
private:

	Bullet* testBullet;
	bool canFire;
};



typedef void (Tower::*SEL_MenuTouchedFunc)(int);

#define towerMenuCallFunc(func) (SEL_MenuTouchedFunc)(&func)


#endif