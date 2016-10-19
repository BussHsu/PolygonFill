#include "CreatePointState.h"
#include "PolyFillSM.h"

std::string CreatePointState::id = "CreatePointState";

CreatePointState::CreatePointState()
	:PolyFillState()
{
}


CreatePointState::~CreatePointState()
{
}

void CreatePointState::LeftClick(int x, int y)
{
	VertexUI* ui, *prevui = machine->GetCurrUI();
	if (machine->UIContains(x, y, &ui))
	{
		if(prevui==ui)
		return;

		machine->CreateEdge(x, y);
		
	}
	else if (prevui)
	{
		{
			CreatePoint(x, y);
			machine->CreateEdge(x, y);
		}
	}
	else
	{
		CreatePoint(x, y);
	}
	machine->UIContains(x, y, &ui);
	//click inside ui
	machine->SetCurrUI(ui);
	//ui->OnClick();
}

void CreatePointState::RightClick(int x, int y)
{
}

void CreatePointState::LeftRelease(int x, int y)
{
	//VertexUI* ui = nullptr, *currUI = nullptr;

	//if (currUI = machine->GetCurrUI())
	//{
	//	if (machine->UIContains(x, y, &ui))
	//	{
	//		if (ui == currUI)
	//			ui->Activate();
	//		else
	//			;
	//		//TODO: shift to drawline
	//	}
	//	else //release outside a ui
	//	{
	//		currUI->Reset();
	//		machine->SetCurrUI(nullptr);
	//	}
	//}
}

void CreatePointState::RightRelease(int x, int y)
{
}

void CreatePointState::CreatePoint(int x, int y)
{
	machine->CreatePoint(x, y);
}

//void CreatePointState::Render()
//{
//	for (auto& p : machine->GetPoints())
//		p.Render();
//}