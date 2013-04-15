#include "TowerInformation.h"


//TowerInformation
TowerInformation* TowerInformation::instance = nullptr;



void TowerInformation::LoadConfig(CCSpriteFrameCache* spriteFrameCache)
{
	// frame

	//mTowerFrame.resize(Tower_Max);
	mTowerFrame[Tower_Mage_LV1] = spriteFrameCache->spriteFrameByName("mage_lvl1_0001.png");
	mTowerFrame[Tower_Mage_LV2] = spriteFrameCache->spriteFrameByName("mage_lvl2_0001.png");
	mTowerFrame[Tower_Mage_LV3] = spriteFrameCache->spriteFrameByName("mage_lvl3_0001.png");
	mTowerFrame[Tower_Mage_LV4_Arcane] = spriteFrameCache->spriteFrameByName("arcane_tower_0001.png");
	mTowerFrame[Tower_Mage_LV4_Sorcerer] = spriteFrameCache->spriteFrameByName("sorcerer_tower_0001.png");
	mTowerFrame[Tower_barrack_LV1] = spriteFrameCache->spriteFrameByName("barrack_lvl1_0001.png");
	mTowerFrame[Tower_barrack_LV2] = spriteFrameCache->spriteFrameByName("barrack_lvl2_0001.png");
	mTowerFrame[Tower_barrack_LV3] = spriteFrameCache->spriteFrameByName("barrack_lvl3_0001.png");
	mTowerFrame[Tower_barrack_LV4_barbarians] = spriteFrameCache->spriteFrameByName("barrack_lvl4_barbarians_0001.png");
	mTowerFrame[Tower_barrack_LV4_paladins] = spriteFrameCache->spriteFrameByName("barrack_lvl4_paladins_0001.png");


	mShooterFrame.resize(Shooter_Max);
	mShooterFrame[Shooter_Mage_LV_1To3_Up] = spriteFrameCache->spriteFrameByName("mage_shooter_0017.png");
	mShooterFrame[Shooter_Mage_LV_1To3_Down] = spriteFrameCache->spriteFrameByName("mage_shooter_0001.png");
	mShooterFrame[Shooter_Mage_LV4_Arcane_Up] = spriteFrameCache->spriteFrameByName("arcane_shooter_0002.png");
	mShooterFrame[Shooter_Mage_LV4_Arcane_Down] = spriteFrameCache->spriteFrameByName("arcane_shooter_0001.png");
	mShooterFrame[Shooter_Mage_LV4_Sorcerer_Up] = spriteFrameCache->spriteFrameByName("sorcerer_tower_0002.png");
	mShooterFrame[Shooter_Mage_LV4_Sorcerer_Down] = spriteFrameCache->spriteFrameByName("sorcerer_tower_0001.png");

	mTowerPreviewFrame.resize(Tower_Preview_Max);
	mTowerPreviewFrame[Tower_Preview_Archer] = spriteFrameCache->spriteFrameByName("tower_preview_archer.png");
	mTowerPreviewFrame[Tower_Preview_Barrack] = spriteFrameCache->spriteFrameByName("tower_preview_barrack.png");
	mTowerPreviewFrame[Tower_Preview_Mage] = spriteFrameCache->spriteFrameByName("tower_preview_mage.png");
	mTowerPreviewFrame[Tower_Preview_Artillery] = spriteFrameCache->spriteFrameByName("tower_preview_artillery.png");

	mTowerConstructingFrame.resize(Tower_Constructing_Max);
	mTowerConstructingFrame[Tower_Constructing_Archer] = spriteFrameCache->spriteFrameByName("tower_constructing_0004.png");
	mTowerConstructingFrame[Tower_Constructing_Barrack] = spriteFrameCache->spriteFrameByName("tower_constructing_0002.png");
	mTowerConstructingFrame[Tower_Constructing_Mage] = spriteFrameCache->spriteFrameByName("tower_constructing_0003.png");
	mTowerConstructingFrame[Tower_Constructing_Artillery] = spriteFrameCache->spriteFrameByName("tower_constructing_0001.png");



	// animation tower
	//auto animationTowerLv1 = addAnimationWithFramesToCache("mage_lvl1", "Tower_Mage_Lv1", 1, 11, SECOND_PER_FRAME * 2, true, 1);
	//auto animationTowerLv2 = addAnimationWithFramesToCache("mage_lvl2", "Tower_Mage_Lv2", 1, 11, SECOND_PER_FRAME, true, 1);
	//auto animationTowerLv3 = addAnimationWithFramesToCache("mage_lvl3", "Tower_Mage_Lv3", 1, 11, SECOND_PER_FRAME, true, 1);
	//auto animationTowerLv4_Arcane = addAnimationWithFramesToCache("arcane_tower", "Tower_Mage_LV4_Arcane", 1, 49, SECOND_PER_FRAME, true, 1);
	//auto animationTowerLv4_Sorcerer = addAnimationWithFramesToCache("sorcerer_tower", "Tower_Mage_LV4_Sorcerer", 1, 11, SECOND_PER_FRAME, true, 1);


	


	this->mTowerAnimation.resize(Tower_Max);
	buildAnimationFrameArray(&mTowerAnimation[Tower_Mage_LV1],"mage_lvl1", 1, 13 );
	buildAnimationFrameArray(&mTowerAnimation[Tower_Mage_LV2],"mage_lvl2", 1, 13 );
	buildAnimationFrameArray(&mTowerAnimation[Tower_Mage_LV3],"mage_lvl3", 1, 13 );
	buildAnimationFrameArray(&mTowerAnimation[Tower_Mage_LV4_Arcane],"arcane_tower", 1, 49 );
	buildAnimationFrameArray(&mTowerAnimation[Tower_Mage_LV4_Sorcerer],"sorcerer_tower", 1, 11 );


	buildAnimationFrameArray(&mTowerAnimation[Tower_barrack_LV1],"barrack_lvl1", 1, 4 );
	buildAnimationFrameArray(&mTowerAnimation[Tower_barrack_LV2],"barrack_lvl2", 1, 4 );
	buildAnimationFrameArray(&mTowerAnimation[Tower_barrack_LV3],"barrack_lvl3", 1, 4 );
	buildAnimationFrameArray(&mTowerAnimation[Tower_barrack_LV4_barbarians],"barrack_lvl4_barbarians", 1, 4 );
	buildAnimationFrameArray(&mTowerAnimation[Tower_barrack_LV4_paladins],"barrack_lvl4_paladins", 1, 4 );
	
	//this->mTowerAnimation[Tower_Mage_LV1] = animationTowerLv1;
	//this->mTowerAnimation[Tower_Mage_LV2] = animationTowerLv2;
	//this->mTowerAnimation[Tower_Mage_LV3] = animationTowerLv3;
	//this->mTowerAnimation[Tower_Mage_LV4_Arcane] = animationTowerLv4_Arcane;
	//this->mTowerAnimation[Tower_Mage_LV4_Sorcerer] = animationTowerLv4_Sorcerer;

	//animation shooter
	//auto animationShooterLv1_3Up = 
	//	addAnimationWithFramesToCache("mage_shooter", "Shooter_Mage_LV_1To3_Up", 17, 24, SECOND_PER_FRAME * 2, false, 1);
	//auto animationShooterLv1_3UpPart2 = 
	//	addAnimationWithFramesToCache("mage_shooter", "Shooter_Mage_LV_1To3_Up_Part2", 25, 29, SECOND_PER_FRAME * 2, false, 1);
	//
	//auto animationShooterLv1_3Down = 
	//	addAnimationWithFramesToCache("mage_shooter", "Shooter_Mage_LV_1To3_Down", 3, 14, SECOND_PER_FRAME * 2, true, 1);
	//auto animationShooterLv1_3DownPart2 = 
	//	addAnimationWithFramesToCache("mage_shooter", "Shooter_Mage_LV_1To3_Down_Part2", 12, 14, SECOND_PER_FRAME * 2, false, 1);




	mShooterAnimation.resize(Shooter_Max);

	buildAnimationFrameArray(&mShooterAnimation[Shooter_Mage_LV_1To3_Down],"mage_shooter", 3, 14 );
	buildAnimationFrameArray(&mShooterAnimation[Shooter_Mage_LV_1To3_Up],"mage_shooter", 17, 29 );
	//Shooter_Mage_LV_1To3_Down specially handle
	auto tempFrame = spriteFrameCache->spriteFrameByName("mage_shooter_0001.png");
	auto tempVector =  mShooterAnimation[Shooter_Mage_LV_1To3_Down];
	tempVector->insert(tempVector->begin(), tempFrame);



	//this->mShooterAnimation[Shooter_Mage_LV_1To3_Up] = animationShooterLv1_3Up;
	//this->mShooterAnimation[Shooter_Mage_LV_1To3_Up_Part2] = animationShooterLv1_3UpPart2;
	//this->mShooterAnimation[Shooter_Mage_LV_1To3_Down] = animationShooterLv1_3Down;
	//this->mShooterAnimation[Shooter_Mage_LV_1To3_Down_Part2] = animationShooterLv1_3DownPart2;


	//Terrain frame
	mTerrainFrame.resize(Terrain_Max);
	mTerrainFrame[Terrain_Build_Yellow] = spriteFrameCache->spriteFrameByName("build_terrain_0001.png");
	mTerrainFrame[Terrain_Build_Gray] = spriteFrameCache->spriteFrameByName("build_terrain_0002.png");
	mTerrainFrame[Terrain_Build_DarkGray] = spriteFrameCache->spriteFrameByName("build_terrain_0003.png");
	mTerrainFrame[Terrain_MageLv1_3_Yellow] = spriteFrameCache->spriteFrameByName("terrain_mage_0001.png");
	mTerrainFrame[Terrain_MageLv1_3_Gray] = spriteFrameCache->spriteFrameByName("terrain_mage_0002.png");
	mTerrainFrame[Terrain_MageLv1_3_DarkGray] = spriteFrameCache->spriteFrameByName("terrain_mage_0003.png");


	//Range Frame
	mRangeFrame = spriteFrameCache->spriteFrameByName("range_circle.png");
	mRangeFrameBarrack = spriteFrameCache->spriteFrameByName("rally_circle.png");

	//Range num
	mAttackRange.resize(Tower_Max);

	mAttackRange[Tower_Mage_LV1] = 10;
	mAttackRange[Tower_Mage_LV2] = 11;
	mAttackRange[Tower_Mage_LV3] = 12;
	mAttackRange[Tower_Mage_LV4_Arcane] = 13;
	mAttackRange[Tower_Mage_LV4_Sorcerer] = 13;


}