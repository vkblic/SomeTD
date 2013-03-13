
#ifndef _TOWER_H_
#define _TOWER_H_

#include "cocos2d.h"
#include "Bullet.h"
#include "../Model/Enumeration.h"
using namespace cocos2d;

//Tower class


class Tower : public CCSprite , public CCTouchDelegate
{

public:
	// 静态初始化方法
	//static Bullet* create(BulletInfoModel* pBulletTag);
	static Tower* create();//静态创建（内存自动释放）
	// 带偏转角度的静态初始化方法
	//static Bullet* createWithRotation(BulletInfoModel* pBulletTag, float pRotation);

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
	void destory();
	void fire(CCSprite* target);
	void onShoot(CCNode* shooter);

public:
	//Menu
	void onMenuSelected(int type);
	void loadResource(eTower_Terrain terrain);//自定义初始化函数

private:

	void BuildTower();
	void showPreivew(bool isShow);
	void showRange(bool isShow);

private:
	eTower mTowerType ;
	eTower_Shooter mShooterTypeUp;
	eTower_Shooter mShooterTypeUpPart2;
	eTower_Shooter mShooterTypeDown;
	eTower_Shooter mShooterTypeDownPart2;
	eTower_Terrain mTerrainType;
	eTower_Preview mPreviewType;
	
	//CCSequence* mShooterAnimationSequence;
	//CCSequence* mTowerAnimationSequence;
private:
	/*
	 相关的精灵对象
	 */
	CCSprite* mShooter;
	CCSprite* mTerrain;
	CCSprite* mTarget;
private:

	float _speed;
	CCPoint _targetLastPosition;
	CCSprite* _target;
	char temp[256];
	Bullet* testBullet;
	bool canFire;
};



typedef void (Tower::*SEL_MenuTouchedFunc)(int);

#define towerMenuCallFunc(func) (SEL_MenuTouchedFunc)(&func)


#endif