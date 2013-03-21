#include "HelloWorldScene.h"
#include "../Sprites/TowerMenu.h"
#include "../Helper/SpriteHelpers.h"
#include "../Helper/CommonHelpers.h"
#include "../Model/TowerInformation.h"
#include "../Managers/EnemyManager.h"
#include "../Sprites/Enemy.h"
using namespace cocos2d;

float HelloWorld::_scale = 1.0f;
CCScene* HelloWorld::scene()
{
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		HelloWorld *layer = HelloWorld::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	bool bRet = false;
	do 
	{
		//////////////////////////////////////////////////////////////////////////
		// super init first
		//////////////////////////////////////////////////////////////////////////

		if (!CCLayer::init())
			break;

		// 		this->_tileMap = CCTMXTiledMap::create("TileMap.tmx");
		// 		this->_background = _tileMap->layerNamed("Background");
		// 
		// 		this->addChild(this->_tileMap, -1);
		// 
		// 		CCTMXObjectGroup *objects = this->_tileMap->objectGroupNamed("Objects");
		// 		CCDictionary *spawnPoint = objects->objectNamed("SpawnPoint");
		// 		int x = spawnPoint->valueForKey("x")->intValue();
		// 		int y = spawnPoint->valueForKey("y")->intValue();
		// 
		// 		CCSprite *player = CCSprite::create("Player.png");
		// 		this->_player = player;
		// 		player->setPosition(CCPoint(x, y));
		// 		this->addChild(player);
		// 		
		this->_tileMap = CCTMXTiledMap::create("KingdomRush_960_720.tmx");
		this->_background = _tileMap->layerNamed("Background");

		this->addChild(this->_tileMap, -1);

		CCTMXObjectGroup *objects = this->_tileMap->objectGroupNamed("Objects");
		//CCDictionary *spawnPoint = objects->objectNamed("Player");
		//int x = spawnPoint->valueForKey("x")->intValue();
		//int y = spawnPoint->valueForKey("y")->intValue();



		// other things
		this->canFire = false;

		// bulletpool
		_bulletsInUse = new std::queue<CCSprite*>();
		_bulletsCanUse = new std::queue<CCSprite*>();

		CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache(); 
		cache->addSpriteFramesWithFile("yeti.plist");
		//cache->addSpriteFramesWithFile("tower.plist");
		cache->addSpriteFramesWithFile("towers.plist");
		cache->addSpriteFramesWithFile("towers_arcane.plist");
		cache->addSpriteFramesWithFile("ingame_gui.plist");
		cache->addSpriteFramesWithFile("common_spritesheet_16_a_2.plist");
		cache->addSpriteFramesWithFile("gui_menu_sprite_3.plist");
		
		//Tower information
		TowerInformation::getInstance()->LoadConfig(cache);


		// Tower
		CCDictionary* tower1 = objects->objectNamed("Tower1");
		int towerX = tower1->valueForKey("x")->intValue();
		int towerY = tower1->valueForKey("y")->intValue();

		this->mTower = Tower::create();
		this->mTower->myInit(eTower_Terrain::Terrain_Build_DarkGray);
		this->mTower->setPosition(CCPoint(towerX, towerY));
		this->addChild(this->mTower);

		this->addChild(TowerMenu::sharedTowerMenu());
		TowerMenu::sharedTowerMenu()->setVisible(false);

		// add animation
		//脚色动画
		// 
		addAnimationWithFramesToCache("yeti","yeti_move", 1, 25, SECOND_PER_FRAME * 2, true);
		addAnimationWithFramesToCache("magebolt","magebolt_boom", 3, 10, SECOND_PER_FRAME , false, 1);




		//enemise


		auto enemyManager = EnemyManager::sharedEnemyManager();
		//WayPoints
		enemyManager->readWayPoints(objects);

		enemyManager->setEnemyLayer(this);
		for (int i = 0; i < 1; ++i)
		{

			//enemy->setPosition(CCPoint(x, y));
			enemyManager->addEnemy("yeti_0001.png");
		}
		



		//this->setViewPointCenter(player->getPosition());


		this->setTouchEnabled(true);
		this->scheduleUpdate();
		//////////////////////////////////////////////////////////////////////////
		// add your codes below...
		//////////////////////////////////////////////////////////////////////////

		// 1. Add a menu item with "X" image, which is clicked to quit the program.

		//         // Create a "close" menu item with close icon, it's an auto release object.
		//         CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
		//             "CloseNormal.png",
		//             "CloseSelected.png",
		//             this,
		//             menu_selector(HelloWorld::menuCloseCallback));
		//         CC_BREAK_IF(! pCloseItem);
		// 
		//         // Place the menu item bottom-right conner.
		//         pCloseItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20));
		// 
		//         // Create a menu with the "close" menu item, it's an auto release object.
		//         CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
		//         pMenu->setPosition(CCPointZero);
		//         CC_BREAK_IF(! pMenu);
		// 
		//         // Add the menu to HelloWorld layer as a child layer.
		//         this->addChild(pMenu, 1);
		// 
		//         // 2. Add a label shows "Hello World".
		// 
		//         // Create a label and initialize with string "Hello World".
		//         CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", 24);
		//         CC_BREAK_IF(! pLabel);
		// 
		//         // Get window size and place the label upper. 
		//         CCSize size = CCDirector::sharedDirector()->getWinSize();
		//         pLabel->setPosition(ccp(size.width / 2, size.height - 50));
		// 
		//         // Add the label to HelloWorld layer as a child layer.
		//         this->addChild(pLabel, 1);
		// 
		//         // 3. Add add a splash screen, show the cocos2d splash image.
		//         CCSprite* pSprite = CCSprite::create("HelloWorld.png");
		//         CC_BREAK_IF(! pSprite);
		// 
		//         // Place the sprite on the center of the screen
		//         pSprite->setPosition(ccp(size.width/2, size.height/2));
		// 
		//         // Add the sprite to HelloWorld layer as a child layer.
		//         this->addChild(pSprite, 0);

		bRet = true;
	} while (0);

	return bRet;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
	// "close" menu item clicked
	CCDirector::sharedDirector()->end();
}

