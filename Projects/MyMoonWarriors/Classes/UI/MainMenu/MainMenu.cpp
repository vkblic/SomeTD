#include "MainMenu.h"
#include ".\textures\CCTextureCache.h"
#include ".\SimpleAudioEngine.h"
using namespace cocos2d;
namespace SomeTD
{
	namespace UI
	{

		CCScene* MainMenu::scene()
		{
			CCScene * scene = NULL;
			do 
			{
				// 'scene' is an autorelease object
				scene = CCScene::create();
				CC_BREAK_IF(! scene);

				// 'layer' is an autorelease object
				MainMenu *layer = MainMenu::create();
				CC_BREAK_IF(! layer);

				// add layer as a child to scene
				scene->addChild(layer);
			} while (0);

			// return the scene
			return scene;
		}

		void MainMenu::CreateActions()
		{
			//	CCAction* action = CCBlink::actionWithDuration(10, 20);

		}
		// on "init" you need to initialize your instance
		bool MainMenu::init()
		{


			bool bRet = false;
			do 
			{
				//////////////////////////////////////////////////////////////////////////
				// super init first
				//////////////////////////////////////////////////////////////////////////

				if (! CCLayer::init())
				{
					break;
				}
				//////////////////////////////////////////////////////////////////////////
				// add your codes below...
				//////////////////////////////////////////////////////////////////////////

				// 1. add loading 
				CCSprite *pLoadSprite= CCSprite::create("loading.png");
				pLoadSprite->setAnchorPoint(CCPoint(0,0));
				this->addChild(pLoadSprite, 0, 1);

				// 2. add logo
				CCSprite* pLogo = CCSprite::create("logo.png");
				pLogo->setAnchorPoint(CCPoint(0,0));
				pLogo->setPosition(CCPoint(0, 320));
				this->addChild(pLogo, 10, 1);

				//menu.png




				// 3. Add menu items 
				// 3.1. NewGame button 
				// 
				CCSprite* pNewGameNormal = CCSprite::create("menu.png", CCRect(0, 0, 126, 33));
				CCSprite* pNewGameSelected = CCSprite::create("menu.png", CCRect(0, 33, 126, 33));
				CCSprite* pNewGameDisabled = CCSprite::create("menu.png", CCRect(0, 33 * 2, 126, 33));

				CCMenuItemSprite * pNewGameBtn = CCMenuItemSprite::create(
					pNewGameNormal,
					pNewGameSelected,
					pNewGameDisabled,
					this,
					menu_selector(MainMenu::onNewGame)
					);
				if(! pNewGameBtn)
					break;
				// 3.2. GameSetting button 
				// 
				CCSprite* pGameSettingsNormal = CCSprite::create("menu.png", CCRect(126, 0, 126, 33));
				CCSprite* pGameSettingsSelected = CCSprite::create("menu.png", CCRect(126, 33, 126, 33));
				CCSprite* pGameSettingsDisabled = CCSprite::create("menu.png", CCRect(126, 33 * 2, 126, 33));

				CCMenuItemSprite * pGameSettingsBtn = CCMenuItemSprite::create(
					pGameSettingsNormal,
					pGameSettingsSelected,
					pGameSettingsDisabled,
					this,
					menu_selector(MainMenu::onSettings)
					// 			[this](CCObject* pSender)
					// 		{
					// 			// "close" menu item clicked
					// 			//CCDirector::sharedDirector()->end();
					// 			this->flareEffect(); 
					// 		}

					);
				if(! pGameSettingsBtn)
					break;
				// 3.2. GameSetting button 
				// 
				CCSprite* pAboutNormal = CCSprite::create("menu.png", CCRect(252, 0, 126, 33));
				CCSprite* pAboutSelected = CCSprite::create("menu.png", CCRect(252, 33, 126, 33));
				CCSprite* pAboutDisabled = CCSprite::create("menu.png", CCRect(252, 33 * 2, 126, 33));

				CCMenuItemSprite * pAboutBtn = CCMenuItemSprite::create(
					pAboutNormal,
					pAboutSelected,
					pAboutDisabled,
					this,
					menu_selector(MainMenu::onAbout)
					);
				if(! pAboutBtn)
					break;
				this->_winSize = CCDirector::sharedDirector()->getWinSize();

				// 3.3. Main menu
				CCMenu* pMenu = CCMenu::create(pNewGameBtn, pGameSettingsBtn, pAboutBtn, NULL);
				pMenu->setPosition(CCPointZero);
				if(! pMenu)
					break;
				pMenu->alignItemsVerticallyWithPadding(10);
				this->addChild(pMenu, 1, 2);
				pMenu->setPosition(ccp(_winSize.width / 2, _winSize.height / 2));
				//this->schedule(update, 0.1);

				// 3.4
				CCTexture2D *tempShip = CCTextureCache::sharedTextureCache()->addImage("ship01.png");
				this->_ship	 = CCSprite::createWithTexture(tempShip, CCRect(0, 45, 60, 38));
				this->addChild(this->_ship, 0, 4);
				CCPoint pos = ccp(0.1 * _winSize.width, 0);
				this->_ship->setPosition(pos);
				this->_ship->runAction(CCMoveBy::create(2, CCPoint(0.5 * _winSize.width, pos.y + _winSize.height + 100)));

				CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.7f);
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Music\\mainMainMusic.mp3");
				this->scheduleUpdate();
				//// 1. Add a menu item with "X" image, which is clicked to quit the program.

				//// Create a "close" menu item with close icon, it's an auto release object.
				//CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
				//    "CloseNormal.png",
				//    "CloseSelected.png",
				//    this,
				//    menu_selector(HelloWorld::onAbout));
				//CC_BREAK_IF(! pCloseItem);

				//// Place the menu item bottom-right conner.
				//pCloseItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20));

				//// Create a menu with the "close" menu item, it's an auto release object.
				//CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
				//pMenu->setPosition(CCPointZero);
				//CC_BREAK_IF(! pMenu);

				//// Add the menu to HelloWorld layer as a child layer.
				//this->addChild(pMenu, 1);

				//// 2. Add a label shows "Hello World".

				//// Create a label and initialize with string "Hello World".
				//CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", 24);
				//CC_BREAK_IF(! pLabel);

				//// Get window size and place the label upper. 
				//CCSize size = CCDirector::sharedDirector()->getWinSize();
				//pLabel->setPosition(ccp(size.width / 2, size.height - 50));

				//// Add the label to HelloWorld layer as a child layer.
				//this->addChild(pLabel, 1);

				//// 3. Add add a splash screen, show the cocos2d splash image.
				//CCSprite* pSprite = CCSprite::create("HelloWorld.png");
				//CC_BREAK_IF(! pSprite);

				//// Place the sprite on the center of the screen
				//pSprite->setPosition(ccp(size.width/2, size.height/2));

				//// Add the sprite to HelloWorld layer as a child layer.
				//this->addChild(pSprite, 0);

				bRet = true;
			} while (0);

