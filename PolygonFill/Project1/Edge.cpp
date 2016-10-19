#include "Edge.h"
#include <GL/glut.h> 
#include "DEF_Color.h"


Edge::Edge(MyEdge* e)
	: BaseUI(),
	m_pModel(e)
{
	
}


Edge::~Edge()
{
}

void Edge::Render()
{
	RenderInitial();
}

void Edge::RenderInitial()
{
	glColor3f(m_OriginColor.x, m_OriginColor.y, m_OriginColor.z);
	glBegin(GL_LINES);
	glVertex2i(m_pModel->v1->x, m_pModel->v1->y);
	glVertex2i(m_pModel->v2->x, m_pModel->v2->y);
	glEnd(); 
}

void Edge::RenderHover()
{
	glColor3f(m_HoverColor.x, m_HoverColor.y, m_HoverColor.z);
}

void Edge::RenderPressing()
{
	glColor3f(m_PressingColor.x, m_PressingColor.y, m_PressingColor.z);
}

void Edge::RenderClicked()
{
	glColor3f(m_ClickedColor.x, m_ClickedColor.y, m_ClickedColor.z);
}
