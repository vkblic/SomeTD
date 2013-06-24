#pragma once

#pragma region Base

struct MsgObject;

template<typename entity_type>
class State
{
protected:
	State()
	{
		std::string s(typeid(*m_pCurrentState).name());
		CC_ASSERT(s.length() > 5 && "[StateBase:{State}]: type error!");

		mType = s.substr(6);
	}
public:

	virtual ~State(){}

	// this will execute when the state is entered
	virtual void Enter(entity_type* entity) = 0;

	// this is the states normal update function,
	// it executes every frame or every normal update trigger
	virtual void Update(entity_type* entity, float dt) = 0;

	// this will execute when the state is exited.
	virtual void Exit(entity_type* entity) = 0;

	// this call by message dispatcher, when these has a message to entity.
	virtual bool OnMessage(entity_type* entity, const MsgObject& msg) = 0;

	virtual const std::string& GetType() const { return mType; }

private:
	std::string mType;
};





#pragma endregion
