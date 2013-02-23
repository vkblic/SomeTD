#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

#include "Box2D/Box2D.h"

#include "SimpleAudioEngine.h"
namespace SomeTD
{
	namespace UI
	{

		class MainMenu : public cocos2d::CCLayer
		{
		public:
			// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
			virtual bool init();  

			void CreateActions();
			// there's no 'id' in cpp, so we recommand to return the exactly class pointer
			static cocos2d::CCScene* scene();


			// selectors
		public:	

			// a selector callback -- "NewGame"
			void onNewGame(CCObject* pSender);

			// a selector callback -- "Setting"
			void onSettings(CCObject* pSender);

			// a selector callback -- "About"
			void onAbout(CCObject* pSender);

			// implement the "static node()" method manually
			CREATE_FUNC(MainMenu);

			// update method
			void update(float dt);

		private:
			cocos2d::CCSprite *_ship;
			cocos2d::CCSize _winSize;

		private:
			void flareEffect();
		};

	}
}
#endif  // __HELLOWORLD_SCENE_H__

