//
//  Bullet.h
//  MoonWarriors-x
//
//  Created by Tom on 12-8-1.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef _SHIP_SPRITE_H_
#define _SHIP_SPRITE_H_

#include "cocos2d.h"
#include "../Model/Enumeration.h"
#include "../Model/InfoData.h"
#include "Bullet.h"

using namespace cocos2d;
class ShipSprite: public cocos2d::CCSprite
{
private:
	ShipSprite(){};
public:
	/** Create a sprite to enemy.
	 @Warning: 
	*/
	static ShipSprite* createWithShipInfo(EnemyInfoModel* enemyInfo);
	
	/** Destroy the "enemy sprite". **/
	void destroy();

	/** Calculate and let HP decrease when hit by bullte **/
	void getHit(BULLET_TYPE bulletType);

	/** Get collision rectangle for this sprite**/
	CCRect getCollisionRect();


protected:
	void shoot(float dt);
	virtual void update(float dt);
public:	 
	bool Active;
protected:
	EnemyInfoModel* mEnemyInfo;
	float _timeTick;
};

#endif
