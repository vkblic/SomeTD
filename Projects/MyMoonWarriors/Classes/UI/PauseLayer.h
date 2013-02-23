//
//  PauseLayer.h
//  MoonWarriors-x
//
//  Created by Tom on 12-8-1.
//  Copyright (c) 2012Äê __MyCompanyName__. All rights reserved.
//

#ifndef MoonWarriors_x_PauseLayer_h
#define MoonWarriors_x_PauseLayer_h

#include "cocos2d.h"

USING_NS_CC;

class PauseLayer: public CCLayerColor
{
    
public:
    PauseLayer();
    ~PauseLayer();
    
    bool init();

    CREATE_FUNC(PauseLayer);
    
public:
    virtual void onEnter();
	virtual void onExit();
    
    // default implements are used to call script callback if exist
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    
private:
    CCScene *mGameScene;
    
};

#endif
