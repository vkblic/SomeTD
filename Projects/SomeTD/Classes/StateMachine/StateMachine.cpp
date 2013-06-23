#include "StateMachine.h"

template <class entity_type>
StateMachine<entity_type>::StateMachine(entity_type* owner)
	: m_pOwner(owner)
	, m_pCurrentState(nullptr)
	, m_pPreviousState(nullptr)
	, m_pGlobalState(nullptr)
{

}

template <class entity_type>
StateMachine<entity_type>::~StateMachine(void)
{

}

