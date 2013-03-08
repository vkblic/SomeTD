//
//  Bullet.cpp
//  TileGameDemo
//
//  Created by kelyad on 02-17-2013.
//

#include "Tower.h"
#include "TowerMenu.h"
#include "../Helper/CommonHelpers.h"
#include "../Model/TowerInformation.h"
#include "Bullet.h"
#include "KCCMenuItemMoreFrame.h"
using namespace cocos2d;
Tower* Tower::create()
{
	Tower *tower = new Tower();
	auto initFrame = TowerInformation::GetInstance()->GetTowerFrame(TOWER_TYPE::Tower_Mage_LV1);
	if (tower && tower->initWithSpriteFrame(initFrame))//备注1
	{
		tower->myInit();
		tower->autorelease();

		return tower;
	}
	CC_SAFE_DELETE(tower);
	return NULL;

}


bool Tower::ccTouchBegan(CCTouch* touch, CCEvent* event)
{

// 	CCPoint touchPointUI = touch->getLocationInView();
// 
// 	CCLog("UI location, x: %f, y: %f", touchPointUI.x, touchPointUI.y);
// 
// 	CCPoint touchPointGL = touch->getLocation();
// 	CCLog("GL location, x: %f, y: %f", touchPointGL.x, touchPointGL.y);
// 
// 
// 	CCPoint touchPointInNodeSpace = this->convertTouchToNodeSpace(touch);
// 	CCLog("touchPointInNodeSpace, x: %f, y: %f", touchPointInNodeSpace.x, touchPointInNodeSpace.y);
// 
// 
// 	//bool isTouched = GetTouchableRect(this).containsPoint(touchPointGL);
// 	CCSize size = this->getContentSize();
// 	CCRect rect = CCRect(0, 0, size.width, size.height);
	bool isTouched = isSpriteTouched(this, touch);
// 	if (!isTouched)
// 		TowerMenu::sharedTowerMenu()->setVisible(false);
	return isTouched;
}

void Tower::ccTouchMoved(CCTouch* touch, CCEvent* event)
{

	//获取当前用户触屏点坐标并将3d坐标映射2d坐标系
	//CCPoint touchPoint = touch->locationInView( touch->view() );
	//touchPoint = CCDirector::sharedDirector()->convertToGL( touchPoint );

	//touchPoint.x, getPosition().y
	//if(touchPoint.x> CCDirector::sharedDirector()->getWinSize().width/2){
	//	CCLog("%s","精灵22~~ccTouchMoved");
	//}
}

void Tower::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	if (!isSpriteTouched(this, touch))
		return;
	TowerMenu *menu = TowerMenu::sharedTowerMenu();
	//this->mMenu->setPosition(CCPoint(this->getContentSize().width / 2, this->getContentSize().height / 2));
	menu->sharedTowerMenu()->showMenu(this->getPosition(), this, TowerMenu::Lv0);
	

	//CCLog("%s","精灵33~~~ccTouchEnded");
} 

//---SpriteClassModel 起始结束的生命周期函数----
void Tower::onEnter()
{
	//注册监听   1.dele类，2.优先级，3.YES为阻碍其他类的move 和 end

	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
	CCSprite::onEnter();
}

void Tower::onExit()
{
	//移除监听
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCSprite::onExit();
}



