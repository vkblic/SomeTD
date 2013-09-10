#pragma once
#include "State.h"
template <class Entity_Type>
class StateMachine
{
public:
	StateMachine(Entity_Type* owner);
	virtual ~StateMachine(void);

public:

	// use to initialize the FSM
	void set_current_state(State<Entity_Type>* _state)	 { current_state_ = _state; }
	void set_previous_state(State<Entity_Type>* _state) { previous_state_ = _state; }
	void set_global_state(State<Entity_Type>* _state)	 { global_state_ = _state; }

	State<Entity_Type>*  current_state()  const { return current_state_; }
	State<Entity_Type>*  global_state()   const { return global_state_; }
	State<Entity_Type>*  previous_state() const { return previous_state_; }

	void Update(float _dt);
	bool HandleMessage(const MsgBase& _msg) const;

	void ChangeState(State<Entity_Type>* _new_state);

	//change state back to the previous state
	void  RevertToPreviousState();

	//returns true if the current state's type is equal to the type of the
	//class passed as a parameter. 
	bool  IsInState(const State<Entity_Type>& _state) const;


private:

	Entity_Type*			owner_;
	State<Entity_Type>*		current_state_;

	// a record of the last state, use for global state
	State<Entity_Type>*		previous_state_;
	State<Entity_Type>*		global_state_;

};