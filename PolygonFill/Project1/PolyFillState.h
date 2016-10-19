#pragma once
#include "BaseState.h"
#include "InputHandler.h"

#include "GL\glut.h"

class PolyFillState :
	public BaseState
{
	//class InputHandler;
	friend class PolyFillSM;

private:
	static std::string name;
protected:
	//PolyFillSM* owner;
	//std::function<void(int x, int y)> MouseDrag;  //only left mouse can drag
	//std::function<void(int x, int y)> MouseMove;
	//std::function<void(int x, int y)> LeftClick;
	//std::function<void(int x, int y)> RightClick;
	//std::function<void(int x, int y)> LeftRelease;
	//std::function<void(int x, int y)> RightRelease;
	//std::function<void(int x, int y, int startX, int startY)>DragLeftRelease;
	//std::function<void(int x, int y, int startX, int startY)> DragRightRelease;
	InputHandler* m_Input;
	PolyFillSM* machine;
	virtual void MouseMove(int x, int y);
	virtual void MouseDrag(int x, int y) {  }
	virtual void LeftClick(int x, int y) {  }
	virtual void RightClick(int x, int y) {  }
	virtual void LeftRelease(int x, int y) {  }
	virtual void RightRelease(int x, int y) {  }
	virtual void DragLeftRelease(int x, int y, int startX, int startY) {  };
	//virtual void DragRightRelease(int x, int y, int startX, int startY) {};
public:
	PolyFillState();
	virtual ~PolyFillState();
	void SetOwner(StateMachine* sm) override;
	std::string GetName() const override { return name; }
	void Enter() override;
	void Exit() override;
	virtual void Render();

	//void SetOwner(PolyFillSM* sm) { owner = sm; }
};

