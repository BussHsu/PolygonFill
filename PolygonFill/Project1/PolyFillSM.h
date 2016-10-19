#pragma once
#include "StateMachine.h"
#include "InputHandler.h"
#include <list>
#include <vector>
#include "VertexUI.h"
#include "ConnectedGraph.h"
#include "Edge.h"
#include "Polygon.h"

class PolyFillSM  :public StateMachine
{
	friend PolyFillState;
	InputHandler m_InputHandler;
	std::vector<ConnectedGraph*> m_Graphs;

	std::list<VertexUI> m_PointList;
	std::list<Edge> m_EdgeList;
	std::list<MyPolygon> m_Polygons;
	VertexUI* m_pCurrPoint;
	VertexUI* m_pHoverPoint;
public:
	PolyFillSM();
	virtual ~PolyFillSM();

	//Getter
	InputHandler* GetInputHandler() { return &m_InputHandler; }
	std::list<VertexUI>& GetPoints() { return m_PointList; }
	VertexUI* GetCurrUI() { return m_pCurrPoint ? m_pCurrPoint : nullptr; }
	void SetCurrUI(VertexUI* value) { m_pCurrPoint = value; }
	VertexUI* GetHoverUI() { return m_pHoverPoint ? m_pHoverPoint : nullptr; }
	void SetHoverUI(VertexUI* value) { m_pHoverPoint = value; }


	//UI manage
	void CreatePoint(int x, int y);
	void CreateEdge(int x0, int y0, int x1, int y1);
	void CreateEdge(int x1, int y1);
	void CreatePolygons();
	bool UIContains(int x, int y , VertexUI** out);
	
	virtual void Render();
};

