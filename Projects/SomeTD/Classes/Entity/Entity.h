
#ifndef _ENTITY_
#define _ENTITY_

#include "cocos2d.h"
#include "../StateMachine/StateMachine.h"
#include "../Common/Common.h"
using namespace cocos2d;

namespace SomeTD
{
	struct MsgObject;

	class BaseEntity : public CCSprite
	{
	protected:
		entity_id mEntityID;
	public: 
		entity_id getEntityID() { return mEntityID; }
		void setEntityID( entity_id id ) { mEntityID = id; }

		virtual bool HandleMessage(const MsgObject& msg) = 0;
	};
}

#endif