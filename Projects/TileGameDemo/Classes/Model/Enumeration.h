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
	Mage_LV1,
	Mage_LV2,
	Mage_LV3,
	Mage_LV4_Arcane,
	Mage_LV4_Sorcerer,
	ArcherTower,
	TOWER_Max
};
enum TOWER_SHOOTER_TYPE
{
	Mage_LV_1To3_Up,			// Shooter of mage tower from lv1 to lv3, direction to up
	Mage_LV_1To3_Down,			// Shooter of mage tower  
	Mage_LV4_Arcane_Up,
	Mage_LV4_Arcane_Down,
	Mage_LV4_Sorcerer_Up,
	Mage_LV4_Sorcerer_Down,
	Mage_LV4_Sorcerer_Magic_Up,
	Mage_LV4_Sorcerer_Magic_Down,
	SHOOTER_Max
};

#endif
