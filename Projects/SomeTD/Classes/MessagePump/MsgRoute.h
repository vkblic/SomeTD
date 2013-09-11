
#ifndef _MSG_ROUTE_
#define _MSG_ROUTE_
#include "MsgObject.h"
#include "../Model/Models.h"
#include <queue>
#include <map>
#include <vector>

class MsgRoute
{
	
public:
	~MsgRoute();
	static MsgRoute* sharedMsgRount();
private:
	MsgRoute();
	static MsgRoute* mInstance;

public:
	void sendMsg( MsgName name, ENTITY_ID senderID, ENTITY_ID receiverID );
	void sendMsg(const MsgBase& msg);
	void sendDelayedMsg( MsgName name, int delay, ENTITY_ID senderID, ENTITY_ID receiverID );
	//void broadcaseMsg(const MsgObject& msg);
	void routeMessage(const MsgBase& msg );
	void routeDelayedMessages();
	void restoreDelayedMsg(const MsgBase& msg);
	const unsigned long& getTick() {return mCurTick;}
	void TickRun(){ mCurTick++; }
private:
	struct msgCompare
	{
		bool operator() (const MsgBase& first, const MsgBase& second)
		{
			return first.delivery_time > second.delivery_time;
		}
	};
	std::priority_queue<MsgBase, std::vector<MsgBase>, msgCompare> mMsgQueue;
	unsigned long mCurTick;


	//for debug

	std::vector<std::string> mMsgNameStr;
	std::vector<std::string> mStateNameStr;

	const char* getMsgNameStr(MsgName name) {return mMsgNameStr[name].c_str();}
	const char* getStateNameStr(ActiveObj_States name) {return mStateNameStr[name].c_str();}
};

#endif