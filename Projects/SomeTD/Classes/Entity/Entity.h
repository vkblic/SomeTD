
#ifndef _ENTITY_
#define _ENTITY_

#include "cocos2d.h"
#include "../StateMachine/StateMachine.h"
#include "../Common/Common.h"
using namespace cocos2d;

namespace SomeTD
{
	struct MsgBase;

	class BaseEntity : public CCSprite
	{
	protected:
		ENTITY_ID entity_id;
	public: 
		ENTITY_ID entity_id() { return entity_id; }
		void set_entity_id( ENTITY_ID id ) { entity_id = id; }

		virtual bool HandleMessage(const MsgBase& msg) = 0;
	};
}

#endif