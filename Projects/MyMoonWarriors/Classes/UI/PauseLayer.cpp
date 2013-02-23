//
//  PauseLayer.cpp
//  MoonWarriors-x
//
//  Created by Tom on 12-8-1.
//  Copyright (c) 2012Äê __MyCompanyName__. All rights reserved.
//

#include "PauseLayer.h"

PauseLayer::PauseLayer()
{
}

PauseLayer::~PauseLayer()
{
}

bool PauseLayer::init()
{
    bool ret = false;
    
    do {
        CC_BREAK_IF(!CCLayerColor::initWithColor(ccc4(255, 0, 0, 50)));
        
        CCArray *array = CCDirector::sharedDirector()->getRunningScene()->getChildren();
        CCObject *object = NULL;
        CCARRAY_FOREACH(array, object)
        {
            CCLayer *layer = (CCLayer*) object;
            layer->onExit();
        }
        
        ret = true;
    } while (0);
    
    return ret;
}

void PauseLayer::onEnter()
{
    CCLayerColor::onEnter();
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

void PauseLayer::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    CCLayerColor::onExit();
}

bool PauseLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCArray *array = CCDirector::sharedDirector()->getRunningScene()->getChildren();
    CCObject *object = NULL;
    CCARRAY_FOREACH(array, object)
    {
        CCLayer* layer = (CCLayer*) object;
        layer->onEnter();
    }
    
    this->removeFromParentAndCleanup(false);
    
    return true;
}

