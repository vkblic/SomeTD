#ifndef _GAME_LAYER_H_
#define _GAME_LAYER_H_
#include "cocos2d.h"
#include "./label_nodes/CCLabelBMFont.h"
namespace SomeTD
{
	namespace UI
	{
		
		class GameLayer : public cocos2d::CCLayer
		{
			enum GameState
			{
				Playing,
				GameOver
			};
		public:
			// framework need method
			virtual bool init();

			static cocos2d::CCScene* scene();

		public:
			CREATE_FUNC(GameLayer);

			void scoreCounter(float);

			virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

			void processEvent(cocos2d::CCEvent* pEvent);

		private:
			GameState _gameState;

			cocos2d::CCLabelBMFont* _labelScore;
			cocos2d::CCLabelTTF* _labelLife;

			int _time;
		};

		
	}
}
#endif