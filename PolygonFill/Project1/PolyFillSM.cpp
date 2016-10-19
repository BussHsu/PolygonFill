#include "PolyFillSM.h"
#include "PolyFillState.h"
#include "BaseState.h"
#include "Edge.h"
#include "Polygon.h"
#include "DEF_States.h"
#include "DEF_Size.h"


PolyFillSM::PolyFillSM()
	:m_pHoverPoint(nullptr),
	m_pCurrPoint(nullptr)
{
}	 

PolyFillSM::~PolyFillSM()
{
}

void PolyFillSM::Render() 
{	   
	(static_cast<PolyFillState*>(m_CurrState))->Render();
}

bool PolyFillSM::UIContains(int x, int y, VertexUI** out)
{
	*out = nullptr;
	bool result = false;
	std::list<VertexUI>::iterator it;
	std::list<VertexUI>::iterator end = m_PointList.end();

	for (it = m_PointList.begin(); it != end; ++it)
	{
		if ((*it).IsInside(x, y))
		{
			result = true;
			*out = &(*it);
			break;
		}
	}
	return result;
}

void PolyFillSM::CreatePoint(int x, int y) 
{
	printf("create pont @ (%d, %d)\n",x ,y);
	ConnectedGraph* g = new ConnectedGraph(x, y);
	int id = m_Graphs.size();
	m_Graphs.push_back(g);
	bool a = m_Graphs[0]==g;
	m_PointList.push_back(VertexUI(g->GetVertex(x, y), POINT_RAD, id));
}

void PolyFillSM::CreateEdge(int x0, int y0, int x1, int y1)
{
	printf("create pont from (%d, %d) to (%d, %d)\n", x0, y0 ,x1, y1);
}

void PolyFillSM::CreateEdge(int x1, int y1)
{
	if (m_pCurrPoint) 
	{
		int i = m_pCurrPoint->GetGroupID();
		VertexUI* v2;
		if (UIContains(x1, y1, &v2))
		{
			int i2 = v2->GetGroupID();
			if (i == i2) //connect the same graph(cycles can occur)
			{
				ConnectedGraph* g = m_Graphs[i];
				MyEdge* e = g->AddEdge(m_pCurrPoint->GetVertexData(), v2->GetVertexData());
				m_EdgeList.push_back(Edge(e));
				CreatePolygons();
			}
			else  //connect different points/subgraph  (no cycle)
			{
				MyEdge* e = m_Graphs[i]->MergeGraph(*m_Graphs[i2], m_pCurrPoint->GetVertexData(), v2->GetVertexData());
				m_EdgeList.push_back(Edge(e));
			}
		}
		
		else  //create& connect (no cycle)
		{
			ConnectedGraph* g = m_Graphs[i];
			m_EdgeList.push_back(Edge(g->AddEdge(m_pCurrPoint->GetVertexData(), x1, y1)));
			
		}
	}
		
	
}

void PolyFillSM::CreatePolygons()
{
	m_Polygons.clear();
	for (auto& g : m_Graphs)
	{
		std::list<std::list<MyVertex*>>& cycles = g->GetCycleList();
		if (cycles.size() > 0)
		{
			std::list<std::list<MyVertex*>>::iterator it = cycles.begin();
			for (; it != cycles.end(); ++it)
			{
				m_Polygons.push_back(MyPolygon(*it));
			}
		}
	}
}