void Tower::myInit()
{
	this->mTowerType = Tower_Mage_LV1;
	this->mShooterTypeUp = Shooter_Mage_LV_1To3_Up;
	this->mShooterTypeUpPart2 = Shooter_Mage_LV_1To3_Up_Part2;
	this->mShooterTypeDown = Shooter_Mage_LV_1To3_Down;
	this->mShooterTypeDownPart2 = Shooter_Mage_LV_1To3_Down_Part2;
	this->mTerrainType = Terrain_MageLv1_3_Yellow;

	TowerInformation* towerInfo = TowerInformation::GetInstance();
	this->mShooter = CCSprite::createWithSpriteFrame(towerInfo->GetShooterFrame(TOWER_SHOOTER_TYPE::Shooter_Mage_LV_1To3_Down));
	this->mTerrain = CCSprite::createWithSpriteFrame(towerInfo->GetTerrainFrame(TOWER_TERRAIN_TYPE::Terrain_Build_DarkGray));

	this->addChild(this->mTerrain, -1);
	this->addChild(this->mShooter, 1);
	this->mShooter->setPosition(CCPoint(48, 64));
	CCSize towerSize = this->getContentSize();
	CCSize terrainSize = this->getContentSize();
	this->mTerrain->setPosition(CCPoint(94/2, 30));

	//Create Menu
	// 1.1. GameSetting button 
	// 
	//do 
	//{

		// Archer tower
// 		CCSprite* archerTowerMenuNormal = CCSprite::createWithSpriteFrameName("main_icons_0001.png");
// 		CCSprite* archerTowerMenuOff = CCSprite::createWithSpriteFrameName("main_icons_disabled_0001.png");
// 		CCSprite* archerTowerMenuDisabled = CCSprite::createWithSpriteFrameName("main_icons_off_0001.png");
// 
// 		KCCMenuItemMoreFrame * archerTowerBtn = KCCMenuItemMoreFrame::create(
// 			archerTowerMenuNormal,
// 			archerTowerMenuOff,
// 			archerTowerMenuDisabled,
// 			this,
// 			menu_selector(Tower::onTowerBuild)
// 			);
// 		if(! archerTowerBtn)
// 			break;
// 		archerTowerBtn->setTag(1);
// 		archerTowerBtn->setPosition(-49 + 74, 56 + 74);
// 		// Barrack Tower
// 		CCSprite* barrackTowerMenuNormal = CCSprite::createWithSpriteFrameName("main_icons_0002.png");
// 		CCSprite* barrackTowerMenuOff = CCSprite::createWithSpriteFrameName("main_icons_disabled_0002.png");
// 		CCSprite* barrackTowerMenuDisabled = CCSprite::createWithSpriteFrameName("main_icons_off_0002.png");
// 
// 		KCCMenuItemMoreFrame * barrackTowerBtn = KCCMenuItemMoreFrame::create(
// 			barrackTowerMenuNormal,
// 			barrackTowerMenuOff,
// 			barrackTowerMenuDisabled,
// 			this,
// 			menu_selector(Tower::onTowerBuild)
// 			);
// 		if(! barrackTowerBtn)
// 			break;
// 		barrackTowerBtn->setTag(2);
// 		barrackTowerBtn->setPosition(49 + 74, 56 + 74);
// 
// 
// 		//Mage Tower
// 		CCSprite* mageTowerMenuNormal = CCSprite::createWithSpriteFrameName("main_icons_0003.png");
// 		CCSprite* mageTowerMenuOff = CCSprite::createWithSpriteFrameName("main_icons_disabled_0003.png");
// 		CCSprite* mageTowerMenuDisabled = CCSprite::createWithSpriteFrameName("main_icons_off_0003.png");
// 
// 		KCCMenuItemMoreFrame * mageTowerBtn = KCCMenuItemMoreFrame::create(
// 			mageTowerMenuNormal,
// 			mageTowerMenuOff,
// 			mageTowerMenuDisabled,
// 			this,
// 			menu_selector(Tower::onTowerBuild)
// 			);
// 		if(! mageTowerBtn)
// 			break;
// 		mageTowerBtn->setTag(3);
// 		mageTowerBtn->setPosition(-49 + 74, -56 + 74);
// 
// 
// 		// Artillery Tower
// 		CCSprite* artilleryTowerMenuNormal = CCSprite::createWithSpriteFrameName("main_icons_0003.png");
// 		CCSprite* artilleryTowerMenuOff = CCSprite::createWithSpriteFrameName("main_icons_disabled_0003.png");
// 		CCSprite* artilleryTowerMenuDisabled = CCSprite::createWithSpriteFrameName("main_icons_off_0003.png");
// 
// 		KCCMenuItemMoreFrame * artilleryTowerBtn = KCCMenuItemMoreFrame::create(
// 			artilleryTowerMenuNormal,
// 			artilleryTowerMenuOff,
// 			artilleryTowerMenuDisabled,
// 			this,
// 			menu_selector(Tower::onTowerBuild)
// 			);
// 		if(! artilleryTowerBtn)
// 			break;
// 		artilleryTowerBtn->setTag(4);
// 		artilleryTowerBtn->setPosition(49 + 74, -56 + 74);
// 

		


		//this->getParent()->addChild(this->mMenu);


		//	this->_winSize = CCDirector::sharedDirector()->getWinSize();

	//} while (false);
	// animation sequence
	// 	this->mShooterAnimationSequence = CCSequence::create(
	// 		CCAnimate::create(TowerInformation::GetInstance()->GetShooterAnimation(TOWER_SHOOTER_TYPE::Shooter_Mage_LV_1To3_Down)),
	// 		CCCallFuncN::create(this, callfuncN_selector(Tower::onShoot)),
	// 		//CCAnimate::create(TowerInformation::GetInstance()->GetShooterAnimation(TOWER_SHOOTER_TYPE::Shooter_Mage_LV_1To3_Down_Part2)),
	// 		NULL);
	// 	this->mTowerAnimationSequence = CCSequence::create(
	// 		CCAnimate::create(TowerInformation::GetInstance()->GetTowerAnimation(TOWER_TYPE::Tower_Mage_LV1)),
	// 		NULL
	// 		);


}

