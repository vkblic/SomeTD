//
//  GamePlayBGLayer.cpp
//  MoonWarriors-x
//
//  Created by Tom on 12-7-30.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "GamePlayBGLayer.h"

GamePlayBGLayer::GamePlayBGLayer()
{
}

GamePlayBGLayer::~GamePlayBGLayer()
{
}

bool GamePlayBGLayer::init()
{
    bool ret = false;
    
    do {
        CC_BREAK_IF(!CCLayer::init());
        
        initBackground();
        initScroll();
        
        ret = true;
    } while (0);
    
    return ret;
}

void GamePlayBGLayer::initBackground()
{
    // 远景层
    mVisionBGSprite = CCSprite::create("bg01.jpg");
    // 复制精灵，省去读取文件的步骤
    mVisionBGSpriteRe = CCSprite::createWithTexture(mVisionBGSprite->getTexture());
    // 获取远景层高度
    mVisionBGHeight = mVisionBGSprite->getContentSize().height - 1;
    // 设置标签(不是为了找到对应的精灵对象，而是为了区分远景层和近景层)
    mVisionBGSprite->setTag(GAMEPLAY_BG_VISION_LAYER);
    mVisionBGSpriteRe->setTag(GAMEPLAY_BG_VISION_LAYER);
    // 设置锚点为零点
    mVisionBGSprite->setAnchorPoint(CCPointZero);
    mVisionBGSpriteRe->setAnchorPoint(CCPointZero);
    // 设置位置，从下到上依次排列远景层和远景复制层
    mVisionBGSprite->setPosition(CCPointZero);
    mVisionBGSpriteRe->setPosition(ccp(0, mVisionBGHeight));
    
    this->addChild(mVisionBGSprite, 0);
    this->addChild(mVisionBGSpriteRe, 0);
    
    
    // 近景层(步骤同远景层)
    mCloseRangeBGTiledMap = CCTMXTiledMap::create("level01.tmx");
    mCloseRangeBGTiledMapRe = CCTMXTiledMap::create("level01.tmx");
    mCloseRangeBGTiledMap->setTag(GAMEPLAY_BG_CLOSE_RANGE_LAYER);
    mCloseRangeBGTiledMapRe->setTag(GAMEPLAY_BG_CLOSE_RANGE_LAYER);
    mCloseRangeBGHeight = mCloseRangeBGTiledMap->getContentSize().height - 1;
    mCloseRangeBGTiledMap->setPosition(CCPointZero);
    mCloseRangeBGTiledMapRe->setPosition(ccp(0, mCloseRangeBGHeight));
    
    this->addChild(mCloseRangeBGTiledMap, 1);
    this->addChild(mCloseRangeBGTiledMapRe, 1);
}

void GamePlayBGLayer::initScroll()
{
    scrollingToInfinity(mVisionBGSprite);
    scrollingToInfinity(mVisionBGSpriteRe);
    scrollingToInfinity(mCloseRangeBGTiledMap);
    scrollingToInfinity(mCloseRangeBGTiledMapRe);
}

void GamePlayBGLayer::scrollingToInfinity(cocos2d::CCNode *pSender )
{
    CCAction *scrollAction = NULL;
    // 根据远景层和近景层不同，执行不同的动作（考虑以后会有更多层，所以用switch）
    switch (pSender->getTag()) {
        case GAMEPLAY_BG_VISION_LAYER:
            // 判断位置，如果完全移动到屏幕之外，则排在当前显示层之上，循环使用
            if (pSender->getPositionY() <= -mVisionBGHeight) {
                pSender->setPosition(ccpAdd(pSender->getPosition(), ccp(0, 2 * mVisionBGHeight)));
            }
            scrollAction = CCSequence::create(CCMoveBy::create(15.0f, ccp(0, -mVisionBGHeight)), CCCallFuncN::create(this, callfuncN_selector(GamePlayBGLayer::scrollingToInfinity)), NULL);
            break;
        
        case GAMEPLAY_BG_CLOSE_RANGE_LAYER:
            if (pSender->getPositionY() <= -mCloseRangeBGHeight) {
                pSender->setPosition(ccpAdd(pSender->getPosition(), ccp(0, 2 * mCloseRangeBGHeight)));
            }
            scrollAction = CCSequence::create(CCMoveBy::create(12.0f, ccp(0, -mCloseRangeBGHeight)), CCCallFuncN::create(this, callfuncN_selector(GamePlayBGLayer::scrollingToInfinity)), NULL);
            break;
            
        default:
            CCAssert(0, "错误的游戏场景ID");
            break;
    }
    
    if (scrollAction) {
        pSender->runAction(scrollAction);
    }
}