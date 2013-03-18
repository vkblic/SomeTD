#include "TowerInformation.h"


//TowerInformation
TowerInformation* TowerInformation::instance = nullptr;



void TowerInformation::LoadConfig(CCSpriteFrameCache* spriteFrameCache)
{
	// frame

	this->mTowerFrame.resize(Tower_Max);
	this->mTowerFrame[Tower_Mage_LV1] = spriteFrameCache->spriteFrameByName("mage_lvl1_0001.png");
	this->mTowerFrame[Tower_Mage_LV2] = spriteFrameCache->spriteFrameByName("mage_lvl2_0001.png");
	this->mTowerFrame[Tower_Mage_LV3] = spriteFrameCache->spriteFrameByName("mage_lvl3_0001.png");
	this->mTowerFrame[Tower_Mage_LV4_Arcane] = spriteFrameCache->spriteFrameByName("arcane_tower_0001.png");
	this->mTowerFrame[Tower_Mage_LV4_Sorcerer] = spriteFrameCache->spriteFrameByName("sorcerer_tower_0001.png");


	this->mShooterFrame.resize(Shooter_Max);
	this->mShooterFrame[Shooter_Mage_LV_1To3_Up] = spriteFrameCache->spriteFrameByName("mage_shooter_0002.png");
	this->mShooterFrame[Shooter_Mage_LV_1To3_Down] = spriteFrameCache->spriteFrameByName("mage_shooter_0001.png");
	this->mShooterFrame[Shooter_Mage_LV4_Arcane_Up] = spriteFrameCache->spriteFrameByName("arcane_shooter_0002.png");
	this->mShooterFrame[Shooter_Mage_LV4_Arcane_Down] = spriteFrameCache->spriteFrameByName("arcane_shooter_0001.png");
	this->mShooterFrame[Shooter_Mage_LV4_Sorcerer_Up] = spriteFrameCache->spriteFrameByName("sorcerer_tower_0002.png");
	this->mShooterFrame[Shooter_Mage_LV4_Sorcerer_Down] = spriteFrameCache->spriteFrameByName("sorcerer_tower_0001.png");

	this->mTowerPreviewFrame.resize(Tower_Preview_Max);
	this->mTowerPreviewFrame[Tower_Preview_Archer] = spriteFrameCache->spriteFrameByName("tower_preview_archer.png");
	this->mTowerPreviewFrame[Tower_Preview_Barrack] = spriteFrameCache->spriteFrameByName("tower_preview_barrack.png");
	this->mTowerPreviewFrame[Tower_Preview_Mage] = spriteFrameCache->spriteFrameByName("tower_preview_mage.png");
	this->mTowerPreviewFrame[Tower_Preview_Artillery] = spriteFrameCache->spriteFrameByName("tower_preview_artillery.png");

	this->mTowerConstructingFrame.resize(Tower_Constructing_Max);
	this->mTowerConstructingFrame[Tower_Constructing_Archer] = spriteFrameCache->spriteFrameByName("tower_constructing_0004.png");
	this->mTowerConstructingFrame[Tower_Constructing_Barrack] = spriteFrameCache->spriteFrameByName("tower_constructing_0002.png");
	this->mTowerConstructingFrame[Tower_Constructing_Mage] = spriteFrameCache->spriteFrameByName("tower_constructing_0003.png");
	this->mTowerConstructingFrame[Tower_Constructing_Artillery] = spriteFrameCache->spriteFrameByName("tower_constructing_0001.png");



	// animation tower
	auto animationTowerLv1 = addAnimationWithFramesToCache("mage_lvl1", "Tower_Mage_Lv1", 3, 7, SECOND_PER_FRAME * 2, true, 1);
	auto animationTowerLv2 = addAnimationWithFramesToCache("mage_lvl2", "Tower_Mage_Lv2", 1, 11, SECOND_PER_FRAME, true, 1);
	auto animationTowerLv3 = addAnimationWithFramesToCache("mage_lvl3", "Tower_Mage_Lv3", 1, 11, SECOND_PER_FRAME, true, 1);
	auto animationTowerLv4_Arcane = addAnimationWithFramesToCache("arcane_tower", "Tower_Mage_LV4_Arcane", 1, 49, SECOND_PER_FRAME, true, 1);
	auto animationTowerLv4_Sorcerer = addAnimationWithFramesToCache("sorcerer_tower", "Tower_Mage_LV4_Sorcerer", 1, 11, SECOND_PER_FRAME, true, 1);

	this->mTowerAnimation.resize(Tower_Max);
	this->mTowerAnimation[eTower::Tower_Mage_LV1] = animationTowerLv1;
	this->mTowerAnimation[eTower::Tower_Mage_LV2] = animationTowerLv2;
	this->mTowerAnimation[eTower::Tower_Mage_LV3] = animationTowerLv3;
	this->mTowerAnimation[eTower::Tower_Mage_LV4_Arcane] = animationTowerLv4_Arcane;
	this->mTowerAnimation[eTower::Tower_Mage_LV4_Sorcerer] = animationTowerLv4_Sorcerer;

	//animation shooter
	auto animationShooterLv1_3Up = 
		addAnimationWithFramesToCache("mage_shooter", "Shooter_Mage_LV_1To3_Up", 17, 24, SECOND_PER_FRAME * 2, false, 1);
	auto animationShooterLv1_3UpPart2 = 
		addAnimationWithFramesToCache("mage_shooter", "Shooter_Mage_LV_1To3_Up_Part2", 25, 29, SECOND_PER_FRAME * 2, false, 1);

	auto animationShooterLv1_3Down = 
		addAnimationWithFramesToCache("mage_shooter", "Shooter_Mage_LV_1To3_Down", 3, 14, SECOND_PER_FRAME * 2, true, 1);
	auto animationShooterLv1_3DownPart2 = 
		addAnimationWithFramesToCache("mage_shooter", "Shooter_Mage_LV_1To3_Down_Part2", 12, 14, SECOND_PER_FRAME * 2, false, 1);




	this->mShooterAnimation.resize(eTower_Shooter::Shooter_Max);
	this->mShooterAnimation[eTower_Shooter::Shooter_Mage_LV_1To3_Up] = animationShooterLv1_3Up;
	this->mShooterAnimation[eTower_Shooter::Shooter_Mage_LV_1To3_Up_Part2] = animationShooterLv1_3UpPart2;
	this->mShooterAnimation[eTower_Shooter::Shooter_Mage_LV_1To3_Down] = animationShooterLv1_3Down;
	this->mShooterAnimation[eTower_Shooter::Shooter_Mage_LV_1To3_Down_Part2] = animationShooterLv1_3DownPart2;


	//Terrain frame
	this->mTerrainFrame.resize(eTower_Terrain::Terrain_Max);
	this->mTerrainFrame[eTower_Terrain::Terrain_Build_Yellow] = spriteFrameCache->spriteFrameByName("build_terrain_0001.png");
	this->mTerrainFrame[eTower_Terrain::Terrain_Build_Gray] = spriteFrameCache->spriteFrameByName("build_terrain_0002.png");
	this->mTerrainFrame[eTower_Terrain::Terrain_Build_DarkGray] = spriteFrameCache->spriteFrameByName("build_terrain_0003.png");
	this->mTerrainFrame[eTower_Terrain::Terrain_MageLv1_3_Yellow] = spriteFrameCache->spriteFrameByName("terrain_mage_0001.png");
	this->mTerrainFrame[eTower_Terrain::Terrain_MageLv1_3_Gray] = spriteFrameCache->spriteFrameByName("terrain_mage_0002.png");
	this->mTerrainFrame[eTower_Terrain::Terrain_MageLv1_3_DarkGray] = spriteFrameCache->spriteFrameByName("terrain_mage_0003.png");


	//Range
	mRangeFrame = spriteFrameCache->spriteFrameByName("range_circle.png");

}