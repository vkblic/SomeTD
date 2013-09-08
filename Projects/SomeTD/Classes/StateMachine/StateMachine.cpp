#include "StateMachine.h"

template <class ENTITY_TYPE>
StateMachine<ENTITY_TYPE>::StateMachine(ENTITY_TYPE* owner)
	: m_pOwner(owner)
	, m_pCurrentState(nullptr)
	, m_pPreviousState(nullptr)
	, m_pGlobalState(nullptr)
{

}

template <class ENTITY_TYPE>
StateMachine<ENTITY_TYPE>::~StateMachine(void)
{

}

