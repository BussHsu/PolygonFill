#include "Polygon.h"
#include <GL\glut.h>

MyPolygon::MyPolygon(std::list<MyVertex*>& l)
	:lowX(INT_MAX),
	lowY(INT_MAX),
	highX(0),
	highY(0),
	m_VertexVec({ std::begin(l), std::end(l) })
{
	////testData
	//m_VertexVec.push_back(&MyVertex(100,100));
	//m_VertexVec.push_back(&MyVertex(150, 150));
	//m_VertexVec.push_back(&MyVertex(130, 100));
	//m_VertexVec.push_back(&MyVertex(150, 50));
	//m_VertexVec.push_back(&MyVertex(120, 110));
	//m_VertexVec.push_back(&MyVertex(50, 30));
	//m_VertexVec.push_back(&MyVertex(20, 180));


	parseData();
}


MyPolygon::~MyPolygon()
{
}

//causion: can't handle flip
void MyPolygon::Fill(const glm::vec3& color)
{
	//setcolor
	glColor3f(color.x, color.y, color.z);

	//need the edge list and active list
	std::list<MyPolygon::EdgeData> active;


	std::list<MyPolygon::EdgeData>::iterator listItor = m_EdgeVec.begin();
	std::list<MyPolygon::EdgeData>::iterator it = listItor;


	for (int scanY = lowY; scanY <= highY; scanY++)
	{
	
		//if scanY reach the lowerY of an edgedata, push that into active list
		//each time a new element is added, sort by x coord and then slope(the order is opposite to make the wanted result)
		while (listItor != m_EdgeVec.end() && (*listItor).Yl == scanY)
		{			
			active.push_back(*listItor);
			active.sort([](EdgeData& d1, EdgeData& d2) {return d1.m > d2.m; });
			active.sort([](EdgeData& d1, EdgeData& d2) {return d1.x > d2.x; });
			++listItor;
		}

		//if active list is not empty
		if (active.size())
		{
			it = active.begin();
			
			while ( it != active.end())
			{
				//remove edgedata with Yh<scanY
				if ((*it).Yh <= scanY)
					active.erase(it++);		
				else // find x
				{
					int xdir = (*it).dX > 0 ? 1 : -1;	//if negative slope x should decrease
					(*it).d += xdir*(*it).dX * 2;
					while ((*it).d > (*it).dY)
					{
						(*it).x+=xdir;
						(*it).d -= (*it).dY * 2;
					}
					it++;
				}	 
			}

			//Draw
			glBegin(GL_LINES);
			for (it = active.begin(); it != active.end(); ++it)
			{
				int xbegin = (*it).x;
				++it;
				if (it == active.end())
				{
					printf("Bug? :active list is odd\n");
					break;
				}

				glVertex2i(xbegin,scanY);
				glVertex2i((*it).x,scanY);

				//printf("",xbegin,(*it).x);
			}
			glEnd();
		}


	}

}

//return the edgedata list(sorted by ascending y coord, if two y are the same, sort by ascending slope m)
void MyPolygon::parseData()
{
	for (int i =0 ; i<m_VertexVec.size();i++)
	{
		//find the boundary
		if (m_VertexVec[i]->x > highX)
			highX = m_VertexVec[i]->x;
		else if (m_VertexVec[i]->x < lowX)
			lowX = m_VertexVec[i]->x;

		if (m_VertexVec[i]->y > highY)
			highY = m_VertexVec[i]->y;
		else if (m_VertexVec[i]->y < lowY)
			lowY = m_VertexVec[i]->y;

		//create edgedata
		int j = i + 1;
		if (j == m_VertexVec.size())
			j = 0;
		m_EdgeVec.push_back(EdgeData(MyEdge(m_VertexVec[i], m_VertexVec[j])));
	}
	m_EdgeVec.sort([](EdgeData& d1, EdgeData& d2) {return (d1.Yl) < d2.Yl; });
}

void MyPolygon::FindIntersections(std::list<MyPolygon::EdgeData>& active, int scanY, int* output)
{
	  
}

bool MyPolygon::IsInside(int x, int y) 
{
	bool res = false;
	//glm::vec2 farPoint = glm::vec2(highX+1000,highY+1000);
	//Edge e = Edge(glm::vec2(x,y),farPoint);
	return res;
}
