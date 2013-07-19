#include "HelloWorldScene.h"

using namespace cocos2d;

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
		
		bRet = true;
	} while (0);

	return bRet;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
	// "close" menu item clicked
	CCDirector::sharedDirector()->end();
}
