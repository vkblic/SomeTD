
#ifndef _TOWER_H_
#define _TOWER_H_

#include "cocos2d.h"

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
	void myInit();//自定义初始化函数
	virtual ~Tower(){}

	//重写触屏相关函数----
	virtual void onEnter();
	virtual void onExit();
	//virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event){}
	virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);


public:
	void update(float dt); // execute every frame
	void destory();
	void fire(CCSprite* target);
	void onShoot(CCNode* shooter);
private:
	int mTowerType ;
	int mShooterTypeUp;
	int mShooterTypeUpPart2;
	int mShooterTypeDown;
	int mShooterTypeDownPart2;
	int mTerrainType;
	
	CCSequence* mShooterAnimationSequence;
	CCSequence* mTowerAnimationSequence;

	CCSprite* mShooter;
	CCSprite* mTerrain;
	CCSprite* mTarget;
	float _speed;
	CCPoint _targetLastPosition;
	CCSprite* _target;
	char temp[256];
};

#endif
