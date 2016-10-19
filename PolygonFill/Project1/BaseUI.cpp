#include "BaseUI.h"
#include <stdio.h>
#include "DEF_Color.h"

BaseUI::BaseUI()
	:
	m_OriginColor(white),
	m_HoverColor(cyan),
	m_PressingColor(red),
	m_ClickedColor(yellow)
{
	m_State = UI_Initial;
}


BaseUI::~BaseUI()
{
}

void BaseUI::Reset()		   //initial state
{
	m_State = 0x00;			//reset
	m_State |= UI_Initial;			//is initial
}

void BaseUI::OnHover()		  //hover state
{
	m_State |= UI_Hover;			//is hovered
}	  

void BaseUI::OnClick() 			 //pressing state
{
	m_State |= UI_Pressing;			//is pressing
}

void BaseUI::Activate() 		   //clicked state
{
	m_State &= ~UI_Initial& ~UI_Pressing;		//is not initial
	m_State |= UI_Clicked;            //is clicked
}

void BaseUI::Render()
{
	if ((m_State & UI_Disable) == UI_Disable)
	{
		RenderDisable();
		return;
	}
	if ((m_State & UI_Pressing) ==UI_Pressing)
	{
		RenderPressing();
		return;
	}
	if ((m_State & UI_Hover) == UI_Hover)
	{
		RenderHover();
		return;
	}
	if ((m_State & UI_Clicked) == UI_Clicked)
		RenderClicked();
	else
		RenderInitial();
}