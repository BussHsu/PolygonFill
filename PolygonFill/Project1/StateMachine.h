#pragma once
#include<map>
#include<string>
#include"DEF_States.h"

class BaseState;

class StateMachine
{
protected:
	std::map<std::string, BaseState*> m_States;
	bool m_bInTransition;
	BaseState* m_CurrState;

	void TransitTo(BaseState* s);

	template <typename T>
	T* GetState();
public:
	StateMachine();
	~StateMachine();

	template<typename T>
	void ChangeState();

};

template<typename T>
void StateMachine::ChangeState()
{
	BaseState* s =(BaseState*) GetState<T>();
	TransitTo(s);
}

template<typename T>
T* StateMachine::GetState()
{
	
	//_ASSERT(std::is_base_of<BaseState, T>::value & "template type is not a state");
	//std::map<std::string, BaseState>::iterator it;
	T* s = new T();
	std::map<std::string, BaseState*>::iterator it;
	it = m_States.find(s->GetName());
	if (it == m_States.end())
	{
		m_States.insert(std::pair < std::string, BaseState*>(s->GetName(), s));
		it = m_States.find(s->GetName());
	}
	
	//s = reinterpret_cast<T>((*it).second);

	s->SetOwner(this);
	return s;
}