void HelloWorld::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}


void HelloWorld::setViewPointCenter(CCPoint pos)
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCSize tileSize = CCSize(this->_tileMap->getTileSize().width * this->_tileMap->getMapSize().width,
		this->_tileMap->getTileSize().height * this->_tileMap->getMapSize().height);



	int x = MAX(pos.x, winSize.width / 2 );
	int y = MAX(pos.y, winSize.height / 2 );

	//x = MIN(x, (this->_tileMap.mapSize.width * _tileMap.tileSize.width) 
	//	- winSize.width / 2);
	//y = MIN(y, (_tileMap.mapSize.height * _tileMap.tileSize.height) 
	//	- winSize.height/2);


	x = MIN(x, tileSize.width - winSize.width / 2 );
	y = MIN(y, tileSize.height - winSize.height / 2);
	CCPoint actualPosition = CCPoint(x, y);

	CCPoint centerOfView = CCPoint(winSize.width / 2, winSize.height / 2);
	CCPoint viewPoint = ccpSub(centerOfView, actualPosition);

	this->setPosition( viewPoint);

}
void HelloWorld::setPlayerPosition(cocos2d::CCPoint pos)
{
	//this->_player->setPosition(pos);

}
bool HelloWorld::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	return true;
}


void HelloWorld::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint touchLocation = pTouch->getLocationInView();
	//in OpenGl coordinates, (0, 0) is left-bottom point not like screen of dx coordinates is left-top point
	touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);
	touchLocation = this->convertToNodeSpace(touchLocation);
	CCLog("Background UI coor, x: %f, y: %f", touchLocation.x, touchLocation.y);
	//bullet
	if(this->canFire)
	{
// 		 		Bullet *bullet = Bullet::create(100, this->_player, "magebolt_0002.png");
// 				
// 					bullet->setPosition(touchLocation);
// 		 		//bullet->setScale(0.25);
// 			 		this->addChild(bullet);
//  		bullet->reuse();
		
		//this->mTower->fire(this->_player);
		return ;

	}

	EnemyManager::sharedEnemyManager()->runEnemiseOneByOne(1000);
	//start player moving
	// animation
	// 

	this->canFire = true;

	//动作, 暂时不用
	return ;
// 	do
// 	{
// 		//this->_player->runAction(CCMoveTo::create(1 ,touchLocation));
// 		ccBezierConfig bezierCfg;
// 		bezierCfg.endPosition = touchLocation;
// 
// 		CCPoint playerPos = _player->getPosition();
// 		CCPoint diff = ccpSub(touchLocation, playerPos);
// 
// 		CCPoint centerPoint = ccpMidpoint(playerPos, touchLocation);
// 
// 
// 		//bezierCfg.controlPoint_1 = ccpSub(centerPoint, ccpMult(diff, 0.3));
// 		//bezierCfg.controlPoint_2 = ccpAdd(centerPoint, ccpMult(diff, 0.3));
// 		bezierCfg.controlPoint_1 = playerPos;
// 
// 		//bezierCfg.controlPoint_1.x -= 100;
// 		bezierCfg.controlPoint_2 = centerPoint;
// 		bezierCfg.controlPoint_2.x -= 200;
// 
// 
// 
// 		//bezierCfg.controlPoint_1.x -= 50;
// 		//bezierCfg.controlPoint_2.x -= 50;
// 
// 
// 		// 	CCSprite *player = CCSprite::create("Player.png");
// 		// 	player->setPosition(centerPoint);
// 		// 	this->addChild(player);
// 
// 		CCSprite *player = CCSprite::create("Player.png");
// 		player->setPosition(bezierCfg.controlPoint_1);
// 		this->addChild(player);
// 
// 		player = CCSprite::create("Player.png");
// 		player->setPosition(bezierCfg.controlPoint_2);
// 		this->addChild(player);
// 
// 		player = CCSprite::create("Player.png");
// 		player->setPosition(touchLocation);
// 		this->addChild(player);
// 
// 
// 		this->_player->runAction(CCBezierTo::create(1,bezierCfg));
// 
// 	}while (false);
	//CCBezierBy


	return ;


	// 	if(abs(diff.x) > abs(diff.y))
	// 	{
	// 		if(diff.x > 0)
	// 		{
	// 			playerPos.x += this->_tileMap->getTileSize().width;
	// 		}
	// 		else
	// 		{
	// 			playerPos.x -= this->_tileMap->getTileSize().width;
	// 		}
	// 	}
	// 	else
	// 	{
	// 		if(diff.y > 0)
	// 		{
	// 			playerPos.y += this->_tileMap->getTileSize().height;
	// 		}
	// 		else
	// 		{
	// 			playerPos.y -= this->_tileMap->getTileSize().height;
	// 		}
	// 	}
	// 	if(playerPos.x <= (this->_tileMap->getMapSize().width * this->_tileMap->getTileSize().width) 
	// 		&& playerPos.y <= (this->_tileMap->getMapSize().height * this->_tileMap->getTileSize().height) 
	// 		&& playerPos.y >= 0.0f 
	// 		&& playerPos.x >= 0.0f
	// 		)
	// 	{
	// 		this->setPlayerPosition(playerPos);
	// 	}
	// 
	// 	this->setViewPointCenter(this->_player->getPosition());
}


void HelloWorld::update(float dt)
{

	EnemyManager::sharedEnemyManager()->update(dt);
}