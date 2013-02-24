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
		return mTowerFrameByType[type];
	}
	CCSpriteFrame* GetShooterFrame(TOWER_SHOOTER_TYPE type)
	{
		return mShooterFrameByType[type];
	}
	CCSpriteFrame* GetTerrainFrame(TOWER_TERRAIN_TYPE type)
	{
		return mTerrainFrameByType[type];
	}
	CCAnimation* GetTowerAnimation(TOWER_TYPE type)
	{
		return mTowerAnimationByType[type];
	}
	CCAnimation* GetShooterAnimation(TOWER_SHOOTER_TYPE type)
	{
		return mShooterAnimationByType[type];
	}
public:
	//加载预制信息
	void LoadConfig(CCSpriteFrameCache* spriteFrameCache)
	{
		// frame
		this->mTowerFrameByType.resize(TOWER_TYPE::TOWER_Max);
		this->mTowerFrameByType[TOWER_TYPE::Tower_Mage_LV1] = spriteFrameCache->spriteFrameByName("mage_lvl1_0001.png");
		this->mTowerFrameByType[TOWER_TYPE::Tower_Mage_LV2] = spriteFrameCache->spriteFrameByName("mage_lvl2_0001.png");
		this->mTowerFrameByType[TOWER_TYPE::Tower_Mage_LV3] = spriteFrameCache->spriteFrameByName("mage_lvl3_0001.png");
		this->mTowerFrameByType[TOWER_TYPE::Tower_Mage_LV4_Arcane] = spriteFrameCache->spriteFrameByName("arcane_tower_0001.png");
		this->mTowerFrameByType[TOWER_TYPE::Tower_Mage_LV4_Sorcerer] = spriteFrameCache->spriteFrameByName("sorcerer_tower_0001.png");


		this->mShooterFrameByType.resize(TOWER_SHOOTER_TYPE::SHOOTER_Max);
		this->mShooterFrameByType[TOWER_SHOOTER_TYPE::Shooter_Mage_LV_1To3_Up] = spriteFrameCache->spriteFrameByName("mage_shooter_0002.png");
		this->mShooterFrameByType[TOWER_SHOOTER_TYPE::Shooter_Mage_LV_1To3_Down] = spriteFrameCache->spriteFrameByName("mage_shooter_0001.png");
		this->mShooterFrameByType[TOWER_SHOOTER_TYPE::Shooter_Mage_LV4_Arcane_Up] = spriteFrameCache->spriteFrameByName("arcane_shooter_0002.png");
		this->mShooterFrameByType[TOWER_SHOOTER_TYPE::Shooter_Mage_LV4_Arcane_Down] = spriteFrameCache->spriteFrameByName("arcane_shooter_0001.png");
		this->mShooterFrameByType[TOWER_SHOOTER_TYPE::Shooter_Mage_LV4_Sorcerer_Up] = spriteFrameCache->spriteFrameByName("sorcerer_tower_0002.png");
		this->mShooterFrameByType[TOWER_SHOOTER_TYPE::Shooter_Mage_LV4_Sorcerer_Down] = spriteFrameCache->spriteFrameByName("sorcerer_tower_0001.png");

		// animation tower
		auto animationTowerLv1 = addAnimationWithFramesToCache("mage_lvl1", "Tower_Mage_Lv1", 3, 7, SECOND_PER_FRAME * 2, true, 1);
		auto animationTowerLv2 = addAnimationWithFramesToCache("mage_lvl2", "Tower_Mage_Lv2", 1, 11, SECOND_PER_FRAME, true, 1);
		auto animationTowerLv3 = addAnimationWithFramesToCache("mage_lvl3", "Tower_Mage_Lv3", 1, 11, SECOND_PER_FRAME, true, 1);
		auto animationTowerLv4_Arcane = addAnimationWithFramesToCache("arcane_tower", "Tower_Mage_LV4_Arcane", 1, 49, SECOND_PER_FRAME, true, 1);
		auto animationTowerLv4_Sorcerer = addAnimationWithFramesToCache("sorcerer_tower", "Tower_Mage_LV4_Sorcerer", 1, 11, SECOND_PER_FRAME, true, 1);

		this->mTowerAnimationByType.resize(TOWER_Max);
		this->mTowerAnimationByType[TOWER_TYPE::Tower_Mage_LV1] = animationTowerLv1;
		this->mTowerAnimationByType[TOWER_TYPE::Tower_Mage_LV2] = animationTowerLv2;
		this->mTowerAnimationByType[TOWER_TYPE::Tower_Mage_LV3] = animationTowerLv3;
		this->mTowerAnimationByType[TOWER_TYPE::Tower_Mage_LV4_Arcane] = animationTowerLv4_Arcane;
		this->mTowerAnimationByType[TOWER_TYPE::Tower_Mage_LV4_Sorcerer] = animationTowerLv4_Sorcerer;

		//animation shooter
		auto animationShooterLv1_3Up = 
			addAnimationWithFramesToCache("mage_shooter", "Shooter_Mage_LV_1To3_Up", 17, 24, SECOND_PER_FRAME * 2, false, 1);
		auto animationShooterLv1_3UpPart2 = 
			addAnimationWithFramesToCache("mage_shooter", "Shooter_Mage_LV_1To3_Up_Part2", 25, 29, SECOND_PER_FRAME * 2, false, 1);

		auto animationShooterLv1_3Down = 
			addAnimationWithFramesToCache("mage_shooter", "Shooter_Mage_LV_1To3_Down", 3, 14, SECOND_PER_FRAME * 2, false, 1);
		auto animationShooterLv1_3DownPart2 = 
			addAnimationWithFramesToCache("mage_shooter", "Shooter_Mage_LV_1To3_Down_Part2", 12, 14, SECOND_PER_FRAME * 2, false, 1);




		this->mShooterAnimationByType.resize(TOWER_SHOOTER_TYPE::SHOOTER_Max);





		this->mShooterAnimationByType[TOWER_SHOOTER_TYPE::Shooter_Mage_LV_1To3_Up] = animationShooterLv1_3Up;
		this->mShooterAnimationByType[TOWER_SHOOTER_TYPE::Shooter_Mage_LV_1To3_Up_Part2] = animationShooterLv1_3UpPart2;
		this->mShooterAnimationByType[TOWER_SHOOTER_TYPE::Shooter_Mage_LV_1To3_Down] = animationShooterLv1_3Down;
		this->mShooterAnimationByType[TOWER_SHOOTER_TYPE::Shooter_Mage_LV_1To3_Down_Part2] = animationShooterLv1_3DownPart2;


		//Terrain frame
		this->mTerrainFrameByType.resize(TOWER_TERRAIN_TYPE::Terrain_Max);
		this->mTerrainFrameByType[TOWER_TERRAIN_TYPE::Terrain_Build_Yellow] = spriteFrameCache->spriteFrameByName("build_terrain_0001.png");
		this->mTerrainFrameByType[TOWER_TERRAIN_TYPE::Terrain_Build_Gray] = spriteFrameCache->spriteFrameByName("build_terrain_0002.png");
		this->mTerrainFrameByType[TOWER_TERRAIN_TYPE::Terrain_Build_DarkGray] = spriteFrameCache->spriteFrameByName("build_terrain_0003.png");
		this->mTerrainFrameByType[TOWER_TERRAIN_TYPE::Terrain_MageLv1_3_Yellow] = spriteFrameCache->spriteFrameByName("terrain_mage_0001.png");
		this->mTerrainFrameByType[TOWER_TERRAIN_TYPE::Terrain_MageLv1_3_Gray] = spriteFrameCache->spriteFrameByName("terrain_mage_0002.png");
		this->mTerrainFrameByType[TOWER_TERRAIN_TYPE::Terrain_MageLv1_3_DarkGray] = spriteFrameCache->spriteFrameByName("terrain_mage_0003.png");
	}

private:
	std::vector<CCSpriteFrame*> mTowerFrameByType; //there's only two texture for now
	std::vector<CCSpriteFrame*>  mShooterFrameByType;
	std::vector<CCAnimation*> mTowerAnimationByType;
	std::vector<CCAnimation*> mShooterAnimationByType;
	std::vector<CCSpriteFrame*> mTerrainFrameByType;
	TOWER_TYPE towerType;
};



#endif