//
//  Bullet.cpp
//  TileGameDemo
//
//  Created by kelyad on 02-17-2013.
//

#include "TowerMenu.h"
#include "Tower.h"
#include "../Helper/CommonHelpers.h"
#include "../Helper/SpriteHelpers.h"
using namespace cocos2d;

TowerMenu* TowerMenu::mInstance = NULL;
TowerMenu* TowerMenu::sharedTowerMenu()
{
	if (TowerMenu::mInstance != NULL)
		return TowerMenu::mInstance;
	TowerMenu::mInstance = new TowerMenu();

	if (TowerMenu::mInstance && TowerMenu::mInstance->initWithSpriteFrameName("gui_ring.png"))//备注1
	{
		TowerMenu::mInstance->myInit();
		TowerMenu::mInstance->autorelease();

		return TowerMenu::mInstance;
	}
	CC_SAFE_DELETE(TowerMenu::mInstance);
	return NULL;

}

void TowerMenu::myInit()
{
	CCSpriteFrameCache* frameChache = CCSpriteFrameCache::sharedSpriteFrameCache();

	//Frames
	this->mMainMenuFrame.resize(eMenu_Frame::Menu_Frame_Max);
	this->mMainMenuFrame[eMenu_Frame::Archer_Normal] = frameChache->spriteFrameByName("main_icons_0001.png");
	this->mMainMenuFrame[eMenu_Frame::Archer_Off] = frameChache->spriteFrameByName("main_icons_off_0001.png");
	this->mMainMenuFrame[eMenu_Frame::Archer_Disabled] = frameChache->spriteFrameByName("main_icons_disabled_0001.png");

	this->mMainMenuFrame[eMenu_Frame::Barrack_Normal] = frameChache->spriteFrameByName("main_icons_0002.png");
	this->mMainMenuFrame[eMenu_Frame::Barrack_Off] = frameChache->spriteFrameByName("main_icons_off_0002.png");
	this->mMainMenuFrame[eMenu_Frame::Barrack_Disabled] = frameChache->spriteFrameByName("main_icons_disabled_0002.png");

	this->mMainMenuFrame[eMenu_Frame::Mage_Normal] = frameChache->spriteFrameByName("main_icons_0003.png");
	this->mMainMenuFrame[eMenu_Frame::Mage_Off] = frameChache->spriteFrameByName("main_icons_off_0003.png");
	this->mMainMenuFrame[eMenu_Frame::Mage_Disabled] = frameChache->spriteFrameByName("main_icons_disabled_0003.png");

	this->mMainMenuFrame[eMenu_Frame::Artillery_Normal] = frameChache->spriteFrameByName("main_icons_0004.png");
	this->mMainMenuFrame[eMenu_Frame::Artillery_Off] = frameChache->spriteFrameByName("main_icons_off_0004.png");
	this->mMainMenuFrame[eMenu_Frame::Artillery_Disabled] = frameChache->spriteFrameByName("main_icons_disabled_0004.png");

	this->mMainMenuFrame[eMenu_Frame::Upgrade_Normal] = frameChache->spriteFrameByName("main_icons_0005.png");
	this->mMainMenuFrame[eMenu_Frame::Upgrade_Off] = frameChache->spriteFrameByName("main_icons_off_0005.png");
	this->mMainMenuFrame[eMenu_Frame::Upgrade_Disabled] = frameChache->spriteFrameByName("main_icons_disabled_0005.png");
	

	this->mMainMenuFrame[eMenu_Frame::Comfirm_Normal] = frameChache->spriteFrameByName("main_icons_0019.png");
	this->mMainMenuFrame[eMenu_Frame::Confirm_Disabled] = frameChache->spriteFrameByName("main_icons_0020.png");

	this->mMainMenuFrame[eMenu_Frame::Sale_Normal] = frameChache->spriteFrameByName("ico_sell_0001.png");
	this->mMainMenuFrame[eMenu_Frame::Sale_Off] = frameChache->spriteFrameByName("ico_sell_off_0001.png");
	this->mMainMenuFrame[eMenu_Frame::Sale_Confirm] = frameChache->spriteFrameByName("ico_sell_0002.png");




	this->mMainMenuFrame[eMenu_Frame::Range_Circle] = frameChache->spriteFrameByName("range_circle.png");
	this->mMainMenuFrame[eMenu_Frame::Rally_Circle] = frameChache->spriteFrameByName("rally_circle.png");




	//Item
	this->mMainMenuItem.resize(eMenu_Sprite::Menu_Sprite_Max);
	this->mMainMenuItem[eMenu_Sprite::Bottom_Centre] = CCSprite::createWithSpriteFrameName("ico_sell_0001.png");
	this->mMainMenuItem[eMenu_Sprite::Bottom_Centre]->setPosition(CCPoint(74, - 56 + 74));
	this->mMainMenuItem[eMenu_Sprite::Bottom_Centre]->setVisible(false);
	this->mMainMenuItem[eMenu_Sprite::Top_Centre] = CCSprite::createWithSpriteFrameName("main_icons_0005.png");
	this->mMainMenuItem[eMenu_Sprite::Top_Centre]->setPosition(CCPoint(74, 56 + 74));
	this->mMainMenuItem[eMenu_Sprite::Top_Centre]->setVisible(false);
	this->mMainMenuItem[eMenu_Sprite::Top_Left] = CCSprite::createWithSpriteFrameName("main_icons_0001.png");
	this->mMainMenuItem[eMenu_Sprite::Top_Left]->setPosition(CCPoint(-49 + 74, 56 + 74));
	this->mMainMenuItem[eMenu_Sprite::Top_Right] = CCSprite::createWithSpriteFrameName("main_icons_0002.png");
	this->mMainMenuItem[eMenu_Sprite::Top_Right]->setPosition(CCPoint(49 + 74, 56 + 74));
	this->mMainMenuItem[eMenu_Sprite::Bottom_Left] = CCSprite::createWithSpriteFrameName("main_icons_0003.png");
	this->mMainMenuItem[eMenu_Sprite::Bottom_Left]->setPosition(CCPoint(-49 + 74, -56 + 74));
	this->mMainMenuItem[eMenu_Sprite::Bottom_Right] = CCSprite::createWithSpriteFrameName("main_icons_0004.png");
	this->mMainMenuItem[eMenu_Sprite::Bottom_Right]->setPosition(CCPoint(49 + 74, -56 + 74));
	for (std::vector<CCSprite*>::iterator it = this->mMainMenuItem.begin(); it != this->mMainMenuItem.end(); it ++)
	{
		if(*it != NULL)
			this->addChild(*it);
	}
	this->mCurLevel = eMenu_Level::Lv0;
}

