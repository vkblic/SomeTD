
#ifndef _ENTITY_
#define _ENTITY_

#include "cocos2d.h"
#include "../MessagePump/MsgObject.h"
#include "../Common/Common.h"
using namespace cocos2d;


class Entity : public CCSprite
{

protected:
	ENTITY_ID mEntityID;
	FSM_Machine mFSM_Machine;
public: 
	ENTITY_ID getEntityID() { return mEntityID; }
	void setEntityID( ENTITY_ID id ) { mEntityID = id; }

	ENTITY_ID getFSM_Machine() { return mFSM_Machine; }
	void setFSM_Machine( FSM_Machine machine ) { mFSM_Machine = machine; }
};



#endif