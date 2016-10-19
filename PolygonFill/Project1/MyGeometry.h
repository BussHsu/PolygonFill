#pragma once
#include <glm\glm.hpp>
#include <math.h>
#include <list>
#include <set>

struct MyPath;
typedef struct s_Vertex 
{
	int gid;
	int x;
	int y;
	int edge;
	std::list<s_Vertex*> neighbors;	  //for	path search
	std::list<s_Vertex*> path;		  //for path search
	bool operator == (s_Vertex& right) { return (x == right.x && y == right.y); }
	void SetGroupID(int id) { gid = id; }

	//TODO move to private
	s_Vertex(int x, int y) :x(x), y(y), edge(0) {}
friend class ConnectedGraph;
private:
	
	s_Vertex(glm::vec2& v) :x(v.x), y(v.y),edge(0) {}

	void SetNeighbor(s_Vertex* n) { neighbors.push_back(n); }
	void RemoveNeghbor(s_Vertex* n) 
	{
		std::list<s_Vertex*>::iterator it; 
		for (it = neighbors.begin(); it != neighbors.end(); ++it)
		{
			if ((*it) == n || (*(*it)) == *n)
			{
				break;
			}
		}

		neighbors.erase(it);
	}	 	
} MyVertex;

typedef struct s_Edge
{
	MyVertex* v1;
	MyVertex* v2;
  
	bool operator == (s_Edge& right) { return (v1 == right.v1&&v2 == right.v2) || (v1==right.v2&& v2==right.v1); }
	s_Edge(MyVertex* v1, MyVertex* v2) :v1(v1), v2(v2) { assert(v1 != v2); }
friend class ConnectedGraph;
private:
	

	int Direction(MyVertex& p0, MyVertex& p1, MyVertex&p2)
	{
		return (p2.x - p0.x)*(p1.y - p0.y) - (p2.y - p0.y)*(p1.x - p0.x);
	}
	bool OnSegment(MyVertex& p0, MyVertex& p1, MyVertex& p2)
	{
		if (p2.x<fmax(p0.x, p1.x) && p2.x>fmin(p0.x, p1.x) && p2.y<fmax(p0.y, p1.y) && p2.y>fmin(p0.y, p1.y))
			return true;
		return false;
	}
public:
	glm::vec2 GetVector() { return glm::vec2((v2->x) - (v1->x),(v2->y)-(v1->y)); }
	bool IntersectWith(s_Edge& e)
	{
		MyVertex* v3 = e.v1;
		MyVertex* v4 = e.v2;
		int d1 = Direction(*v3, *v4, *v1);
		int d2 = Direction(*v3, *v4, *v2);
		int d3 = Direction(*v1, *v2, *v3);
		int d4 = Direction(*v1, *v2, *v4);
		if (((d1 > 0 && d2 < 0) || (d2 > 0 && d1 < 0)) && ((d3 > 0 && d4 < 0) || (d3 < 0 && d4>0)))
			return true;
		if (d1 == 0)
			return OnSegment(*v3, *v4, *v1);
		else if (d2 == 0)
			return OnSegment(*v3, *v4, *v2);
		else if (d3 == 0)
			return OnSegment(*v1, *v2, *v3);
		else if (d4 == 0)
			return OnSegment(*v1, *v2, *v4);
		else
			return false;
	}
	MyVertex* Contains(int x, int y) 
	{
		if (v1->x == x&& v1->y == y)
			return v1;
		else if (v2->x == x&& v2->y == y)
			return v2;
		else
			return nullptr;
	}
	MyVertex* Contains(MyVertex* v)
	{
		if (v1==v)
			return v1;
		else if (v2==v)
			return v2;
		else
			return nullptr;
	}
	void SwapP() { MyVertex* temp = v1; v1 = v2; v2 = temp; }

} MyEdge;

////TODO need to redesign
//typedef struct s_Path 
//{
//	bool cycle = false;
//	MyVertex* p1, *p2;	//endpoints of the path
//	
//	std::list<MyEdge*> path;
//	s_Path(MyEdge* e) { AddToPath(e); }
//	s_Path(std::list <MyEdge*> elist) 
//	{ 
//		std::list <MyEdge*>::iterator it;
//		std::list <MyEdge*>::iterator end = elist.end();
//		for (it = elist.begin(); it != end; ++it)
//			AddToPath((*it));
//	}
//
//	void AddToPath(MyEdge* e) 
//	{
//		if (std::find(path.begin(), path.end(), e) != path.end())	//edge is already in the path
//			return;
//		if (path.size() == 0)	//if path is empty
//		{
//			path.push_back(e); p1 = e->v1; p2 = e->v2; 
//		}
//		MyVertex* v1 = e->v1;
//		MyVertex* v2 = e->v2;
//		if (p1 != v1 && p1 != v2 &&  p2 != v1 && p2 != v2)	  //not conncected
//			return;
//		
//		if ((p1 == v1 && p2 == v2) || (p2 == v1&&p1 == v2) && p1->edge < 2 && p2->edge < 2)
//		{
//			//cycle
//			if (p1 == v1 && p2 == v2)
//				e->SwapP();
//			cycle = true;
//			path.push_back(e);
//		}
//		else if (p1 == v1)
//		{
//			e->SwapP();
//			p1 = e->v1;
//			path.push_front(e);
//		}
//		else if (p1 == v2) 
//		{
//			p1 = e->v1;
//			path.push_front(e);
//		}
//		else if (p2 == v1)
//		{
//			p2 = e->v2;
//			path.push_back(e);
//		}
//		else if (p2 == v2)
//		{
//			e->SwapP();
//			p2 = e->v2;
//			path.push_back(e);
//		}
//
//			return;
//	}
//
//	std::list<MyVertex*>& Traverse() 
//	{
//		std::list<MyVertex*> out;
//		std::list<MyEdge*>::iterator it;
//		std::list<MyEdge*>::iterator end = path.end();
//
//		for (it = path.begin(); it != end; it++)
//		{
//			out.push_back((*it)->v1);
//		}
//		it--;
//		out.push_back((*it)->v2);
//		return out;
//	}
//}
//MyPath;