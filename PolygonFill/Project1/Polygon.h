#pragma once
#include "BaseUI.h"
#include "Edge.h"
#include <vector>
#include <list>
#include "MyGeometry.h"
#include "DEF_Color.h"

class MyPolygon :	public BaseUI
{

	struct EdgeData 
	{
		//from Xl Yl to Xh Yh
		int x,Xl,Yl,Xh,Yh, dX, dY, d;
		float m;
		EdgeData(MyEdge& e) 
		{
			const MyVertex* vl = (e.v1->y < e.v2->y )? e.v1 : e.v2;
			const MyVertex* vh = (e.v1->y < e.v2->y) ? e.v2 : e.v1;
			Xl = x = vl->x;
			Yl = vl->y;
			Xh = vh->x;
			Yh = vh->y;
			dX = Xh-Xl;
			dY = Yh-Yl;
			m = ((float)dY) / dX;
			d = 0;
		}				  

		void Print() 
		{					 
			printf("(%d, %d) to (%d, %d) slope %f \n",Xl,Yh-dY,Xl+dX,Yh,m);
		}
	};
	std::vector<MyVertex*> m_VertexVec;	 //vertices must be in clockwise order
	std::list<EdgeData> m_EdgeVec;
	void parseData();
	void FindIntersections(std::list<MyPolygon::EdgeData>& active, int scanY, int* intersections);
protected:
	int lowX, highX, lowY, highY;
public:
	MyPolygon(std::list<MyVertex*>& l);
	virtual ~MyPolygon();

	void Render() { Fill(red); }
	void Fill(const glm::vec3& color);
	bool IsInside(int x, int y) override;
	
};

