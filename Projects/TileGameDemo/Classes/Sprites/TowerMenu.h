
#ifndef _TOWER_MENU_
#define _TOWER_MENU_

#include "cocos2d.h"

using namespace cocos2d;

class TowerMenu : public CCSprite , public CCTouchDelegate
{
public:	 
	enum MenuItemFrame
	{
		LockNormal,
		LockOff,
		LockDisabled,
		ArcherNormal,
		ArcherOff,
		ArcherDisabled,
		BarrackNormal,
		BarrackOff,
		BarrackDisabled,
		MageNormal,
		MageOff,
		MageDisabled,
		ArtilleryNormal,
		ArtilleryOff,
		ArtilleryDisabled,
		ComfirmNormal,
		ConfirmDisabled,
		MainFrameMax
	};
	enum MenuItemSprite
	{
		Archer,
		Barrack,
		Mage,
		Atillery,
		Upgrade,
		Sale,
		MenuItemSpriteMax
	};
public:
	// 静态初始化方法
	//static Bullet* create(BulletInfoModel* pBulletTag);
	static TowerMenu* create();//静态创建（内存自动释放）
	// 带偏转角度的静态初始化方法
	//static Bullet* createWithRotation(BulletInfoModel* pBulletTag, float pRotation);

public:
public:
	void myInit();//自定义初始化函数
	virtual ~TowerMenu(){}

	//重写触屏相关函数----
	virtual void onEnter();
	virtual void onExit();
	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);


public:
	void update(float dt); // execute every frame
	void onBuild(); //when bullet hit target
	void onUpgrade();
	void destory();
	
	CCRect getCollisionRect();
private:

	std::vector<CCSpriteFrame*> mMainMenuFrame;
	std::vector<CCSprite*> mMainMenuItem;
	float _speed;
	CCPoint _targetLastPosition;
	CCSprite* _target;
	char temp[256];
};

#endif
