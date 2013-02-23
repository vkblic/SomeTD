//
//  GamePlayScene.h
//  MoonWarriors-x
//
//  Created by Tom on 12-7-30.
//  Copyright (c) 2012Äê __MyCompanyName__. All rights reserved.
//

#ifndef MoonWarriors_x_GamePlayScene_h
#define MoonWarriors_x_GamePlayScene_h

#include "cocos2d.h"
#include "GamePlayBGLayer.h"
#include "GamePlayLayer.h"

USING_NS_CC;

class GamePlayScene: public CCScene
{
    
public:
    GamePlayScene();
    ~GamePlayScene();
    
    bool init();
    
    CREATE_FUNC(GamePlayScene);
    
};

#endif
