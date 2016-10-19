#include "CreateLineState.h"
#include "PolyFillSM.h"
#include "VertexUI.h"

std::string CreateLineState::id = "CreateLine";


CreateLineState::CreateLineState()
{
}


CreateLineState::~CreateLineState()
{
}

void CreateLineState::CreateLine(int x, int y) 
{
	
}

void CreateLineState::LeftClick(int x, int y)
{
}

void CreateLineState::RightClick(int x, int y) {}
void CreateLineState::LeftRelease(int x, int y) 
{
	VertexUI* ui;
	if (machine->UIContains(x, y, &ui))
	{
		if (machine->GetCurrUI())
		{
			glm::vec2 v;
			ui->GetCenter(&v);
			machine->CreateEdge(v.x, v.y);
			machine->SetCurrUI(nullptr);
		}
		else
		{
			machine->SetCurrUI(ui);
			ui->Activate();
		}
	}
	else
	{
		machine->SetCurrUI(nullptr);
	}
	
}
void CreateLineState::RightRelease(int x, int y) 
{
	

}
								 