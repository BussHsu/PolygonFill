#pragma once
#include "Mouse.h"
#include <functional>
//get input from the mouse to create the full logic
class InputHandler
{
	friend class PolyFillState;
	Mouse  m_Mouse;
public:
	InputHandler();
	~InputHandler();
	
	const Mouse& GetMouse() const { return m_Mouse;}
	//handlers
	void OnMouseMove(int x, int y);
	void OnMouseClick(MouseButton button, int x, int y);
	void OnMouseRelease(MouseButton button , int x, int y);
	//function hooks
	std::function<void(int, int)> MouseDrag;  //only left mouse can drag
	std::function<void(int, int)> MouseMove;
	std::function<void(int, int)> LeftClick;
	std::function<void(int, int)> RightClick;
	std::function<void(int, int)> LeftRelease;
	std::function<void(int, int)> RightRelease;
	std::function<void(int, int, int, int)>DragLeftRelease;
	//std::function<void(int x, int y, int startX, int startY)> DragRightRelease;

	
};

