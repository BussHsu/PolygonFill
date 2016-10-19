#pragma once
#include <glm/glm.hpp>
#include "MyGeometry.h"
class BaseUI
{
	const unsigned char UI_Initial = 0x01; // hex for 0000 0001
	const unsigned char UI_Hover = 0x02; // hex for 0000 0010
	const unsigned char UI_Pressing = 0x04; // hex for 0000 0100
	const unsigned char UI_Clicked = 0x08; // hex for 0000 1000
	const unsigned char UI_Disable = 0x10; 

	unsigned char m_State;

	
protected:
	glm::vec3 m_OriginColor;
	glm::vec3 m_HoverColor;
	glm::vec3 m_PressingColor;
	glm::vec3 m_ClickedColor;
public:
	BaseUI();
	~BaseUI();
	//response - conditioning
	virtual bool IsInside(int x, int y) {return false;}
	//response - ui display
	virtual void Reset();
	virtual void OnHover();
	virtual void OnClick();
	virtual void Activate();
	//response - callback
	//TODO design callback function	

	//
	bool IsHover() { return m_State&UI_Hover >0; }
	bool IsPressing() { return m_State&UI_Pressing > 0; }
	//control
	virtual void Disable() { m_State |= UI_Disable; }
	virtual void Enable() { m_State &= ~UI_Disable; }

	//Rendering functions
	virtual void Render();				//logic template
	virtual void RenderInitial() {}		
	virtual void RenderHover() {}
	virtual void RenderPressing() {}
	virtual void RenderClicked() {}
	virtual void RenderDisable() {}


};

