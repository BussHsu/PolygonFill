#include "Circle.h"
#include "GL\glut.h"
#include <math.h>

#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

Circle::Circle(int x, int y, int r)
	:x(x),
	y(y),
	r(r)
{
}


Circle::~Circle()
{
}
		   
bool Circle::IsInside(const int posX, const int posY) const
{
	int dx = posX - x;
	int dy = posY - y;
	return pow(r, 2) > pow(dx, 2) + pow(dy, 2) ? true : false;
}

void Circle::Draw()
{
	DrawCircle(x, y, r);
}

void Circle::Fill()
{
	FillCircle(x, y, r);
}

void Circle::DrawCircle(int x, int y, int r)
{
	int dY = r;
	float F = 1 + pow(((float)r) - 0.5f, 2);			//F is the mid point factor
	int rSquare = pow(r, 2);

	glBegin(GL_POINTS);
	for (int i = 0; i <= r/1.41423; i++)
	{

		glVertex2i((GLint)x + i, (GLint)y+dY);
		glVertex2i((GLint)x - i, (GLint)y+dY);
		glVertex2i((GLint)x + i, (GLint)y-dY);
		glVertex2i((GLint)x - i, (GLint)y - dY);
		glVertex2i((GLint)x + dY, (GLint)y + i);
		glVertex2i((GLint)x - dY, (GLint)y + i);
		glVertex2i((GLint)x + dY, (GLint)y - i);
		glVertex2i((GLint)x - dY, (GLint)y - i);
		
		if (F > rSquare)
		{
			F += 2 * i - 2 * dY + 5;
			dY--;			
		}
		else
		{
			F += 2 *i + 3;
		}
	}
	glEnd();
}

void Circle::FillCircle(int x, int y, int r)
{
	int dY = r;
	float F = 1 + pow(((float)r) - 0.5f, 2);			//F is the mid point factor
	int rSquare = pow(r, 2);

	glBegin(GL_LINES);
	for (int i = 0; i <= r / 1.41423; i++)
	{

		glVertex2i((GLint)x + i, (GLint)y + dY);
		glVertex2i((GLint)x - i, (GLint)y + dY);
		glVertex2i((GLint)x + i, (GLint)y - dY);
		glVertex2i((GLint)x - i, (GLint)y - dY);
		glVertex2i((GLint)x + dY, (GLint)y + i);
		glVertex2i((GLint)x - dY, (GLint)y + i);
		glVertex2i((GLint)x + dY, (GLint)y - i);
		glVertex2i((GLint)x - dY, (GLint)y - i);

		if (F > rSquare)
		{
			F += 2 * i - 2 * dY + 5;
			dY--;
		}
		else
		{
			F += 2 * i + 3;
		}
	}
	glEnd();
}
