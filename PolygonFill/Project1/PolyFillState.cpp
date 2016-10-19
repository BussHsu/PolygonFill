#include "PolyFillState.h"
#include "PolyFillSM.h"



std::string PolyFillState::name = "PolyFillState";

PolyFillState::PolyFillState()
	:BaseState()
{
	printf("PolyFillState ctor \n");
}


PolyFillState::~PolyFillState()
{
}
void PolyFillState::SetOwner(StateMachine* sm)
{
	machine = static_cast<PolyFillSM*>(sm); 
}

void PolyFillState::Enter()
{
	m_Input= &((static_cast<PolyFillSM*>(machine))->m_InputHandler);
	if (m_Input)
	{
		m_Input->LeftClick = std::bind(&PolyFillState::LeftClick, this, std::placeholders::_1, std::placeholders::_2);
		m_Input->LeftRelease = std::bind(&PolyFillState::LeftRelease, this, std::placeholders::_1, std::placeholders::_2);
		m_Input->RightClick = std::bind(&PolyFillState::RightClick, this, std::placeholders::_1, std::placeholders::_2);
		m_Input->RightRelease = std::bind(&PolyFillState::RightRelease, this, std::placeholders::_1, std::placeholders::_2);

		m_Input->MouseDrag = std::bind(&PolyFillState::MouseDrag, this, std::placeholders::_1, std::placeholders::_2);
		m_Input->MouseMove = std::bind(&PolyFillState::MouseMove, this, std::placeholders::_1, std::placeholders::_2);
		m_Input->DragLeftRelease = std::bind(&PolyFillState::DragLeftRelease, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
	//m_Input->DragRightRelease = this->DragRightRelease;
	}
}

void PolyFillState::Exit()
{
}

void PolyFillState::MouseMove(int x, int y)
{
	VertexUI* ui;
	if (machine->UIContains(x, y, &ui))
	{
		ui->OnHover();
		machine->SetHoverUI(ui);
		glutPostRedisplay();
	}
	else if (ui = machine->GetHoverUI())
	{
		ui->Reset();
		machine->SetHoverUI(nullptr);
		glutPostRedisplay();
	}
 }

void PolyFillState::Render()
{
	for (auto& p : machine->m_PointList)
		p.Render();
	for (auto& e : machine->m_EdgeList)
		e.Render();

	for (auto& e : machine->m_Polygons)
		e.Render();
}