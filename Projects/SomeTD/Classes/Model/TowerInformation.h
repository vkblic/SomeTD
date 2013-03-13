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



	CCAnimation* getTowerAnimation(eTower type)
	{
		return mTowerAnimation[type];
	}
	CCAnimation* getShooterAnimation(eTower_Shooter type)
	{
		return mShooterAnimation[type];
	}



public:
	//加载预制信息
	void LoadConfig(CCSpriteFrameCache* spriteFrameCache);

private:
	std::vector<CCSpriteFrame*> mTowerFrame; //there's only two texture for now
	std::vector<CCSpriteFrame*>  mShooterFrame;
	std::vector<CCAnimation*> mTowerAnimation;
	std::vector<CCAnimation*> mShooterAnimation;
	std::vector<CCSpriteFrame*> mTerrainFrame;
	std::vector<CCSpriteFrame*> mTowerPreviewFrame;
	std::vector<CCSpriteFrame*> mTowerConstructingFrame;
	eTower towerType;
};



#endif