void Tower::onTowerBuild(CCObject* pSender)
{

}

void Tower::update(float dt)
{
	// 	CCPoint pos = this->getPosition();
	// 	//pos.y -= this->mBulletInfo->BulletSpeed * dt;
	// 	this->setPositionY(pos.y);
	// 	if(this->isHit())
	// 	{
	// 		this->unscheduleUpdate();
	// 		//this->destory();
	// 		
	// 		CCSequence* sequence = CCSequence::createWithTwoActions(
	// 			CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName("magebolt_boom")),
	// 			CCCallFunc::create(this, callfunc_selector(Tower::destory))
	// 		);
	// 		this->runAction(sequence);
	// 	}
	// 	else
	// 	{
	// 		CCPoint pos = this->getPosition();
	// 		CCPoint targetPosNew = this->_target->getPosition();
	// 		//ccVertex2F toOldTarget = vertex2( this->_targetLastPosition.x - pos.x, this->_targetLastPosition.y - pos.y );
	// 
	// 		ccVertex2F toNewTarget = vertex2( targetPosNew.x - pos.x, targetPosNew.y - pos.y);
	// 		//ccVertex2F toNewPos = vertex2FAdd(toOldTarget, toNewTarget);
	// 		ccVertex2F toNewPos = vertex2FMul(&vertex2FNormalization(toNewTarget), dt * this->_speed * 5);
	// 		
	// 		//sprintf_s(temp,255, "%-08.4f",dt);
	// 		//CCLog(temp);
	// 		CCPoint newPos = CCPoint(pos.x + toNewPos.x, pos.y + toNewPos.y);
	// 		this->setPosition(newPos);
	// 
	// 		float angleRadians = atanf((float)toNewPos.y / (float)toNewPos.x);
	// 		float angleDegrees = CC_RADIANS_TO_DEGREES(angleRadians);
	// 		float cocosAngle = -1 * angleDegrees + 180;
	// 		this->setRotation(cocosAngle);
	// 
	// 	}
	//CCSpriteFrameCache.addSpriteFrame()
	// this->setPosition(ccpAdd(this->getPosition(), ccpMult(mVelocity, dt)));
}


void Tower::fire(CCSprite* target)
{
	this->mTarget = target;
	//this->mShooter->runAction(CCAnimate::create(TowerInformation::GetInstance()->GetShooterAnimation(TOWER_SHOOTER_TYPE::Shooter_Mage_LV_1To3_Down_Part2)));
	CCSequence* a = CCSequence::createWithTwoActions(
		CCDelayTime::create(SECOND_PER_FRAME * 8 * 2),
		CCCallFuncN::create(this, callfuncN_selector(Tower::onShoot)));


	CCSpawn* spawn = CCSpawn::create(
		CCAnimate::create(TowerInformation::GetInstance()->GetShooterAnimation(TOWER_SHOOTER_TYPE::Shooter_Mage_LV_1To3_Down)),
		a, NULL
		);

	this->mShooter->runAction(
		spawn
		);

	CCAnimation* aa = TowerInformation::GetInstance()->GetTowerAnimation(TOWER_TYPE::Tower_Mage_LV1);
	this->runAction(CCAnimate::create(aa));
}

void Tower::onShoot(CCNode* shooter)
{
	Bullet *bullet = Bullet::create(100, this->mTarget, "magebolt_0002.png");
	CCPoint bulletPos;
	bulletPos.x = this->getPosition().x - this->getContentSize().width / 2
		//+ this->mTower->getPosition().x - this->mTower->getContentSize().width / 2
		+ this->mShooter->getPosition().x; //- this->mShooter->getContentSize().width / 2;
	//+ 18; // offset
	bulletPos.y = this->getPosition().y - this->getContentSize().height / 2
		//+ this->mTower->getPosition().y - this->mTower->getContentSize().height / 2
		+ this->mShooter->getPosition().y; //- this->mShooter->getContentSize().height / 2;
	//+ 23; // offset

	bullet->setPosition(bulletPos);
	//bullet->setScale(0.25);
	this->getParent()->addChild(bullet);
	bullet->reuse();
}

void Tower::destory()
{

	this->setVisible(false);
}



