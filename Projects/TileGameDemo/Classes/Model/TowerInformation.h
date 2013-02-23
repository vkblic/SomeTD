#ifndef _TOWER_INFORMATION_H_
#define _TOWER_INFORMATION_H_

#include "Enumeration.h"
#include "cocos2d.h"
#include "../Sprites/Bullet.h"
#include "../Helper/SpriteHelpers.h"
#include "../Helper/CommonHelpers.h"


class TowerInformation
{
	/*
	 *Single Instance
	 **/
private:
	static TowerInformation* instance ;
	TowerInformation()
	{
		 //_TowerFrameByType = new std::vector<CCSpriteFrame*>();

	};
public:		
	static TowerInformation* GetInstance()
	{
		if (instance == nullptr)
			instance = new TowerInformation();
		return instance;
	}

public:	 
	CCSpriteFrame* GetTowerFrame(TOWER_TYPE type)
	{
		return _TowerFrameByType[type];
	}
	CCSpriteFrame* GetShooterFrameUp(TOWER_TYPE type)
	{
		return _ShoortFrameByType[type];
	}

public:
	//加载预制信息
	void LoadConfig(CCSpriteFrameCache* spriteFrameCache)
	{
		// frame
		this->_TowerFrameByType.resize(TOWER_TYPE::TOWER_Max);
		this->_TowerFrameByType[TOWER_TYPE::Mage_LV1] = spriteFrameCache->spriteFrameByName("mage_lvl1_0001.png");
		this->_TowerFrameByType[TOWER_TYPE::Mage_LV2] = spriteFrameCache->spriteFrameByName("mage_lvl2_0001.png");
		this->_TowerFrameByType[TOWER_TYPE::Mage_LV3] = spriteFrameCache->spriteFrameByName("mage_lvl3_0001.png");
		this->_TowerFrameByType[TOWER_TYPE::Mage_LV4_Arcane] = spriteFrameCache->spriteFrameByName("arcane_tower_0001.png");
		this->_TowerFrameByType[TOWER_TYPE::Mage_LV4_Sorcerer] = spriteFrameCache->spriteFrameByName("sorcerer_tower_0001.png");


		this->_ShoortFrameByType.resize(TOWER_SHOOTER_TYPE::SHOOTER_Max);
		this->_ShoortFrameByType[TOWER_SHOOTER_TYPE::Mage_LV_1To3_Up] = spriteFrameCache->spriteFrameByName("mage_shooter_0002.png");
		this->_ShoortFrameByType[TOWER_SHOOTER_TYPE::Mage_LV_1To3_Down] = spriteFrameCache->spriteFrameByName("mage_shooter_0001.png");
		this->_ShoortFrameByType[TOWER_SHOOTER_TYPE::Mage_LV4_Arcane_Up] = spriteFrameCache->spriteFrameByName("arcane_shooter_0002.png");
		this->_ShoortFrameByType[TOWER_SHOOTER_TYPE::Mage_LV4_Arcane_Down] = spriteFrameCache->spriteFrameByName("arcane_shooter_0001.png");
		this->_ShoortFrameByType[TOWER_SHOOTER_TYPE::Mage_LV4_Sorcerer_Up] = spriteFrameCache->spriteFrameByName("sorcerer_tower_0002.png");
		this->_ShoortFrameByType[TOWER_SHOOTER_TYPE::Mage_LV4_Sorcerer_Down] = spriteFrameCache->spriteFrameByName("sorcerer_tower_0001.png");

		// animation
		auto animationTowerLv1 = addAnimationWithFramesToCache("mage_lvl1", "Tower_Mage_Lv1", 1, 11, SECOND_PER_FRAME, true, 1);
		auto animationTowerLv2 = addAnimationWithFramesToCache("mage_lvl2", "Tower_Mage_Lv1", 1, 11, SECOND_PER_FRAME, true, 1);
		auto animationTowerLv3 = addAnimationWithFramesToCache("mage_lvl3", "Tower_Mage_Lv1", 1, 11, SECOND_PER_FRAME, true, 1);
		auto animationTowerLv4_Arcane = addAnimationWithFramesToCache("mage_lvl1", "Tower_Mage_Lv1", 1, 0, SECOND_PER_FRAME, true, 1);
		auto animationTowerLv4_Sorcerer = addAnimationWithFramesToCache("mage_lvl1", "Tower_Mage_Lv1", 1, 0, SECOND_PER_FRAME, true, 1);
		//this->_TowerAnimationByType[]
	}

private:
	std::vector<CCSpriteFrame*> _TowerFrameByType; //there's only two texture for now
	std::vector<CCSpriteFrame*>  _ShoortFrameByType;

	std::vector<CCAnimation*> _TowerAnimationByType;
	std::vector<CCAnimation*> _ShoortAnimationByType;
	//int _DamageByType [2];
	Bullet *BulletInfo; 
	TOWER_TYPE towerType;
};



#endif