bool TowerMenu::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	CCLog("TowerMenu::ccTouchBegan(CCTouch* touch, CCEvent* event)");
	if(!this->isVisible())
		return false;

	bool isTouched = isSpriteTouched(this, touch);
	if (isTouched)
	{
		CCSprite* selectedItem = getTouchedItem(touch);
		if(selectedItem)
		{
			MenuItemTag tag = (MenuItemTag)selectedItem->getTag();

// 			if (tag == MenuItemTag::Touched)
// 				return true;
// 			switch (tag)
// 			{
// 			case MenuItemTag::ArcherConfirmed:
// 				(this->mCurTower->*mCallFunc)(TowerMenuSelectType::BuildingArcher);
// 				break;
// 			case MenuItemTag::BarrackComfirmed:
// 				(this->mCurTower->*mCallFunc)(TowerMenuSelectType::BuildingBarrack);
// 				break;
// 			case MenuItemTag::MageConfirmed:
// 				(this->mCurTower->*mCallFunc)(TowerMenuSelectType::BuildingMage);
// 				break;
// 			case MenuItemTag::ArtilleryConfirmed:
// 				(this->mCurTower->*mCallFunc)(TowerMenuSelectType::BuildingArtillery);
// 				break;
// 			case MenuItemTag::UpgradeConfirmed:
// 				(this->mCurTower->*mCallFunc)(TowerMenuSelectType::Upgrade);
// 				break;
// 			case MenuItemTag::SpecialLeftConfirmed:
// 			case MenuItemTag::SpecialRightConfirmed:
// 			default:
// 				this->hideMenu();
// 				break;
// 			}

			(this->mCurTower->*mCallFunc)(tag);

			if(tag & 0xffff0000)
				this->hideMenu();
// 			if (MenuItemTag::confirmed == selectedItem->getTag())
// 			{
// 				this->hideMenu();
// 				(this->mCurTower->*mCallFunc)(TowerMenuSelectType::BuildingArcher);
// 			}
		}
		return true;
	}
	this->hideMenu();
	return false;
}

