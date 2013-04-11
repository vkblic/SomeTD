
#ifndef _ACTIVE_ENTITY_
#define _ACTIVE_ENTITY_

#include "cocos2d.h"
#include "Entity.h"
#include "../Model/Models.h"
using namespace cocos2d;


class ActiveEntity : public Entity
{

public:
	static ActiveEntity* create(ActiveObjModel* enemyInfo, CCSpriteBatchNode* hpBatchNode);


public:
	CCRect getCollisionRect();
	ActiveObjModel* getEntityInfo() { return this->mEntityInfo; }

public:
	void myInit();//自定义初始化函数
protected:
	//void getNextLv(eTower)

	/*
	*Set hp sprite position in enemy layer coordinate
	*
	*/
	void setHpSpritePosition();



	void updateHpSpriteSize();


protected:

	CCSpriteBatchNode* mHpBatchNode;
	ActiveObjModel* mEntityInfo;

	CCSprite* mHp;
	int mCurHP;
	CCRect mDefualtColorRect;
	float mHpBarMaxWidth;

// States
protected:
	ActiveObj_States mState;
public: 
	void setState(ActiveObj_States state) { mState = state;}
	ActiveObj_States getState() { return mState; }
};



//typedef void (Tower::*SEL_MenuTouchedFunc)(int);

//#define towerMenuCallFunc(func) (SEL_MenuTouchedFunc)(&func)


#endif