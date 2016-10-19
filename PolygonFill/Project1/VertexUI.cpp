#include "VertexUI.h"

#include "GL\glut.h"
 
VertexUI::VertexUI(MyVertex* p, int r,int groupId)
	:BaseUI()
	
{ 
	m_pModel = p;
	p->SetGroupID(groupId);
	circle = new Circle(p->x, p->y, r);
}


VertexUI::~VertexUI()
{
	if (circle);
	//	delete circle;
}

void VertexUI::SetColors(const glm::vec3& originC,const glm::vec3& pressC,const glm::vec3& activeC) 
{
	m_OriginColor = originC;
	m_PressingColor = pressC;
	m_ClickedColor = activeC;
}

void VertexUI::RenderInitial() 
{
	glColor3f(m_OriginColor.x, m_OriginColor.y, m_OriginColor.z);
	circle->Draw();
}

void VertexUI::RenderHover()
{
	glColor3f(m_HoverColor.x, m_HoverColor.y, m_HoverColor.z);
	circle->Draw();
}

void VertexUI::RenderPressing()
{
	glColor3f(m_PressingColor.x, m_PressingColor.y, m_PressingColor.z);
	circle->Fill();
}

void VertexUI::RenderClicked()
{
	glColor3f(m_ClickedColor.x, m_ClickedColor.y, m_ClickedColor.z);
	circle->Fill();
}