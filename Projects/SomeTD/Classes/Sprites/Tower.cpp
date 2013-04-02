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
#include "../Managers/AlliesManager.h"
#include "Bullet.h"
using namespace cocos2d;
Tower* Tower::create()
{
	Tower *tower = new Tower();
	auto initFrame = TowerInformation::getInstance()->getTowerFrame(Tower_Mage_LV1);
	if (tower && tower->initWithSpriteFrame(initFrame))//备注1
	{
		//tower->loadResource();
		tower->autorelease();
		//CCLog("tower: %d", tower->retainCount());
		return tower;
	}
	CC_SAFE_DELETE(tower);
	return NULL;

}

void Tower::myInit(eTower_Terrain terrain, CCSpriteBatchNode* batchNode)
{
	mTargetID = -1;

	mTowerType = Tower_None;
	mShooterTypeUp = Shooter_None;
	mShooterTypeUpPart2 = Shooter_None;
	mShooterTypeDown = Shooter_None;
	mShooterTypeDownPart2 = Shooter_None;
	mTerrainType = terrain;
	mCanFire = false;
	mCurAnimationIndex = 0;
	mCurPassedFrames = 0;
	mFramesInterval = 1;
	mShootWhen = 8;
	mReloadTime = 0.2f;
	mReloadElapsed = 0.0f;
	mAttackRange = 200;

	mBatchNode = batchNode;
	
	for(int i = 0; i < 3; ++i)
	{
		mSoldiers[i] = -1;

	}
	TowerInformation* towerInfo = TowerInformation::getInstance();

	//this->mShooter = CCSprite::createWithSpriteFrame(towerInfo->GetShooterFrame(TOWER_SHOOTER_TYPE::Shooter_Mage_LV_1To3_Down));
	//this->addChild(this->mShooter, 1);
	//this->mShooter->setPosition(CCPoint(48, 64));
	this->mShooter = NULL;


	//Terrain
	mTerrain = CCSprite::createWithSpriteFrame(towerInfo->getTerrainFrame(terrain));
	this->addChild(mTerrain, -1);
	CCSize towerSize = this->getContentSize();
	CCSize terrainSize = this->getContentSize();
	mTerrain->setPosition(CCPoint(94/2, 30));
	this->setOpacity(0);

	//Range Sprite
	mRangeSprite = CCSprite::createWithSpriteFrame(towerInfo->getTowerRange());
	this->addChild(this->mRangeSprite);
	mRangeSprite->setPosition(CCPoint(towerSize.width / 2, towerSize.height /2));
	mRangeSprite->setVisible(false);

	float scale = mAttackRange / (mRangeSprite->getContentSize().width / 2);
	mRangeSprite->setScale(scale);

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
	case Tower_Mage_LV1:
		{
			mLv = TowerMenu::eMenu_Level::Lv1_Mage;
		}
		break;
	case Tower_Mage_LV2:
		{

			mLv = TowerMenu::eMenu_Level::Lv2_Mage;
		}
		break;
	case Tower_Mage_LV3:
		{

			mLv = TowerMenu::eMenu_Level::Lv3_Mage;
		}
		break;
	case Tower_Mage_LV4_Arcane:
		{

			mLv = TowerMenu::eMenu_Level::Lv4_Mage_Arcane;
		}
		break;
	case Tower_Mage_LV4_Sorcerer:
		{

			mLv = TowerMenu::eMenu_Level::Lv4_Mage_Sorcerer;
		}
		break;
	case Tower_barrack_LV1:
		{
			mLv = TowerMenu::eMenu_Level::Lv1_Barrack;
		}
		break;
	case Tower_barrack_LV2:
		{

			mLv = TowerMenu::eMenu_Level::Lv2_Barrack;
		}
		break;
	case Tower_barrack_LV3:
		{

			mLv = TowerMenu::eMenu_Level::Lv3_Barrack;
		}
		break;
	case Tower_barrack_LV4_paladins:
		{

			mLv = TowerMenu::eMenu_Level::Lv4_Barrack_Paladins;
		}
		break;
	case Tower_barrack_LV4_barbarians:
		{

			mLv = TowerMenu::eMenu_Level::Lv4_Barrack_Barbarians;
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
			this->mTowerType = Tower_barrack_LV1;
			this->mShooterTypeUp = Shooter_None;
			this->mShooterTypeUpPart2 = Shooter_None;
			this->mShooterTypeDown = Shooter_None;
			this->mShooterTypeDownPart2 = Shooter_None;
			this->BuildTower();
		}
		break;
	case TowerMenu::MageChecked:
		{
			CCLog("TowerMenu::MageChecked");
			this->showPreivew(true, Tower_Preview_Mage);
			//this->showRange(true);
		}
		break;
	case TowerMenu::MageConfirmed:
		{
			CCLog("TowerMenu::MageConfirmed");
			this->mTowerType = Tower_Mage_LV1;
			this->mShooterTypeUp = Shooter_Mage_LV_1To3_Up;
			this->mShooterTypeUpPart2 = Shooter_Mage_LV_1To3_Up_Part2;
			this->mShooterTypeDown = Shooter_Mage_LV_1To3_Down;
			this->mShooterTypeDownPart2 = Shooter_Mage_LV_1To3_Down_Part2;
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
			this->upgradeTower('\0');
		}
		break;
	case TowerMenu::SpecialLeftChecked:
		{
			CCLog("SpecialLeftChecked");
			this->showRange(true);
		}
		break;
	case TowerMenu::SpecialLeftConfirmed:
		{
			CCLog("SpecialLeftConfirmed");
			this->upgradeTower('l');
		}
		break;
	case TowerMenu::SpecialRightChecked:
		{
			CCLog("SpecialLeftChecked");
			this->showRange(true);
		}
	case TowerMenu::SpecialRightConfirmed:
		{
			CCLog("SpecialRightConfirmed");
			this->upgradeTower('r');
		}
		break;
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

	// deal with Barrack
	if(mTowerType & 0x00F000F0)
	{
		this->mCanFire = false;
		this->scheduleUpdate();
		CCPoint pos = this->getPosition();
		CCPoint massPos = CCPoint(pos.x, pos.y - 100);
		this->setMassPos(massPos);

		for(int i = 0; i < 3;++ i)
		{
			auto ally = AllyManager::sharedAllyManager()->addAllyAndGetReadyForFight("soldier_lvl4_paladin", pos);
			ally->moveTo(mSoldiersMassPos[i]);
		}
		return;
	}

	if(this->mShooter)
	{
		this->mShooter->release();
	}

	this->mShooter = CCSprite::createWithSpriteFrame(tInfo->getShooterFrame((eTower_Shooter)this->mShooterTypeDown));
	this->addChild(this->mShooter, 1);
	this->mShooter->setPosition(CCPoint(47, 67));
	this->mCanFire = true;
	this->scheduleUpdate();
}


