//
//  SettingScene.cpp
//  MoonWarriors-x
//
//  Created by Tom on 12-7-30.
//  Copyright (c) 2012Äê __MyCompanyName__. All rights reserved.
//

#include "SettingScene.h"

SettingScene::SettingScene()
{
}

SettingScene::~SettingScene()
{
}

bool SettingScene::init()
{
    bool ret = false;
    
    do {
        CC_BREAK_IF(!CCScene::init());
        
        this->addChild(SettingBGLayer::create(), 0);
        
        ret = true;
    } while (0);
    
    return ret;
}