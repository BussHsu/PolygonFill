#pragma once
#include "MyGeometry.h"
#include <list>
class ConnectedGraph		//TODO abstract base class graph
{
	std::list<MyVertex*> m_vList;
	std::list<MyEdge*> m_eList;
	std::list<std::list<MyVertex*>> m_cycles;

	void CheckCycles();
	void Connect(MyVertex* v1, MyVertex* v2);
	void CleanPathData();
public:
	ConnectedGraph(int x, int y);
	~ConnectedGraph();

	//bool HasVertex(MyVertex& v);
	//bool HasVertex(int x, int y);
	//bool HasEdge(MyEdge& e);
	std::list<MyVertex*>& GetVList() { return m_vList; }
	std::list<MyEdge*>& GetEList () { return m_eList; }
	std::list<std::list<MyVertex*>>& GetCycleList() { return m_cycles; }
	
	MyVertex* GetVertex(int x, int y);
	MyVertex* GetVertex(MyVertex& v);
	MyVertex* GetVertex(MyVertex* v);
	MyEdge* GetEdge(MyVertex* v1, MyVertex* v2);
	MyEdge* GetEdge(MyEdge& e);
	
	MyEdge* AddEdge(MyEdge& edge);
	MyEdge* AddEdge(MyVertex* a, MyVertex* b);
	MyEdge* AddEdge(MyVertex* a, int x, int y);

	MyEdge* MergeGraph(ConnectedGraph& g, MyVertex* v1, MyVertex* v2);
};

