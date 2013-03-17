// 
//  Enumeration.h
//  MyMoonWarriors
//
//  By Kelyad on 11/04/2012
//

#ifndef ENUMERATION_h
#define ENUMERATION_h

//Tower
enum eTower
{
	Tower_Mage_LV1,
	Tower_Mage_LV2,
	Tower_Mage_LV3,
	Tower_Mage_LV4_Arcane,
	Tower_Mage_LV4_Sorcerer,
	Tower_ArcherTower,
	Tower_Max,
	Tower_None
};

enum eTower_Preview
{
	Tower_Preview_Archer,
	Tower_Preview_Barrack,
	Tower_Preview_Mage,
	Tower_Preview_Artillery,
	Tower_Preview_Max,
	Tower_Preview_None
};

enum eTower_Constructing
{
	Tower_Constructing_Archer,
	Tower_Constructing_Barrack,
	Tower_Constructing_Mage,
	Tower_Constructing_Artillery,
	Tower_Constructing_Max,
	Tower_Constructing_None
};


enum eTower_Shooter
{
	Shooter_Mage_LV_1To3_Up,			
	Shooter_Mage_LV_1To3_Up_Part2,
	Shooter_Mage_LV_1To3_Down,			
	Shooter_Mage_LV_1To3_Down_Part2,
	Shooter_Mage_LV4_Arcane_Up,
	Shooter_Mage_LV4_Arcane_Up_Part2,
	Shooter_Mage_LV4_Arcane_Down,
	Shooter_Mage_LV4_Arcane_Down_Part2,
	Shooter_Mage_LV4_Sorcerer_Up,
	Shooter_Mage_LV4_Sorcerer_Up_Part2,
	Shooter_Mage_LV4_Sorcerer_Down,
	Shooter_Mage_LV4_Sorcerer_Down_Part2,
	Shooter_Mage_LV4_Sorcerer_Magic_Up,
	Shooter_Mage_LV4_Sorcerer_Magic_Up_Part2,
	Shooter_Mage_LV4_Sorcerer_Magic_Down,
	Shooter_Mage_LV4_Sorcerer_Magic_Down_Part2,
	Shooter_Max,
	Shooter_None
};

enum eTower_Terrain
{
	Terrain_Build_Yellow,
	Terrain_Build_Gray,
	Terrain_Build_DarkGray,
	Terrain_MageLv1_3_Yellow,
	Terrain_MageLv1_3_Gray,
	Terrain_MageLv1_3_DarkGray,
	Terrain_Max,
	Terrain_None
};

#endif
