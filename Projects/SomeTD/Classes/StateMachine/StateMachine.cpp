#include "StateMachine.h"

template <class Entity_Type>
StateMachine<Entity_Type>::StateMachine(Entity_Type* _owner)
	: current_state_(nullptr)
	, previous_state_(nullptr)
	, global_state_(nullptr)
{
	kkAssertMsg( _owner!= nullptr, "[StateMachine{constructor}] : owner is null!" );
	owner_ = _owner;
}


template <class Entity_Type>
StateMachine<Entity_Type>::~StateMachine(void)
{
	
}

template <class Entity_Type>
void StateMachine<Entity_Type>::Update(float dt)
{
	if(global_state_ != nullptr)
		global_state_->Update(owner_, dt);
	else if(current_state_ != nullptr)
		current_state_->Update(owner_, dt);
	else
		kkAssertMsg(false, "[StateMachine: {Update}]: No State Vaild!");
}

template <class Entity_Type>
bool StateMachine<Entity_Type>::HandleMessage(const MsgBase& _msg) const
{
	// first check if current state is valid 
	if (current_state_ != nullptr)
		return global_state_->OnMessage(owner_, _msg);
	// if not, check globle state
	else if(global_state_ != nullptr)
		return global_state_->OnMessage(owner_, _msg);
	else
		kkAssertMsg( false, "[StateMachine: {HandleMessage}]: No State Vaild!" );

	return false;
}

template <class Entity_Type>
void StateMachine<Entity_Type>::ChangeState(State<Entity_Type>* _new_state)
{
	kkAssertMsg( _new_state != nullptr && "[StateMachine: {HandleMessage}]: Trying to assign null state to current!" );

	//keep a record of the previous state
	previous_state_ = current_state_;

	//call the exit method of the existing state
	current_state_->Exit(owner_);

	//change state to the new state
	current_state_ = _new_state;

	//call the entry method of the new state
	current_state_->Enter(owner_);
}


template <class Entity_Type>
void StateMachine<Entity_Type>::RevertToPreviousState()
{
	ChangeState(previous_state_);
}

template <class Entity_Type>
bool StateMachine<Entity_Type>::IsInState( const State<Entity_Type>& _state )const
{
	if (strcmp(_state.state_name(), current_state()) == 0 )
		return true;
	return false;
}