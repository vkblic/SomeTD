#include "GameLayer.h"

using namespace cocos2d;
namespace SomeTD
{
	namespace UI
	{
		CCScene* GameLayer::scene()
		{
			CCScene * scene = NULL;
			do 
			{
				// 'scene' is an autorelease object
				scene = CCScene::create();
				CC_BREAK_IF(! scene);

				// 'layer' is an autorelease object
				GameLayer *layer = GameLayer::create();
				CC_BREAK_IF(! layer);

				// add layer as a child to scene
				scene->addChild(layer);
			} while (0);

			// return the scene
			return scene;
		}
		bool GameLayer::init()
		{
			bool bRet = false;
			do 
			{
				if(!CCLayer::init())
					break;
				this->_gameState = GameState::Playing;

				CCSize winSize = CCDirector::sharedDirector()->getWinSize();
				//score
				this->_labelScore = CCLabelBMFont::create("Score: 0", "arial-14.fnt");
				this->_labelScore->setAnchorPoint(CCPoint(1.0f, 0.0f));
				this->_labelScore->setAlignment(CCTextAlignment::kCCTextAlignmentRight);
				this->addChild(this->_labelScore, 1000);
				this->_labelScore->setPosition(CCPoint(winSize.width - 5, winSize.height - 5));

				// ship life
				auto shitTexture = CCTextureCache::sharedTextureCache()->addImage("ship01.png");
				auto life = CCSprite::createWithTexture(shitTexture, CCRect(0.0f, 0.0f, 60.0f, 38.0f));
				life->setScale(0.6f);
				life->setPosition(CCPoint(30.0f, 460.0f));
				this->addChild(life, 1, 5);

				// ship life count
				this->_labelLife = CCLabelTTF::create("0", "Arial", 20);
				this->_labelLife->setPosition(CCPoint(60, 463));
				this->_labelLife->setColor(ccRED);
				this->addChild(this->_labelLife, 1000);

				// ship 

				// accept touch now!

				auto deviceType = CCApplication::sharedApplication()->getTargetPlatform();
				switch (deviceType)
				{
				case TargetPlatform::kTargetAndroid:
				case TargetPlatform::kTargetIpad:
				case TargetPlatform::kTargetIphone:
					{
						this->setTouchEnabled(true);
					}
					break;
				case TargetPlatform::kTargetWindows:
				case TargetPlatform::kTargetMacOS:
					{

					}
					break;
				}

				// schedule
				this->scheduleUpdate();
				this->schedule((SEL_SCHEDULE)&GameLayer::scoreCounter, 1);

				//music
				if (true)
				{
				}


				bRet = true;
			} while (false);
			return bRet;
		}
		void GameLayer::scoreCounter(float)
		{
			if (this->_gameState == GameState::Playing)
			{
				this->_time++;

				//std::string minute = itoa(this->_time / 60);
				//auto second = this->_time % 60;
				///minute = minute > 9 ? minute : "0" + minute;
				//second = second > 9 ? second : "0" + second;
			}
		}

		void GameLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
		{
			//this->processEvent()
		}

	}

}