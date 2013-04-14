#include "MsgRoute.h"
#include "../Common/Common.h"
#include "../Managers/AllyManager.h"
#include "../Managers/EnemyManager.h"
#include "../Managers/EntityManager.h"

MsgRoute* MsgRoute::mInstance = nullptr;
MsgRoute* MsgRoute::sharedMsgRount()
{
	if(mInstance == nullptr)
		mInstance = new MsgRoute();
	return mInstance;
}
MsgRoute::MsgRoute()
	: mCurTick(0)
{
	mMsgNameStr.resize(MSG_MAX);
	mMsgNameStr[MSG_NULL] = "MSG_NULL";
	mMsgNameStr[MSG_RESERVED_Enter] = "MSG_RESERVED_Enter";
	mMsgNameStr[MSG_RESERVED_Exit] = "MSG_RESERVED_Exit";
	mMsgNameStr[MSG_RESERVED_Update] = "MSG_RESERVED_Update";
	mMsgNameStr[MSG_Timeout] = "MSG_Timeout";
	mMsgNameStr[MSG_FoundTarget] = "MSG_FoundTarget";
	mMsgNameStr[MSG_CommandMove] = "MSG_CommandMove";
	mMsgNameStr[MSG_InAttackPosition] = "MSG_InAttackPosition";
	mMsgNameStr[MSG_TargetNotAvailable] = "MSG_TargetNotAvailable";
	mMsgNameStr[MSG_AttackerNoAvailable] = "MSG_AttackerNoAvailable";
	mMsgNameStr[MSG_RequestPosition] = "MSG_RequestPosition";
	mMsgNameStr[MSG_ReceivePosition] = "MSG_ReceivePosition";
	mMsgNameStr[MSG_Damage] = "MSG_Damage";
	mMsgNameStr[MSG_StopMoving] = "MSG_StopMoving";
	mMsgNameStr[MSG_ArriveEndPoint] = "MSG_ArriveEndPoint";
	
	mStateNameStr.resize(STATE_MAX);
	mStateNameStr[STATE_NULL] = "STATE_NULL";
	mStateNameStr[STATE_Idle] = "STATE_Idle";
	mStateNameStr[STATE_Moving] = "STATE_Moving";
	mStateNameStr[STATE_Stoped] = "STATE_Stoped";
	mStateNameStr[STATE_MovingWithAttack] = "STATE_MovingWithAttack";
	mStateNameStr[STATE_MovingToTarget] = "STATE_MovingToTarget";
	mStateNameStr[STATE_Attacking] = "STATE_Attacking";
	mStateNameStr[STATE_Dead] = "STATE_Dead";


}

MsgRoute::~MsgRoute()
{

}

void MsgRoute::sendMsg( MsgName name, entity_id senderID, entity_id receiverID )
{
	MsgObject msg;
	msg.name = name;
	msg.sender_id = senderID;
	msg.receiver_id = receiverID;
	msg.delivery_time = mCurTick;
	this->routeMessage(msg);
}

void MsgRoute::sendMsg(const MsgObject& msg)
{
	this->routeMessage(msg);
}

void MsgRoute::sendDelayedMsg( MsgName name, int delay, entity_id senderID, entity_id receiverID )
{
	MsgObject msg;
	msg.name = name;
	msg.sender_id = senderID;
	msg.receiver_id = receiverID;
	kkAssertMsg(delay > 0, "[MsgRoute::sendDelayedMsg], delay must higter than 0!");
	msg.delivery_time = mCurTick + delay;
	this->routeMessage(msg);
}

void MsgRoute::routeMessage(const MsgObject& msg )
{
	if (msg.delivery_time > mCurTick)
	{
		this->restoreDelayedMsg(msg);
		return;
	}

	auto gameObj = EntityManager::sharedEntityManager()->getEntity(msg.receiver_id);
	if(gameObj == nullptr)
	{
		CCLog(" [ %d --> %d] [%s] [%s]", msg.sender_id, msg.receiver_id, getMsgNameStr(msg.name));
		kkAssertMsgf(false, "[MsgRoute::routeMessage] can't get entity from EntityManager!");
	}
	switch (gameObj->getFSM_Machine())
	{
	case FSM_Ally:
		{
			CCLog("[-->FSM_Ally] [ %d --> %d] [%s] [%s] [entityID: %d]", msg.sender_id, msg.receiver_id, getMsgNameStr(msg.name), getStateNameStr(static_cast<ActiveEntity*>(gameObj)->getState()), gameObj->getEntityID());
			AllyManager::sharedAllyManager()->fsmTranslater(msg, static_cast<AllyUnit*>(gameObj));
		}
		break;
	case FSM_Enemy:
		{
			CCLog("[-->FSM_Enemy] [ %d --> %d] [%s] [%s] [entityID: %d]", msg.sender_id, msg.receiver_id, getMsgNameStr(msg.name), getStateNameStr(static_cast<ActiveEntity*>(gameObj)->getState()), gameObj->getEntityID());
			EnemyManager::sharedEnemyManager()->fsmTranslater(msg, static_cast<EnemyUnit*>(gameObj));
		}
		break;
	case FSM_Tower:
		{

		}
		break;
	default:
		kkAssertMsg(false, "[MsgRoute::routeMessage] no FSM Machine found!");
		break;
	}

}
void MsgRoute::restoreDelayedMsg(const MsgObject& msg)
{
	mMsgQueue.push(msg);
}

void MsgRoute::routeDelayedMessages()
{
	while(true)
	{
		if( mMsgQueue.size() == 0)
			return;
		if (mMsgQueue.top().delivery_time > mCurTick)
			break;
		this->routeMessage(mMsgQueue.top());
		mMsgQueue.pop();
		
	}
}