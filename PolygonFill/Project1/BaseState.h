#pragma once
#include <string>

class BaseState
{
	friend class StateMachine; 

protected:
	StateMachine* owner;
public:
	BaseState();
	~BaseState();

	static std::string basetype_name;
	virtual std::string GetName() const { return basetype_name; }

	virtual void Enter() {}
	virtual void Exit() {}

	virtual void SetOwner(StateMachine* sm) { owner = sm; }
	bool operator ==(const BaseState& left)
	{
		return left.GetName() == this->GetName();
	}
};

