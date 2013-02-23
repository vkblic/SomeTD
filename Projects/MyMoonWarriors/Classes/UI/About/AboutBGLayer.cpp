//
//  AboutBGLayer.cpp
//  MoonWarriors-x
//
//  Created by Tom on 12-7-30.
//  Copyright (c) 2012Äê __MyCompanyName__. All rights reserved.
//

#include "AboutBGLayer.h"

AboutBGLayer::AboutBGLayer()
{
}

AboutBGLayer::~AboutBGLayer()
{
}

bool AboutBGLayer::init()
{
    bool ret = false;
    
    do {
        CC_BREAK_IF(!CCLayer::init());
        
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        CCLabelTTF *label = CCLabelTTF::create("AboutScene", "", 32);
        label->setPosition(ccp(winSize.width / 2, winSize.height / 2));
        this->addChild(label);
        
        ret = true;
    } while (0);
    
    return ret;
}