#pragma once
#include<glm\glm.hpp>
//Utilize mid point algorithm to draw and fill circles
class Circle
{
	int x;
	int y;
	int r;

public:
	Circle(int x, int y, int r);
	~Circle();

	void GetCenter(glm::vec2* center) const { center->x = x; center->y = y; }
	int GetRadius() const { return r; }
	void SetCenter(int x, int y) { this->x = x; this->y = y; }
	void SetRadius(int rad) { r = rad; }

	bool IsInside(const int posX, const int posY)const;

	static void DrawCircle(int x, int y, int r);
	static void FillCircle(int x, int y, int r);
	void Draw();
	void Fill();
};

