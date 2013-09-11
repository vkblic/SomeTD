#pragma once

#pragma region Base

struct MsgBase;

template<typename Entity_Type>
class State
{
protected:
	State(){}
public:

	virtual ~State(){}

	// this will execute when the state is entered
	virtual void Enter(Entity_Type* entity) = 0;

	// this is the states normal update function,
	// it executes every frame or every normal update trigger
	virtual void Update(Entity_Type* entity, float dt) = 0;

	// this will execute when the state is exited.
	virtual void Exit(Entity_Type* entity) = 0;

	// this call by message dispatcher, when these has a message to entity.
	virtual bool OnMessage(Entity_Type* entity, const MsgBase& msg) = 0;

	
	virtual const char* state_name() = 0;

};

template< typename 




#pragma endregion