CCSprite* TowerMenu::getTouchedItem(CCTouch* touch ) 
{
	if(eMenu_Level::Lv0 == this->mCurLevel )
	{
		if(isSpriteTouched(this->mMainMenuItem[eMenu_Sprite::Top_Left], touch))
		{
			if (this->mMainMenuItem[eMenu_Sprite::Top_Left]->getTag() == MenuItemTag::ArcherChecked)
			{
				this->mMainMenuItem[eMenu_Sprite::Top_Left]->setTag(MenuItemTag::ArcherConfirmed);
				return this->mMainMenuItem[eMenu_Sprite::Top_Left];
			}
			this->mMainMenuItem[eMenu_Sprite::Top_Left]->setDisplayFrame(this->mMainMenuFrame[eMenu_Frame::Comfirm_Normal]);
			this->mMainMenuItem[eMenu_Sprite::Top_Left]->setTag(MenuItemTag::ArcherChecked);
			this->mMainMenuItem[eMenu_Sprite::Top_Right]->setDisplayFrame(this->mMainMenuFrame[eMenu_Frame::Barrack_Off]);
			this->mMainMenuItem[eMenu_Sprite::Top_Right]->setTag(MenuItemTag::NonTouched);
			this->mMainMenuItem[eMenu_Sprite::Bottom_Left]->setDisplayFrame(this->mMainMenuFrame[eMenu_Frame::Mage_Off]);
			this->mMainMenuItem[eMenu_Sprite::Bottom_Left]->setTag(MenuItemTag::NonTouched);
			this->mMainMenuItem[eMenu_Sprite::Bottom_Right]->setDisplayFrame(this->mMainMenuFrame[eMenu_Frame::Artillery_Off]);
			this->mMainMenuItem[eMenu_Sprite::Bottom_Right]->setTag(MenuItemTag::NonTouched);
			return this->mMainMenuItem[eMenu_Sprite::Top_Left];
		}
		else if(isSpriteTouched(this->mMainMenuItem[eMenu_Sprite::Top_Right], touch))
		{
			if (this->mMainMenuItem[eMenu_Sprite::Top_Right]->getTag() == MenuItemTag::BarrackChecked)
			{
				this->mMainMenuItem[eMenu_Sprite::Top_Right]->setTag(MenuItemTag::BarrackComfirmed);
				return this->mMainMenuItem[eMenu_Sprite::Top_Right];
			}
			this->mMainMenuItem[eMenu_Sprite::Top_Left]->setDisplayFrame(this->mMainMenuFrame[eMenu_Frame::Archer_Off]);
			this->mMainMenuItem[eMenu_Sprite::Top_Left]->setTag(MenuItemTag::NonTouched);
			this->mMainMenuItem[eMenu_Sprite::Top_Right]->setDisplayFrame(this->mMainMenuFrame[eMenu_Frame::Comfirm_Normal]);
			this->mMainMenuItem[eMenu_Sprite::Top_Right]->setTag(MenuItemTag::BarrackChecked);
			this->mMainMenuItem[eMenu_Sprite::Bottom_Left]->setDisplayFrame(this->mMainMenuFrame[eMenu_Frame::Mage_Off]);
			this->mMainMenuItem[eMenu_Sprite::Bottom_Left]->setTag(MenuItemTag::NonTouched);
			this->mMainMenuItem[eMenu_Sprite::Bottom_Right]->setDisplayFrame(this->mMainMenuFrame[eMenu_Frame::Artillery_Off]);
			this->mMainMenuItem[eMenu_Sprite::Bottom_Right]->setTag(MenuItemTag::NonTouched);
			return this->mMainMenuItem[eMenu_Sprite::Top_Right];
		}
		else if(isSpriteTouched(this->mMainMenuItem[eMenu_Sprite::Bottom_Left], touch))
		{
			if (this->mMainMenuItem[eMenu_Sprite::Bottom_Left]->getTag() == MenuItemTag::MageChecked)
			{
				this->mMainMenuItem[eMenu_Sprite::Bottom_Left]->setTag(MenuItemTag::MageConfirmed);
				return this->mMainMenuItem[eMenu_Sprite::Bottom_Left];
			}
			this->mMainMenuItem[eMenu_Sprite::Top_Left]->setDisplayFrame(this->mMainMenuFrame[eMenu_Frame::Archer_Off]);
			this->mMainMenuItem[eMenu_Sprite::Top_Left]->setTag(MenuItemTag::NonTouched);
			this->mMainMenuItem[eMenu_Sprite::Top_Right]->setDisplayFrame(this->mMainMenuFrame[eMenu_Frame::Barrack_Off]);
			this->mMainMenuItem[eMenu_Sprite::Top_Right]->setTag(MenuItemTag::NonTouched);
			this->mMainMenuItem[eMenu_Sprite::Bottom_Left]->setDisplayFrame(this->mMainMenuFrame[eMenu_Frame::Comfirm_Normal]);
			this->mMainMenuItem[eMenu_Sprite::Bottom_Left]->setTag(MenuItemTag::MageChecked);
			this->mMainMenuItem[eMenu_Sprite::Bottom_Right]->setDisplayFrame(this->mMainMenuFrame[eMenu_Frame::Artillery_Off]);
			this->mMainMenuItem[eMenu_Sprite::Bottom_Right]->setTag(MenuItemTag::NonTouched);
			return this->mMainMenuItem[eMenu_Sprite::Bottom_Left];
		}
		else if(isSpriteTouched(this->mMainMenuItem[eMenu_Sprite::Bottom_Right], touch))
		{
			if (this->mMainMenuItem[eMenu_Sprite::Bottom_Right]->getTag() == MenuItemTag::ArtilleryChecked)
			{
				this->mMainMenuItem[eMenu_Sprite::Bottom_Right]->setTag(MenuItemTag::ArtilleryConfirmed);
				return this->mMainMenuItem[eMenu_Sprite::Bottom_Right];
			}
			this->mMainMenuItem[eMenu_Sprite::Top_Left]->setDisplayFrame(this->mMainMenuFrame[eMenu_Frame::Archer_Off]);
			this->mMainMenuItem[eMenu_Sprite::Top_Left]->setTag(MenuItemTag::NonTouched);
			this->mMainMenuItem[eMenu_Sprite::Top_Right]->setDisplayFrame(this->mMainMenuFrame[eMenu_Frame::Barrack_Off]);
			this->mMainMenuItem[eMenu_Sprite::Top_Right]->setTag(MenuItemTag::NonTouched);
			this->mMainMenuItem[eMenu_Sprite::Bottom_Left]->setDisplayFrame(this->mMainMenuFrame[eMenu_Frame::Mage_Off]);
			this->mMainMenuItem[eMenu_Sprite::Bottom_Left]->setTag(MenuItemTag::NonTouched);
			this->mMainMenuItem[eMenu_Sprite::Bottom_Right]->setDisplayFrame(this->mMainMenuFrame[eMenu_Frame::Comfirm_Normal]);
			this->mMainMenuItem[eMenu_Sprite::Bottom_Right]->setTag(MenuItemTag::ArtilleryChecked);
			return this->mMainMenuItem[eMenu_Sprite::Bottom_Right];
		}
		else
		{
			return NULL;
		}
	}
	return NULL;
}



