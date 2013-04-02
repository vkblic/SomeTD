// 
//  Enumeration.h
//  MyMoonWarriors
//
//  By Kelyad on 11/04/2012
//

#ifndef ENUMERATION_h
#define ENUMERATION_h
#include "cocos2d.h"
using namespace cocos2d;
const int TileWidth = 16;
const int TileHeight = 16;
const int HP_BAR_WIDTH = 30;
static const float SECOND_PER_FRAME = 0.0167f;
typedef struct WayPoint
{
	WayPoint(int x, int y)
	{
		this->pos.x = x;
		this->pos.y = y;
	}
	CCPoint pos;
}*pWayPoint;
inline WayPoint IDS_Create_WayPoint(float x, float y)
{
	return WayPoint(x, y);
}

//Tower
enum eTower
{
	Tower_None = 0x0,

	// low 16bit
	Tower_Mage_LV1 = 0x0001,
	Tower_Mage_LV2 = 0x0002,
	Tower_Mage_LV3 = 0x0004,
	Tower_barrack_LV1 = 0x0010,
	Tower_barrack_LV2 = 0x0020,
	Tower_barrack_LV3 = 0x0030,

	// high 16bit
	Tower_Mage_LV4_Arcane = 0x00010000,
	Tower_Mage_LV4_Sorcerer = 0x00020000,
	Tower_barrack_LV4_barbarians = 0x00100000,
	Tower_barrack_LV4_paladins = 0x00200000,

	Tower_Max,
	
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
