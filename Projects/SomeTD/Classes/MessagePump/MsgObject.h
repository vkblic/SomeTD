
#ifndef _MSG_OBJECT_
#define _MSG_OBJECT_
#include "../Common/Common.h"
#include "cocos2d.h"
using namespace cocos2d;
enum MsgName
{ 
	MSG_NULL,
	MSG_RESERVED_Enter,		
	MSG_RESERVED_Exit,		
	MSG_RESERVED_Update,	
	MSG_Timeout,
	MSG_ChangeState,
	MSG_FoundTarget,
	MSG_CommandMove,
	MSG_TargetNotAvailable,
	MSG_AttackerNoAvailable,
	MSG_RequestPosition,
	MSG_ReceivePosition,
	MSG_Damage,

	//enemy
	MSG_StopMoving,
	MSG_ArriveEndPoint,
	//ally
	MSG_InAttackPosition,
	MSG_InPostion,



	MSG_MAX,

};




enum FSM_Machine
{
	FSM_Ally,
	FSM_Enemy,
	FSM_Tower
};

struct MsgObject
{
	MsgName name;				//name of message (an enumerated type works well)
	ENTITY_ID sender_id;		//unique id of sender
	ENTITY_ID receiver_id;	//unique id of receiver
	float delivery_time;		//deliver message at this time

	//Note that the sender_id and receiver_id are not pointers to game objects.
	//Since messages can be delayed, the sender or receiver may get removed
	//from the game and a pointer would become dangerously invalid.
	//friend bool operator < (MsgObject& a, MsgObject& b)
	//{
	//	return a.delivery_time > b.delivery_time; //the less delivery_time is, the higher priority
	//}

} ;

struct CollisionRectMsg : public MsgObject
{
	CCRect rect;
};

struct MsgDamage : public MsgObject
{
	CCRect senderCollisionRect;
	int damage;

};

#endif