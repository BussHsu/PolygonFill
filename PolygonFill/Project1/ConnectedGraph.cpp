#include "ConnectedGraph.h"



ConnectedGraph::ConnectedGraph(int x, int y)
{
	m_vList.push_back(new MyVertex(x,y));
	printf("vlist size = %d \n",m_vList.size());
}


ConnectedGraph::~ConnectedGraph()
{
}

//bool ConnectedGraph::HasEdge(MyEdge& e) 
//{
//	for (auto& x : m_eList)
//	{
//		if ((*x) == e)
//			return true;
//	}
//	return false;
//}

MyVertex* ConnectedGraph::GetVertex(int x, int y)
{
	for (auto v : m_vList)
	{
		if (v->x == x && v->y == y)
			return v;
	}
	return nullptr;
}
MyVertex* ConnectedGraph::GetVertex(MyVertex& v) 
{
	for (auto x : m_vList)
	{
		if (*x==v)
			return x;
	}
	return nullptr;
}

MyVertex* ConnectedGraph::GetVertex(MyVertex* v) 
{
	for (auto x : m_vList)
		if (x == v)
			return x;
	GetVertex(*v);
}

MyEdge* ConnectedGraph::GetEdge(MyVertex* v1, MyVertex* v2)
{
	MyEdge& temp = MyEdge(v1,v2);
	for (auto x : m_eList)
	{
		if (*x==temp)
			return x;
	}
	return nullptr;
}
MyEdge* ConnectedGraph::GetEdge(MyEdge& e)
{
	for (auto x : m_eList)
	{
		if (*x == e)
			return x;
	}
	return nullptr;
}

MyEdge* ConnectedGraph::AddEdge(MyVertex* a, MyVertex* b)
{
	MyEdge* ret = nullptr;
	bool hasA = false;
	bool hasB = false;
	for (auto x : m_vList)
	{
		if (x == a)
			hasA = true;
		else if (x == b)
			hasB = true;
	}
	if (hasA&&hasB)
	{
		ret = GetEdge(a, b);
		if (!ret)
		{
			Connect(a, b);
			m_eList.push_back(ret = new MyEdge(a, b));
			//TODO cycles
			CheckCycles();
			return ret;
		}
		else
			return ret;
	}
	else if (hasA)
	{
		m_vList.push_back(b);
		Connect(a, b);
		m_eList.push_back(ret=new MyEdge(a, b));
		return ret;
	}
	else if (hasB)
	{
		m_vList.push_back(a);
		Connect(a, b);
		m_eList.push_back(ret=new MyEdge(a, b));
		return ret;
	}
	else if (m_vList.empty() && m_eList.empty())
	{
		m_vList.push_back(a);
		m_vList.push_back(b);
		Connect(a, b);
		m_eList.push_back(ret =new MyEdge(a, b));
		return ret;
	}

	else
		return false;
	
}

MyEdge* ConnectedGraph::AddEdge(MyEdge& e)
{
	MyEdge* ret = nullptr;
	//0.edge is already in the graph
	if (ret = GetEdge(e))	
		return ret;
	
	//1.if graph has no vertex
	if (m_vList.empty())
	{
		m_vList.push_back(e.v1);
		m_vList.push_back(e.v2);
		Connect(e.v1, e.v2);
		m_eList.push_back(&e);
	}

	//2.if  graph has no edge	(should contain one vertex)
	if (m_eList.size() == 0)	
	{  	
		std::list<MyVertex*>::iterator it = m_vList.begin(); //first vertex (should be only one)
		if (!e.Contains(*it))		//if the edge doesn't contain this vertex 
			return ret;			//TODO on other part should create another connected graph instead

		//vertex in vlist
		if (e.v1 == *it)
			m_vList.push_back(e.v2);
		else
			m_vList.push_back(e.v1);

		Connect(e.v1, e.v2);

		//edge in elist
		m_eList.push_back(&e);
		return &e;
	}

	//if graph already has edges
	MyVertex* v1 = GetVertex(e.v1);
	MyVertex* v2 = GetVertex(e.v2); 
	if (v1 && v2)			//form a cycle!!
	{  		
		Connect(v1, v2);
		m_eList.push_back(ret = new MyEdge(v1, v2));
		//TODO detect cycle  and push into m_cycles
		CheckCycles();
	}
	else if (v1)
	{
		m_vList.push_back(e.v2);
		Connect(v1, e.v2);
		m_eList.push_back(ret = new MyEdge(v1, e.v2));
	}

	else if (v2)
	{
		m_vList.push_back(e.v1);
		Connect(e.v1, v2);
		m_eList.push_back(ret = new MyEdge(e.v1, v2));
	}

	return ret;
}

MyEdge*	ConnectedGraph::AddEdge(MyVertex* a, int x, int y)
{
	return AddEdge(a, new MyVertex(x, y));
}

MyEdge* ConnectedGraph::MergeGraph(ConnectedGraph& g, MyVertex* v1, MyVertex* v2)
{
	MyEdge* ret = nullptr;
	int id = m_vList.front()->gid;
	for (auto& x : g.GetVList())
	{
		x->gid = id;
		m_vList.push_back(x);
	}
	for (auto& x : g.GetEList())
	{
		m_eList.push_back(x);
	}
	for (auto& x : g.GetCycleList())
	{
		m_cycles.push_back(x);
	}


	Connect(v1, v2);
	m_eList.push_back(ret = new MyEdge(v1,v2));
	return ret;
}

//private
void ConnectedGraph::Connect(MyVertex* v1, MyVertex* v2)
{
	v1->SetNeighbor(v2);
	v2->SetNeighbor(v1);
	v1->edge++;
	v2->edge++;
}

void ConnectedGraph::CheckCycles()
{
	std::list<MyVertex*>::iterator it = m_vList.begin();
	MyVertex* currP = (*it);
	MyVertex* prevP = currP;
	currP->path.push_back(currP);
	std::list<MyVertex*> next;
	next.push_back(currP);
	while (!next.empty())
	{
		//go to next
		currP = next.front();

		for (auto x : currP->neighbors)
		{
			if (x == prevP)	  //no reverse travel
				continue;
			if (x->path.empty()) //untraveled
			{
				x->path = currP->path;
				x->path.push_back(x);
				next.push_back(x);
			}
			else 	   //traveled by another path: must have a cycle
			{
				//case 1: traveled by this path
				//case 2: traveled by anoth path
				std::list<MyVertex*>::reverse_iterator rIt=x->path.rbegin();
				for (; rIt != x->path.rend(); rIt++)
				{
					it = std::find(currP->path.begin(), currP->path.end(), *rIt);
					if (it != currP->path.end())		//a cycle from *it to currP,x to *rIt
					{
						std::list<MyVertex*> path;
						for (; it != currP->path.end(); ++it)
							path.push_back((*it));
						for (std::list<MyVertex*>::reverse_iterator rIt2 = x->path.rbegin(); rIt2 != rIt; ++rIt2)
						{
							path.push_back((*rIt2));  							
						}
						m_cycles.push_back(path);
						printf("cycle detected! \n");
					}
				}
			}

		}  		
		prevP = currP;
		next.pop_front();
	}
	CleanPathData();
}

void ConnectedGraph::CleanPathData()
{
	for (auto x : m_vList)
		x->path.clear();
}
//bool ConnectedGraph::HasVPointer(MyVertex* v)
//{
//	
//}