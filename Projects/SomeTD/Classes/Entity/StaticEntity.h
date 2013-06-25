
#ifndef _STATIC_ENTITY_
#define _STATIC_ENTITY_

#include "cocos2d.h"
#include "Entity.h"
#include "../Model/Models.h"
using namespace cocos2d;

namespace SomeTD
{

	class StaticEntity : public BaseEntity
	{

	public:
		CCRect getCollisionRect();



	protected:

		virtual bool myInit(CCSpriteFrame* defaultFrame);

		CCSpriteFrame* mDefaultFrame;

	};



	//typedef void (Tower::*SEL_MenuTouchedFunc)(int);

	//#define towerMenuCallFunc(func) (SEL_MenuTouchedFunc)(&func)


}
#endif