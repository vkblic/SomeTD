//
//  GamePlayBGLayer.h
//  MoonWarriors-x
//
//  Created by Tom on 12-7-30.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef MoonWarriors_x_GamePlayBGLayer_h
#define MoonWarriors_x_GamePlayBGLayer_h

#include "cocos2d.h"

USING_NS_CC;

typedef enum
{
    //
    GAMEPLAY_BG_NONE                = -1,
    // 远景层
    GAMEPLAY_BG_VISION_LAYER        = 0,
    // 近景层
    GAMEPLAY_BG_CLOSE_RANGE_LAYER   = 1,
} GAMEPLAY_BG;

class GamePlayBGLayer: public CCLayer
{
    
public:
    GamePlayBGLayer();
    ~GamePlayBGLayer();
    
    bool init();
    
    CREATE_FUNC(GamePlayBGLayer);
    
private:
    // 初始化背景
    void initBackground();
    // 初始化滚动
    void initScroll();
    // 无限背景滚动
    void scrollingToInfinity(CCNode *pBGLayer);
    
private:
    // 远景层（背景）
    CCSprite *mVisionBGSprite;
    // 远景重复层
    CCSprite *mVisionBGSpriteRe;
    // 远景层高度
    float mVisionBGHeight;
    
    // 近景层（地图）
    CCTMXTiledMap *mCloseRangeBGTiledMap;
    // 近景重复层
    CCTMXTiledMap *mCloseRangeBGTiledMapRe;
    // 近景层高度
    float mCloseRangeBGHeight;
    
};

#endif
