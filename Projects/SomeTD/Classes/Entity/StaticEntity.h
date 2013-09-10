
#ifndef _STATIC_ENTITY_
#define _STATIC_ENTITY_

#include "Entity.h"

#include "cocos2d.h"

#include "../Model/Models.h"

using namespace cocos2d;

namespace SomeTD
{

	class StaticEntity : public BaseEntity
	{

	public:
		CCRect getCollisionRect();



	protected:

		virtual bool __MyInit(CCSpriteFrame* _defual_frame);

		CCSpriteFrame* default_frame_;

	};



	//typedef void (Tower::*SEL_MenuTouchedFunc)(int);

	//#define towerMenuCallFunc(func) (SEL_MenuTouchedFunc)(&func)


}
#endif