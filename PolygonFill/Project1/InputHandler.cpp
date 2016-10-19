#include "InputHandler.h"


InputHandler::InputHandler():
MouseMove(nullptr),
MouseDrag(nullptr),
LeftClick(nullptr),
LeftRelease(nullptr),
RightClick(nullptr),
RightRelease(nullptr),
DragLeftRelease(nullptr)
{
	printf("InputHandler Ctor \n");
}


InputHandler::~InputHandler()
{
}

void InputHandler::OnMouseMove(int x, int y) 
{
	//update x y position;
	m_Mouse.x = x;
	m_Mouse.y = y;
	if (m_Mouse.CurrBtnState[0] == true)
	{
		if (MouseDrag)
			MouseDrag(x, y);
	}
	else
	{
		if (MouseMove)
			MouseMove(x, y);
	}
}

void InputHandler::OnMouseClick(MouseButton button, int x, int y) 
{
	//if already clicked ==> don't do anything
	if (m_Mouse.CurrBtnState[button])	
		return;

	m_Mouse.CurrBtnState[button] = true;
	m_Mouse.SetStartPoint(x, y);
	switch (button) 
	{
	case LEFT:
		if (LeftClick)
			LeftClick(x, y);
		break;
	case RIGHT:
		if (RightClick)
			RightClick(x, y);
		break;
	case MIDDLE:
		//do nothing
		break;
	default:
		break;
	}


}

void InputHandler::OnMouseRelease(MouseButton button, int x, int y) 
{
	bool i = m_Mouse.IsDragging();
	if (!m_Mouse.IsDragging())
	{
		switch (button)
		{
		case LEFT:
		{
			if (LeftRelease)
				LeftRelease(x, y);
		}
			break;
		case RIGHT:
		{
			if (RightRelease)
				RightRelease(x, y);
		}
			break;
		case MIDDLE:
			//do nothing
			break;
		default:
			break;
		}
	}
	else			//dragging
		switch (button)
		{
		case LEFT:
		{
			if (LeftRelease)
				DragLeftRelease(x, y, m_Mouse.startX, m_Mouse.startY);
		}
			break;
		case RIGHT:
		{
			if (RightRelease)
				;
				//DragRightRelease(x, y, m_Mouse.startX, m_Mouse.startY);
		}
			break;
		case MIDDLE:
			//do nothing
			break;
		default:
			break;
		}
	m_Mouse.CurrBtnState[button] = false;
	m_Mouse.ResetStartPoint();
}