			return bRet;
		}

		void MainMenu::onNewGame(CCObject* pSender)
		{
			// "close" menu item clicked
			//CCDirector::sharedDirector()->end();
			flareEffect();
		}

		void MainMenu::onSettings(CCObject* pSender)
		{
			// "close" menu item clicked
			CCTextureCache::sharedTextureCache()->dumpCachedTextureInfo();
			//CCDirector::sharedDirector()->end();
		}

		void MainMenu::onAbout(CCObject* pSender)
		{
			// "close" menu item clicked
			CCDirector::sharedDirector()->end();
		}


		void MainMenu::update(float dt)
		{
			if( this->_ship->getPosition().y > this->_winSize.height)
			{
				int a  = 0;
				CCPoint pos = CCPoint((dt / 100.0f) * this->_winSize.width, 10);
				this->_ship->setPosition(pos);
				this->_ship->runAction( CCMoveBy::create(2, CCPoint(0.5 * _winSize.width, pos.y + _winSize.height + 100)));
			}
		}


		void MainMenu::flareEffect()
		{
			auto flare = CCSprite::create("flare.jpg");
			_ccBlendFunc blendFunc = {0x0302, 1};
			flare->setBlendFunc(blendFunc);

			this->addChild(flare, 10.0f);
			flare->setOpacity(0.0f);
			flare->setPosition( CCPoint(-30.0f, 297.0f) );
			flare->setRotation(-120.0f);
			flare->setScale(0.2f);


			auto opacityAnim = CCFadeTo::create(0.5f, 255);
			auto opacDim = CCFadeTo::create(1.0f, 0);
			auto biggeAnim = CCScaleBy::create(0.7f, 1.2f, 1.2f);
			auto biggerEase = CCEaseSineOut::create(biggeAnim);
			auto moveAnim = CCMoveBy::create(0.5f, CCPoint(328.0f, 0.0f));
			auto easeMove = CCEaseSineOut::create(moveAnim);
			auto rotateAnim = CCRotateBy::create(2.5f, 90.0f);
			auto rotateEase = CCEaseExponentialOut::create(rotateAnim);
			auto bigger = CCScaleTo::create(0.5f, 1.0f);

			flare->runAction(CCSequence::create(opacityAnim, biggerEase, opacDim, NULL/*, killflare, onComplete*/));
			flare->runAction(easeMove);
			flare->runAction(rotateEase);
			flare->runAction(bigger);

		}
	}
}