#include "HelloWorldScene.h"
#include "./libs/tinyxml2.h"
using namespace cocos2d;
using namespace tinyxml2;

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

void rootFirst(tinyxml2::XMLNode* node, int lv)
{

	CCLog("%s, lv: %d",node->ToElement()->Name(), lv);
	char buffer[1024] ;
	buffer[0] = '\0';

	auto attribute = node->ToElement()->FirstAttribute();
	while(attribute)
	{
		sprintf(buffer + strlen(buffer), "%s: %s    ", attribute->Name(), attribute->Value());
		attribute = attribute->Next();
	}
	CCLog(buffer);

	//child first
	if(!node->NoChildren())
		rootFirst(node->FirstChild(), lv + 1) ;

	// handle all sibling
	do 
	{
		if (node->NextSibling())
			rootFirst(node->NextSibling(), lv) ;
		node = node->NextSibling() ;
	} while (node);


	return ;
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

		CC_BREAK_IF(! CCLayer::init());

		//////////////////////////////////////////////////////////////////////////
		// add your codes below...
		//////////////////////////////////////////////////////////////////////////

		// 1. Add a menu item with "X" image, which is clicked to quit the program.

		// Create a "close" menu item with close icon, it's an auto release object.
		CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
			"CloseNormal.png",
			"CloseSelected.png",
			this,
			menu_selector(HelloWorld::menuCloseCallback));
		CC_BREAK_IF(! pCloseItem);

		// Place the menu item bottom-right conner.
		pCloseItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20));

		// Create a menu with the "close" menu item, it's an auto release object.
		CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
		pMenu->setPosition(CCPointZero);
		CC_BREAK_IF(! pMenu);

		// Add the menu to HelloWorld layer as a child layer.
		this->addChild(pMenu, 1);

		// 2. Add a label shows "Hello World".

		// Create a label and initialize with string "Hello World".
		CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", 24);
		CC_BREAK_IF(! pLabel);

		// Get window size and place the label upper. 
		CCSize size = CCDirector::sharedDirector()->getWinSize();
		pLabel->setPosition(ccp(size.width / 2, size.height - 50));

		// Add the label to HelloWorld layer as a child layer.
		this->addChild(pLabel, 1);

		// 3. Add add a splash screen, show the cocos2d splash image.
		CCSprite* pSprite = CCSprite::create("HelloWorld.png");
		CC_BREAK_IF(! pSprite);

		// Place the sprite on the center of the screen
		pSprite->setPosition(ccp(size.width/2, size.height/2));

		// Add the sprite to HelloWorld layer as a child layer.
		this->addChild(pSprite, 0);




		// Read Xml test
		// 1. 

		tinyxml2::XMLDocument doc;
		doc.LoadFile( "D:/App1/App1/BlankPage.xaml" );
		int re = doc.ErrorID();


		//CCLog("Root Child: %s", doc.FirstChild()->ToElement()->Name());

		rootFirst(doc.FirstChild(), 0);


		bRet = true;
	} while (0);

	return bRet;
}



void HelloWorld::menuCloseCallback(CCObject* pSender)
{
	// "close" menu item clicked
	CCDirector::sharedDirector()->end();
}

