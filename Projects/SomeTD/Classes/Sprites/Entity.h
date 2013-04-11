
#ifndef _ENTITY_
#define _ENTITY_

#include "cocos2d.h"
#include "../MessagePump/MsgObject.h"
#include "../Common/Common.h"
using namespace cocos2d;


class Entity : public CCSprite
{

protected:
	entity_id mEntityID;
	FSM_Machine mFSM_Machine;
public: 
	entity_id getEntityID() { return mEntityID; }
	void setEntityID( entity_id id ) { mEntityID = id; }

	entity_id getFSM_Machine() { return mFSM_Machine; }
	void setFSM_Machine( FSM_Machine machine ) { mFSM_Machine = machine; }
};



#endif