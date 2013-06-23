#pragma once
#include "State.h"
template <class entity_type>
class StateMachine
{
public:
	StateMachine(entity_type* owner);
	virtual ~StateMachine(void);

public:

	// use to initialize the FSM
	void SetCurrentState(State<entity_type>* state)	 { m_pCurrentState = state; }
	void SetPreviousState(State<entity_type>* state) { m_pPreviousState = state; }
	void SetGlobalState(State<entity_type>* state)	 { m_pGlobalState = state; }

	State<entity_type>*  GetCurrentState()  const { return m_pCurrentState; }
	State<entity_type>*  GetGlobalState()   const { return m_pGlobalState; }
	State<entity_type>*  GetPreviousState() const { return m_pPreviousState; }

	void Update(float dt)
	{
		if(m_pGlobalState != nullptr)
			m_pGlobalState->Update(m_pOwner, dt);
		else if(m_pCurrentState != nullptr)
			m_pCurrentState->Update(m_pOwner, dt);
		else
			CC_ASSERT("[StateMachine: {Update}]: No State Vaild!");
	}


	bool HandleMessage(const MsgObject& msg) const
	{
		// first check if current state is valid 
		if (m_pCurrentState != nullptr)
			return m_pGlobalState->OnMessage(m_pOwner, msg);
		// if not, check globle state
		else if(m_pGlobalState != nullptr)
			return m_pGlobalState->OnMessage(m_pOwner, msg);
		else
			CC_ASSERT("[StateMachine: {HandleMessage}]: No State Vaild!");
		
		return false;
	}

	void ChangeState(State<entity_type>* newState)
	{
		CC_ASSERT(newState != nullptr && "[StateMachine: {HandleMessage}]: Trying to assign null state to current!");

		//keep a record of the previous state
		m_pPreviousState = m_pCurrentState;

		//call the exit method of the existing state
		m_pCurrentState->Exit(m_pOwner);

		//change state to the new state
		m_pCurrentState = newState;

		//call the entry method of the new state
		m_pCurrentState->Enter(m_pOwner);
	}

	//change state back to the previous state
	void  RevertToPreviousState()
	{
		ChangeState(m_pPreviousState);
	}

	//returns true if the current state's type is equal to the type of the
	//class passed as a parameter. 
	bool  isInState(const State<entity_type>& st)const
	{
		if (typeid(*m_pCurrentState) == typeid(st)) return true;
		return false;
	}


private:

	entity_type*			m_pOwner;
	State<entity_type>*		m_pCurrentState;

	// a record of the last state, use for global state
	State<entity_type>*		m_pPreviousState;
	State<entity_type>*		m_pGlobalState;

	
};

