#ifndef _HERO_ENTITY_
#define _HERO_ENTITY_

#include "StaticEntity.h"
#include "./StateMachine/StateMachine.h"
#include <memory>
using namespace cocos2d;

namespace SomeTD
{

	class HeroEntity : public StaticEntity
	{
	private:
		StateMachine<HeroEntity>* state_machine;

	};



	//typedef void (Tower::*SEL_MenuTouchedFunc)(int);

	//#define towerMenuCallFunc(func) (SEL_MenuTouchedFunc)(&func)


}
#endif