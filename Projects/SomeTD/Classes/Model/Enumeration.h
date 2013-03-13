// 
//  Enumeration.h
//  MyMoonWarriors
//
//  By Kelyad on 11/04/2012
//

#ifndef ENUMERATION_h
#define ENUMERATION_h


enum BULLET_TYPE
{
	TYPE1,
	TYPE2
};


//enemy show time
enum ENEMY_SHOW_COUNT
{
	Repeate, //
	Once,	//just one time
	Twice
};

//enemy action type
enum ENEMY_ACTION_TYPE
{
	ATTACK,		//stay on the top of the screen with attack
	VERTICAL,	//No attack
	HORIZONTAL,	//No attack
	OVERLAP	
};

enum ATTACK_MODE
{
	NORMAL,
	TSUIHIKIDAN
};

//Tower
enum TOWER_TYPE
{
	Tower_Mage_LV1,
	Tower_Mage_LV2,
	Tower_Mage_LV3,
	Tower_Mage_LV4_Arcane,
	Tower_Mage_LV4_Sorcerer,
	Tower_ArcherTower,
	TOWER_Max,
	Tower_None
};
enum TOWER_SHOOTER_TYPE
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
	SHOOTER_Max,
	SHOOTER_NONE
};

enum TOWER_TERRAIN_TYPE
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
