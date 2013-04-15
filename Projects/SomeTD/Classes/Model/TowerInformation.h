#ifndef _TOWER_INFORMATION_H_
#define _TOWER_INFORMATION_H_

#include "Enumeration.h"
#include "cocos2d.h"
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
	static TowerInformation* getInstance()
	{
		if (instance == nullptr)
			instance = new TowerInformation();
		return instance;
	}

public:	 
	CCSpriteFrame* getTowerFrame(eTower type)
	{
		return mTowerFrame[type];
	}

	CCSpriteFrame* getShooterFrame(eTower_Shooter type)
	{
		return mShooterFrame[type];
	}

	CCSpriteFrame* getTerrainFrame(eTower_Terrain type)
	{
		return mTerrainFrame[type];
	}


	CCSpriteFrame* getTowerPreviewFrame(eTower_Preview type)
	{
		return mTowerPreviewFrame[type];
	}

	CCSpriteFrame* getTerrainFrame(eTower_Constructing type)
	{
		return mTowerConstructingFrame[type];
	}

	CCSpriteFrame* getTowerRange(eTower towerType)
	{
		if(towerType & 0x00F0)
			return mRangeFrameBarrack;
		else
		return mRangeFrame;
	}

	std::vector<CCSpriteFrame*>* getTowerAnimation(eTower type)
	{
		return mTowerAnimation[type];
	}

	std::vector<CCSpriteFrame*>* getShooterAnimation(eTower_Shooter type)
	{
		return mShooterAnimation[type];
	}



public:
	//加载预制信息
	void LoadConfig(CCSpriteFrameCache* spriteFrameCache);

private:
	std::map<eTower, CCSpriteFrame*> mTowerFrame; //there's only two texture for now
	std::vector<CCSpriteFrame*>  mShooterFrame;
	std::vector<std::vector<CCSpriteFrame*>*> mTowerAnimation;
	std::vector<std::vector<CCSpriteFrame*>*> mShooterAnimation;
	std::vector<CCSpriteFrame*> mTerrainFrame;
	std::vector<CCSpriteFrame*> mTowerPreviewFrame;
	std::vector<CCSpriteFrame*> mTowerConstructingFrame;
	CCSpriteFrame* mRangeFrame;
	CCSpriteFrame* mRangeFrameBarrack;
	std::vector<int> mAttackRange;
	eTower mTowerType;
};

struct TowerModel
{
	eTower mTowerType ;
	eTower_Shooter mShooterTypeUp;
	eTower_Shooter mShooterTypeUpPart2;
	eTower_Shooter mShooterTypeDown;
	eTower_Shooter mShooterTypeDownPart2;

	/*
	 *shoot when animation frame index equal this value.
	 *@range [0, frameCount - 1]
	 */
	int mShootWhen;

	/*
	 *change display frame every x frame
	 *@default: 1
	 *@must >= 1
	 */
	int mFramesInterval;

	/*
	 *time use for reload, or we can see fire interval time.
	 *@unit: second
	 *@range [0, max)
	 */
	float mReloadTime;

	eTower_Terrain mTerrainType;

};




#endif