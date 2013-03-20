
#ifndef _ENEMY_
#define _ENEMY_

#include "cocos2d.h"
#include "Bullet.h"
#include "../Model/Enumeration.h"
using namespace cocos2d;

//Tower class


class Enemy : public CCSprite , public CCTouchDelegate
{

public:
	static Enemy* create(const char* pszSpriteFrameName);

public:
public:
	virtual ~Enemy(){}

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
	CCRect getCollisionRect();

	void FollowPath(CCNode* sender);

	void run(std::vector<WayPoint>& wayPoints);

	void run(std::vector<WayPoint>& wayPoints, float duration, float tension);

public:
	void loadResource(eTower_Terrain terrain);//自定义初始化函数

private:
	//void getNextLv(eTower)

private:
	int _wayPointIndex;
	int _wayPointCount;
	std::vector<WayPoint> mWayPoints;
	//eTower_Preview mPreviewType;
	
	//CCSequence* mShooterAnimationSequence;
	//CCSequence* mTowerAnimationSequence;
private:
	/*
	 相关的精灵对象
	 */
	CCSprite* mShooter;
	CCSprite* mTerrain;
	CCSprite* mTarget;
	CCSprite* mRange;
private:

	float _speed;
	CCPoint _targetLastPosition;
	CCSprite* _target;
	char temp[256];
	Bullet* testBullet;
	bool canFire;
};



//typedef void (Tower::*SEL_MenuTouchedFunc)(int);

//#define towerMenuCallFunc(func) (SEL_MenuTouchedFunc)(&func)


#endif