
#ifndef _BULLET_H_
#define _BULLET_H_

#include "cocos2d.h"

using namespace cocos2d;

class Bullet : public CCSprite , public CCTouchDelegate
{

public:
	// 静态初始化方法
	//static Bullet* create(BulletInfoModel* pBulletTag);
	static Bullet* create(float speed, CCSprite* target, const char* spName);//静态创建（内存自动释放）
	// 带偏转角度的静态初始化方法
	//static Bullet* createWithRotation(BulletInfoModel* pBulletTag, float pRotation);

public:
public:
	void myInit(float speed, CCSprite* target);//自定义初始化函数
	virtual ~Bullet(){}

	//重写触屏相关函数----
	virtual void onEnter();
	virtual void onExit();
	//virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event){}
	virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);


public:
	void update(float dt); // execute every frame
	bool isHit(); //when bullet hit target
	void destory();
	void reuse();
	CCRect getCollisionRect();
private:
	float _speed;
	CCPoint _targetLastPosition;
	CCSprite* _target;
	char temp[256];
};

#endif
