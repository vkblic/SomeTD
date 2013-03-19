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
#include "../Managers/EnemyManager.h"
#include "Bullet.h"
using namespace cocos2d;
Tower* Tower::create()
{
	Tower *tower = new Tower();
	auto initFrame = TowerInformation::getInstance()->getTowerFrame(eTower::Tower_Mage_LV1);
	if (tower && tower->initWithSpriteFrame(initFrame))//备注1
	{
		//tower->loadResource();
		tower->autorelease();
		CCLog("tower: %d", tower->retainCount());
		return tower;
	}
	CC_SAFE_DELETE(tower);
	return NULL;

}


bool Tower::ccTouchBegan(CCTouch* touch, CCEvent* event)
{

	//CCLog("Tower::ccTouchBegan(CCTouch* touch, CCEvent* event)");
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
	TowerMenu::eMenu_Level mLv = TowerMenu::eMenu_Level::Lv0;
	switch (this->mTowerType)
	{
	case eTower::Tower_Mage_LV1:
		{
			mLv = TowerMenu::eMenu_Level::Lv1_Mage;
		}
		break;
	case eTower::Tower_Mage_LV2:
		{

			mLv = TowerMenu::eMenu_Level::Lv2_Mage;
		}
		break;
	case eTower::Tower_Mage_LV3:
		{

			mLv = TowerMenu::eMenu_Level::Lv3_Mage;
		}
		break;
	case eTower::Tower_Mage_LV4_Arcane:
		{

			mLv = TowerMenu::eMenu_Level::Lv1_Mage;
		}
	case eTower::Tower_Mage_LV4_Sorcerer:
		{

			mLv = TowerMenu::eMenu_Level::Lv1_Mage;
		}
		break;
	default:
		break;
	}

	menu->sharedTowerMenu()->showMenu(this->getPosition(), mLv, this, towerMenuCallFunc(Tower::onMenuSelected));


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

void Tower::myInit(eTower_Terrain terrain)
{
	this->mTarget = NULL;

	this->mTowerType = eTower::Tower_None;
	this->mShooterTypeUp = eTower_Shooter::Shooter_None;
	this->mShooterTypeUpPart2 = eTower_Shooter::Shooter_None;
	this->mShooterTypeDown = eTower_Shooter::Shooter_None;
	this->mShooterTypeDownPart2 = eTower_Shooter::Shooter_None;
	this->mTerrainType = terrain;
	this->canFire = false;
	TowerInformation* towerInfo = TowerInformation::getInstance();

	//this->mShooter = CCSprite::createWithSpriteFrame(towerInfo->GetShooterFrame(TOWER_SHOOTER_TYPE::Shooter_Mage_LV_1To3_Down));
	//this->addChild(this->mShooter, 1);
	//this->mShooter->setPosition(CCPoint(48, 64));
	this->mShooter = NULL;


	//Terrain
	this->mTerrain = CCSprite::createWithSpriteFrame(towerInfo->getTerrainFrame(terrain));
	this->addChild(this->mTerrain, -1);
	CCSize towerSize = this->getContentSize();
	CCSize terrainSize = this->getContentSize();
	this->mTerrain->setPosition(CCPoint(94/2, 30));
	this->setOpacity(0);

	//Range Sprite
	this->mRange = CCSprite::createWithSpriteFrame(towerInfo->getTowerRange());
	this->addChild(this->mRange);
	this->mRange->setPosition(CCPoint(towerSize.width / 2, towerSize.height /2));
	this->mRange->setVisible(false);

	float scale = 200 / (this->mRange->getContentSize().width / 2);
	this->mRange->setScale(scale);




}

void Tower::onMenuSelected(int type)
{
	TowerMenu::MenuItemTag tag = (TowerMenu::MenuItemTag)type;
	switch (tag)
	{
	case TowerMenu::NonTouched:
		{
			CCLog("TowerMenu::NonTouched");
			this->showPreivew(false, Tower_Preview_None);
			this->showRange(false);
		}
		break;
	case TowerMenu::ArcherChecked:
		{
			CCLog("TowerMenu::ArcherChecked");
			this->showPreivew(true, Tower_Preview_Archer);
			this->showRange(true);
		}
		break;
	case TowerMenu::ArcherConfirmed:
		{
			CCLog("TowerMenu::ArcherConfirmed");
		}
		break;
	case TowerMenu::BarrackChecked:
		{
			CCLog("TowerMenu::BarrackChecked");
			this->showPreivew(true, Tower_Preview_Barrack);
			this->showRange(true);
		}
		break;
	case TowerMenu::BarrackComfirmed:
		{
			CCLog("TowerMenu::BarrackComfirmed");
		}
		break;
	case TowerMenu::MageChecked:
		{
			CCLog("TowerMenu::MageChecked");
			this->showPreivew(true, Tower_Preview_Mage);
			this->showRange(true);
		}
		break;
	case TowerMenu::MageConfirmed:
		{
			CCLog("TowerMenu::MageConfirmed");
			this->mTowerType = eTower::Tower_Mage_LV1;
			this->mShooterTypeUp = eTower_Shooter::Shooter_Mage_LV_1To3_Up;
			this->mShooterTypeUpPart2 = eTower_Shooter::Shooter_Mage_LV_1To3_Up_Part2;
			this->mShooterTypeDown = eTower_Shooter::Shooter_Mage_LV_1To3_Down;
			this->mShooterTypeDownPart2 = eTower_Shooter::Shooter_Mage_LV_1To3_Down_Part2;
			this->BuildTower();
		}
		break;
	case TowerMenu::ArtilleryChecked:
		{
			CCLog("TowerMenu::ArtilleryChecked");
			this->showPreivew(true, Tower_Preview_Artillery);
			this->showRange(true);
		}
		break;
	case TowerMenu::ArtilleryConfirmed:
		{
			CCLog("TowerMenu::ArtilleryConfirmed");
		}
		break;
	case TowerMenu::UpgradeChecked:
		{
			CCLog("TowerMenu::UpgradeChecked");
			this->showRange(true);
		}
		break;
	case TowerMenu::UpgradeConfirmed:
		{
			CCLog("TowerMenu::UpgradeConfirmed");
			this->upgradeTower();
		}
		break;
	case TowerMenu::SpecialLeftChecked:
		CCLog("SpecialLeftChecked");
		break;
	case TowerMenu::SpecialLeftConfirmed:
		CCLog("SpecialLeftConfirmed");
		break;
	case TowerMenu::SpecialRightChecked:
		CCLog("SpecialRightChecked");
		break;
	case TowerMenu::SpecialRightConfirmed:
		CCLog("SpecialRightConfirmed");
		break;
	default:
		break;
	}
}


void Tower::BuildTower()
{
	TowerInformation* tInfo = TowerInformation::getInstance();
	this->setDisplayFrame(tInfo->getTowerFrame(this->mTowerType));
	this->setOpacity(255);
	if(this->mShooter)
	{
		this->mShooter->release();
	}

	this->mShooter = CCSprite::createWithSpriteFrame(tInfo->getShooterFrame((eTower_Shooter)this->mShooterTypeDown));
	this->addChild(this->mShooter, 1);
	this->mShooter->setPosition(CCPoint(48, 64));
	this->canFire = true;
	this->scheduleUpdate();
}


void Tower::upgradeTower()
{

	switch (this->mTowerType)
	{
	case eTower::Tower_Mage_LV1:
		{
			this->mTowerType = eTower::Tower_Mage_LV2;
		}
		break;
	case eTower::Tower_Mage_LV2:
		{
			this->mTowerType = eTower::Tower_Mage_LV3;
		}
		break;	
	case eTower::Tower_Mage_LV3:
		{
			this->mTowerType = eTower::Tower_Mage_LV1;
		}
		break;
	default:
		break;
	}




	TowerInformation* tInfo = TowerInformation::getInstance();
	this->setDisplayFrame(tInfo->getTowerFrame(this->mTowerType));
	this->setOpacity(255);

	// special tower with 
	if( this->mTowerType & 0xFFFF0000)
	{
		if(this->mShooter)
		{
			this->mShooter->release();
		}

		this->mShooter = CCSprite::createWithSpriteFrame(tInfo->getShooterFrame((eTower_Shooter)this->mShooterTypeDown));
		this->addChild(this->mShooter, 1);
		this->mShooter->setPosition(CCPoint(48, 64));
		this->canFire = true;
	}

}
void Tower::showPreivew(bool isShow, eTower_Preview towerType)
{
	if(!isShow)
	{
		if(this->mTowerType)
		{
			TowerInformation* towerInfo = TowerInformation::getInstance();
			this->setDisplayFrame(towerInfo->getTowerFrame(this->mTowerType));
			this->setOpacity(255);
		}
		else
			this->setOpacity(0);
		return;
	}
	TowerInformation* towerInfo = TowerInformation::getInstance();
	this->setDisplayFrame(towerInfo->getTowerPreviewFrame(towerType));
	this->setOpacity(180);
}

void Tower::showRange(bool isShow)
{
	this->mRange->setVisible(isShow ? true : true);
}


void Tower::update(float dt)
{
	static float dtMin = 0;
	static float total = 0;
	total += dt;
// 	if (total > 20)
// 		return ;
	if (dtMin > 0.1)
	{
		//CCLog("Tower::update");
		dtMin = 0 ;
	}
	else
	{
		dtMin += dt;
		//return;
	}
	if(this->canFire)
	{
		if (this->mTarget == NULL)
		{
			auto pos = this->getPosition();
			auto target = EnemyManager::sharedEnemyManager()->getEnemyInRange(pos, 100);
			if (target == NULL)
				return ;

			CCLog("tower get new target");
			this->mTarget = target;
		}
		this->fire();
	}
	else
	{
		if (this->mTarget == NULL)
		{
			return ;
			CCLog("no target!");
		}
		auto pos = this->getPosition();
		if (!EnemyManager::sharedEnemyManager()->isEnemyInRange(pos, 100, this->mTarget))
		{
			CCLog("target out of range!");
			this->mTarget = NULL;
		}
		else
		{
			//CCLog("target still in range!");
		}
	}

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


void Tower::fire()
{
	CCLog("Tower::fire()");
	this->canFire = false;
	//this->mShooter->runAction(CCAnimate::create(TowerInformation::GetInstance()->GetShooterAnimation(TOWER_SHOOTER_TYPE::Shooter_Mage_LV_1To3_Down_Part2)));
	TowerInformation* tInfo = TowerInformation::getInstance();
	CCSequence* firecallback = CCSequence::create(
		CCDelayTime::create(SECOND_PER_FRAME * 8 * 2),
		CCCallFuncN::create(this, callfuncN_selector(Tower::onShoot)),
		CCDelayTime::create(0.5),
		CCCallFunc::create(this, callfunc_selector(Tower::onFired)),
		NULL
	);
	CCSequence* towerAnimCallback = CCSequence::create(
		CCAnimate::create(tInfo->getTowerAnimation(this->mTowerType)),
		NULL
	);

	CCSpawn* spawn = CCSpawn::create(
		CCAnimate::create(tInfo->getShooterAnimation(eTower_Shooter::Shooter_Mage_LV_1To3_Down)),
		firecallback, 
		//towerAnimCallback,
		NULL
		);

	this->mShooter->runAction(
		spawn
		);

	CCAnimation* aa = tInfo->getTowerAnimation(this->mTowerType);

	this->runAction(CCAnimate::create(aa));
}

void Tower::onShoot(CCNode* shooter)
{

	CCLog("Tower::onShoot()");
	static bool first = true;

	if(first)
	{
		this->testBullet = Bullet::create(100, this->mTarget, "magebolt_0002.png");
		this->getParent()->addChild(this->testBullet);
		first = false;
	}



	//this->testBullet = Bullet::create(100, this->mTarget, "magebolt_0002.png");
	CCPoint bulletPos;
	bulletPos.x = this->getPosition().x - this->getContentSize().width / 2
		//+ this->mTower->getPosition().x - this->mTower->getContentSize().width / 2
		+ this->mShooter->getPosition().x; //- this->mShooter->getContentSize().width / 2;
	//+ 18; // offset
	bulletPos.y = this->getPosition().y - this->getContentSize().height / 2
		//+ this->mTower->getPosition().y - this->mTower->getContentSize().height / 2
		+ this->mShooter->getPosition().y; //- this->mShooter->getContentSize().height / 2;
	//+ 23; // offset

	this->testBullet->setPosition(bulletPos);
	//bullet->setScale(0.25);
	//this->getParent()->addChild(this->testBullet);

	this->testBullet->reuse();
}

void Tower::onFired()
{
	CCLog("Tower::onFired()");
	this->canFire = true;
}