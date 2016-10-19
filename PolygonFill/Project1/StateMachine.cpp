#include "StateMachine.h"
#include "BaseState.h"


StateMachine::StateMachine()
	:m_bInTransition(false),
	m_CurrState(nullptr)
{
}


StateMachine::~StateMachine()
{
}

			  

void StateMachine::TransitTo(BaseState* s)
{
	if (m_CurrState && (m_bInTransition || m_CurrState == s))
		return;
	m_bInTransition = true;
	if (m_CurrState)
		m_CurrState->Exit();

	m_CurrState = s; 
	m_CurrState->Enter();

	m_bInTransition = false;
}




