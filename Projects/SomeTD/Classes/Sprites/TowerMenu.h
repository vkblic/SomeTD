
#ifndef _TOWER_MENU_
#define _TOWER_MENU_

#include "cocos2d.h"
#include "Tower.h"
using namespace cocos2d;

class TowerMenu : public CCSprite , public CCTouchDelegate
{
public:	 
	enum eMenu_Frame
	{
		//common item
		Lock_Normal,
		Lock_Off,
		Lock_Disabled,
		Comfirm_Normal,
		Confirm_Disabled,
		Upgrade_Normal,
		Upgrade_Off,
		Upgrade_Disabled,
		Sale_Normal,
		Sale_Off,
		Sale_Confirm,
		Range_Circle,
		Rally_Circle,



		// archer tower
		Archer_Normal,
		Archer_Off,
		Archer_Disabled,
		Archer_Lv4_Left_Normal,
		Archer_Lv4_Left_Off,
		Archer_Lv4_Left_Confirm,
		Archer_Lv4_Rightr_Normal,
		Archer_Lv4_Rightr_Off,
		Archer_Lv4_Rightr_Confirm,

		// barrack tower
		Barrack_Normal,
		Barrack_Off,
		Barrack_Disabled,
		Barrack_Lv4_Left_Normal,
		Barrack_Lv4_Left_Off,
		Barrack_Lv4_Left_Confirm,
		Barrack_Lv4_Rightr_Normal,
		Barrack_Lv4_Rightr_Off,
		Barrack_Lv4_Rightr_Confirm,

		// mage tower
		Mage_Normal,
		Mage_Off,
		Mage_Disabled,
		Mage_Lv4_Arcane_Normal,
		Mage_Lv4_Arcane_Off,
		Mage_Lv4_Arcane_Confirm,
		Mage_Lv4_Sorcerer_Normal,
		Mage_Lv4_Sorcerer_Off,
		Mage_Lv4_Sorcerer_Confirm,

		// artillery tower
		Artillery_Normal,
		Artillery_Off,
		Artillery_Disabled,
		Artillery_Lv4_Left_Normal,
		Artillery_Lv4_Left_Off,
		Artillery_Lv4_Left_Confirm,
		Artillery_Lv4_Rightr_Normal,
		Artillery_Lv4_Rightr_Off,
		Artillery_Lv4_Rightr_Confirm,


		
		Menu_Frame_Max
	};
	enum eMenu_Sprite
	{
		Top_Left,
		Top_Right,
		Bottom_Left,
		Bottom_Right,
		Top_Centre,
		Bottom_Centre,
		Menu_Sprite_Max
	};

	enum eMenu_Level
	{
		Lv0,
		Lv1_Archer,
		Lv1_Barrack,
		Lv1_Mage,
		Lv1_Artillery,
		Lv2_Archer,
		Lv2_Barrack,
		Lv2_Mage,
		Lv2_Artillery,
		Lv3_Archer,
		Lv3_Barrack,
		Lv3_Mage,
		Lv3_Artillery,
	};




	enum MenuItemTag
	{
		NonTouched				= 0x0,

		// low 16 bit for checked status
		ArcherChecked			= 0x0001,
		BarrackChecked			= 0x0002,
		MageChecked				= 0x0004,
		ArtilleryChecked		= 0x0008,
		UpgradeChecked			= 0x0010,
		SpecialLeftChecked		= 0x0020,
		SpecialRightChecked		= 0x0040,



		// high 16 bit for confirmed status
		ArcherConfirmed			= ArcherChecked << 16,
		BarrackComfirmed		= BarrackChecked << 16,
		MageConfirmed			= MageChecked << 16,  
		ArtilleryConfirmed		= ArtilleryChecked << 16,
		UpgradeConfirmed		= UpgradeChecked << 16,
		SpecialLeftConfirmed	= SpecialLeftChecked << 16,
		SpecialRightConfirmed	= SpecialRightChecked << 16,


		//
		Checker = 0xFFFF0000

	};


public:
	static TowerMenu* sharedTowerMenu();

public:
public:
	void myInit();//自定义初始化函数
	virtual ~TowerMenu(){}
	//重写触屏相关函数----
	virtual void onEnter();
	virtual void onExit();
	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);


	virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);


public:
	void update(float dt); // execute every frame
	void onBuild(); //when bullet hit target
	void onUpgrade();
	void destory();
	void showMenu(CCPoint pos, eMenu_Level lv, Tower* tower, SEL_MenuTouchedFunc callback);

private:
	void resetFrame();
	void hideMenu();
	void onMenuHided();
	//return current touched item, if non-touch, return NULL.
	CCSprite* getTouchedItem(CCTouch* touch ) ;


private:

	std::vector<CCSpriteFrame*> mMainMenuFrame;
	std::vector<CCSprite*> mMainMenuItem;
	float _speed;
	CCPoint _targetLastPosition;
	CCSprite* _target;
	char temp[256];
protected:
	static TowerMenu* mInstance;
	int mCurLevel;
	Tower* mCurTower;
	SEL_MenuTouchedFunc mCallFunc;

};

#endif