void Tower::upgradeTower(const char special)
{
	switch (this->mTowerType)
	{
	case Tower_Mage_LV1:
		{
			this->mTowerType = Tower_Mage_LV2;
		}
		break;
	case Tower_Mage_LV2:
		{
			this->mTowerType = Tower_Mage_LV3;
		}
		break;	
	case Tower_Mage_LV3:
		{
			if(special == 'l')
			{
				this->mTowerType = Tower_Mage_LV4_Arcane;
			}

			else if(special == 'r')
			{
				this->mTowerType = Tower_Mage_LV4_Sorcerer;
			}
		}
		break;
	case Tower_barrack_LV1:
		{
			this->mTowerType = Tower_barrack_LV2;
		}
		break;
	case Tower_barrack_LV2:
		{
			this->mTowerType = Tower_barrack_LV3;
		}
		break;	
	case Tower_barrack_LV3:
		{
			if(special == 'l')
			{
				this->mTowerType = Tower_barrack_LV4_barbarians;
			}

			else if(special == 'r')
			{
				this->mTowerType = Tower_barrack_LV4_paladins;
			}
		}
		break;
	default:
		return;
	}




	TowerInformation* tInfo = TowerInformation::getInstance();
	this->setDisplayFrame(tInfo->getTowerFrame(this->mTowerType));
	this->setOpacity(255);

	// special tower only 
	if( (this->mTowerType & 0xFFFF0000) && !(mTowerType & 0x00F000F0))
	{
		if(this->mShooter)
		{
			this->mShooter->release();
		}

		this->mShooter = CCSprite::createWithSpriteFrame(tInfo->getShooterFrame((eTower_Shooter)this->mShooterTypeDown));
		this->addChild(this->mShooter, 1);
		this->mShooter->setPosition(CCPoint(48, 64));
		this->mCanFire = true;
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
	this->mRangeSprite->setVisible(isShow);
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
	// deal with barrack
	if (mTowerType & 0x00F000F0)
	{
		return;
	}
	else
	{
		if(this->mCanFire)
		{
			if(this->mReloadElapsed < this->mReloadTime)
			{
				this->mReloadElapsed += dt;
				return;
			}
			// if no target, we get one 
			if (this->mTargetID == -1)
			{
				long target = EnemyManager::sharedEnemyManager()->getEnemyInRange(this->getPosition(), mAttackRange);
				if(target != -1)
					this->mTargetID = target;
			}
			else
			{
				// if there's a target, available check 
				if(!EnemyManager::sharedEnemyManager()->isEnemyInRange(this->getPosition(), mAttackRange, mTargetID))
				{
					long target = EnemyManager::sharedEnemyManager()->getEnemyInRange(this->getPosition(), mAttackRange);
					//CCLog("tower get new target: %d", target);
					this->mTargetID = target;
				}
			}
			if(this->mTargetID != -1)
				this->fire();
		}
		else
		{
			this->firing();
		}
	}



}

void Tower::firing()
{
	auto tInfo = TowerInformation::getInstance();

	std::vector<CCSpriteFrame*>* shooterFrames = tInfo->getShooterAnimation(this->mShooterTypeDown);
	std::vector<CCSpriteFrame*>* towerFrames = tInfo->getTowerAnimation(this->mTowerType);
	int framesCount = towerFrames->size();



	if(this->mCurAnimationIndex > framesCount)
	{
		this->mCanFire = true;
		this->mReloadElapsed = 0;
		// restore frame
		this->mShooter->setDisplayFrame(tInfo->getShooterFrame(this->mShooterTypeDown));
		this->setDisplayFrame(tInfo->getTowerFrame(this->mTowerType));
		return;
	}

	// deal with frame interval 
	if (this->mCurPassedFrames % this->mFramesInterval == 0)
	{
		if(this->mCurAnimationIndex < framesCount)
		{
			CCSpriteFrame* frame = shooterFrames->at(this->mCurAnimationIndex);
			if(frame != nullptr)
				this->mShooter->setDisplayFrame(frame);
			frame = towerFrames->at(this->mCurAnimationIndex);
			if(frame != nullptr)
				this->setDisplayFrame(frame);

			// deal with shoot frame
			if (this->mCurAnimationIndex == this->mShootWhen)
				this->onShoot();
		}
		++this->mCurAnimationIndex;
	}
	++this->mCurPassedFrames;


}

void Tower::fire()
{
	this->mCanFire = false;
	this->mCurAnimationIndex = 0;
	this->mCurPassedFrames = 0;
	this->mFramesInterval = 2;
	this->mShootWhen = 8;
	//CCLog("Tower::fire()");
	//this->canFire = false;
	////this->mShooter->runAction(CCAnimate::create(TowerInformation::GetInstance()->GetShooterAnimation(TOWER_SHOOTER_TYPE::Shooter_Mage_LV_1To3_Down_Part2)));
	//TowerInformation* tInfo = TowerInformation::getInstance();
	//CCSequence* firecallback = CCSequence::create(
	//	CCDelayTime::create(SECOND_PER_FRAME * 8 * 2),
	//	CCCallFuncN::create(this, callfuncN_selector(Tower::onShoot)),
	//	CCDelayTime::create(0.5),
	//	CCCallFunc::create(this, callfunc_selector(Tower::onFired)),
	//	NULL
	//);
	//CCSequence* towerAnimCallback = CCSequence::create(
	//	CCAnimate::create(tInfo->getTowerAnimation(this->mTowerType)),
	//	NULL
	//);
	//
	//CCSpawn* spawn = CCSpawn::create(
	//	CCAnimate::create(tInfo->getShooterAnimation(Shooter_Mage_LV_1To3_Down)),
	//	firecallback, 
	//	//towerAnimCallback,
	//	NULL
	//	);
	//
	//this->mShooter->runAction(
	//	spawn
	//	);
	//
	//CCAnimation* aa = tInfo->getTowerAnimation(this->mTowerType);
	//
	//this->runAction(CCAnimate::create(aa));
}

void Tower::onShoot()
{

	//CCLog("Tower::onShoot()");
	static bool first = true;

	//if(first)
	//{
	auto bullet = Bullet::create();
	//	first = false;
	//}



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

	bullet->setPosition(bulletPos);
	//bullet->setScale(0.25);
	//this->getParent()->addChild(this->testBullet);
	// 
	// check if target is still available, if not, get one.
	if(!EnemyManager::sharedEnemyManager()->isEnemyInRange(this->getPosition(), mAttackRange, mTargetID))
	{
		long target = EnemyManager::sharedEnemyManager()->getEnemyInRange(this->getPosition(), mAttackRange);
		//CCLog("tower get new target: %d when shooting", target);
		mTargetID = target;
	}
	if (mTargetID != -1)
	{
		bullet->reuse(100, EnemyManager::sharedEnemyManager()->getAvailableEnemy(mTargetID), CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("magebolt_0002.png"));

		mBatchNode->addChild(bullet);
	}

	//else
	//CCLog("no target in range when shooting, fire cancle!");
}

void Tower::setMassPos(const CCPoint& pos)
{
	mSoldiersMassPos[0] = CCPoint(pos.x - 30, pos.y);
	mSoldiersMassPos[1] = CCPoint(pos.x , pos.y);
	mSoldiersMassPos[2] = CCPoint(pos.x + 30, pos.y);
}