void TowerMenu::ccTouchMoved(CCTouch* touch, CCEvent* event)
{

	//获取当前用户触屏点坐标并将3d坐标映射2d坐标系
	//CCPoint touchPoint = touch->locationInView( touch->view() );
	//touchPoint = CCDirector::sharedDirector()->convertToGL( touchPoint );

	//touchPoint.x, getPosition().y
	//if(touchPoint.x> CCDirector::sharedDirector()->getWinSize().width/2){
	//	CCLog("%s","精灵22~~ccTouchMoved");
	//}
}

void TowerMenu::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	CCLog("TowerMenu::ccTouchEnded");
} 

//---SpriteClassModel 起始结束的生命周期函数----
void TowerMenu::onEnter()
{
	//注册监听   1.dele类，2.优先级，3.YES为阻碍其他类的move 和 end

	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
	CCSprite::onEnter();
}

void TowerMenu::onExit()
{
	//移除监听
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCSprite::onExit();
}

void TowerMenu::showMenu(CCPoint pos, eMenu_Level lv, Tower* tower, SEL_MenuTouchedFunc callback)
{
	this->mCurTower = tower;
	this->mCallFunc = callback;
	this->setPosition(pos);
	//Tower* a = (Tower*) this->mCurTower;
	this->mCurLevel = lv;

	switch (this->mCurLevel)
	{
	case eMenu_Level::Lv0:
		{
			this->mMainMenuItem[eMenu_Sprite::Top_Left]->setDisplayFrame(this->mMainMenuFrame[eMenu_Frame::Archer_Normal]);
			this->mMainMenuItem[eMenu_Sprite::Top_Right]->setDisplayFrame(this->mMainMenuFrame[eMenu_Frame::Barrack_Normal]);
			this->mMainMenuItem[eMenu_Sprite::Bottom_Left]->setDisplayFrame(this->mMainMenuFrame[eMenu_Frame::Mage_Normal]);
			this->mMainMenuItem[eMenu_Sprite::Bottom_Right]->setDisplayFrame(this->mMainMenuFrame[eMenu_Frame::Artillery_Normal]);
		}
		break;
	case eMenu_Level::Lv1_Mage:
		{
			this->mMainMenuItem[eMenu_Sprite::Top_Left]->setVisible(false);
			this->mMainMenuItem[eMenu_Sprite::Top_Right]->setVisible(false);
			this->mMainMenuItem[eMenu_Sprite::Bottom_Left]->setVisible(false);
			this->mMainMenuItem[eMenu_Sprite::Bottom_Right]->setVisible(false);
			this->mMainMenuItem[eMenu_Sprite::Bottom_Centre]->setDisplayFrame(this->mMainMenuFrame[eMenu_Frame::Upgrade_Normal]);
			this->mMainMenuItem[eMenu_Sprite::Bottom_Centre]->setDisplayFrame(this->mMainMenuFrame[eMenu_Frame::Sale_Normal]);
			this->mMainMenuItem[eMenu_Sprite::Bottom_Centre]->setVisible(true);
			this->mMainMenuItem[eMenu_Sprite::Top_Centre]->setVisible(true);
		}
		break;
	default:
		return;
		break;
	}
	this->setVisible(true);
}

void TowerMenu::hideMenu()
{
	this->setVisible(false);
	//this->resetFrame();
	(this->mCurTower->*mCallFunc)(MenuItemTag::NonTouched);
	this->mCurTower = NULL;
}


void TowerMenu::resetFrame()
{
	

}

void TowerMenu::update(float dt)
{

}

void TowerMenu::destory()
{

	this->setVisible(false);
}

CCRect TowerMenu::getCollisionRect()
{
	CCPoint pos = this->getPosition();
	return CCRect(pos.x - 3, pos.y -3, 6, 6);
}



