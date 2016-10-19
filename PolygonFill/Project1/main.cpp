/*----------------------------------------------------------------------------------------
 *	
 *	project:	01_MouseBasics
 *	author:		Rob Bateman
 *	note:		This file is designed to show you the basics of how to set up your glut
 *				apps to recieve mouse input. 
 *
 *				The first stage of this is to provide a button callback function that 
 *				will be called whenever a mouse button is pressed or released. In this
 *				sourcefile It is the function "MouseButton" that is set as the glut
 *				callback for button events. 
 *
 *				The function prototype must always be (though the name can change!):
 *
 *				void MouseButton( int button, int state, int x, int y );
 *
 *				The parameters are :
 *
 *				button -	values can be GLUT_LEFT_BUTTON,GLUT_RIGHT_BUTTON,GLUT_MIDDLE_BUTTON
 *				state  -	was the button pressed or released, specified with GLUT_DOWN & GLUT_UP respectively.
 *				x      -	the x-position of the mouse click
 *				y      -	the y-position of the mouse click
 */
#include <list>


#ifdef WIN32
	#define WIN32_LEAN_AND_MEAN
	#include <Windows.h>
#endif

#include <GL/glut.h>
#include "PolyFillSM.h"
#include "DEF_States.h"
#include "DEF_Size.h"
#include "VertexUI.h"
#include "Polygon.h"
PolyFillSM* machine = nullptr;

//Test
MyPolygon* testPolygon = nullptr;

std::list<VertexUI>* g_pCircleUIs = new std::list<VertexUI>();
VertexUI* g_pPressingUI;

int winw, winh;
/*----------------------------------------------------------------------------------------
 *	This function will be used to draw the 3D scene
 */
void Draw3D()
{
}

/*----------------------------------------------------------------------------------------
 *	This function will be used to draw an overlay over the 3D scene.
 *	This will be used to draw our fonts, buttons etc......
 */
//void Draw2D()
//{
//	//glColor3f(1.0f, 1.0f, 1.0f);
//	//glBegin(GL_POINTS);
//	//for each (MyVertex v in *g_pVertices)
//	//{
//	//	glVertex2i((GLint)v.x, (GLint)v.y);
//	//}
//	//glEnd();
//	//for(VertexUI& c : *g_pCircleUIs)
//	//{
//	//		c.Render();
//	//}
//
//
//}

/*----------------------------------------------------------------------------------------
 *	This is the main display callback function. It sets up the drawing for 
 *	The 3D scene first then calls the Draw3D() function. After that it switches to 
 *	an orthographic projection and calls Draw2D().
 */
void Draw()
{
	/*
	 *	Clear the background
	 */
	glClear( GL_COLOR_BUFFER_BIT |
			 GL_DEPTH_BUFFER_BIT );

	/*
	 *	Set the orthographic viewing transformation
	 */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,winw,0,winh,-1,1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//test
	//if(testPolygon)
	//testPolygon->Fill(glm::vec3(1.0f, 1.0f, 1.0f));


	//tell machine to render
	if(machine)
		machine->Render();

	glutSwapBuffers();
}

/*----------------------------------------------------------------------------------------
 *	This function is called when the window is resized. All this does is simply 
 *	store the new width and height of the window which are then referenced by
 *	the draw function to set the correct viewing transforms 
 */
void Resize(int w, int h)
{
	winw = w;
	winh = h;

	/*
	 *	Allow drawing in full region of the screen
	 */
	glViewport(0,0,w,h);
}


/*----------------------------------------------------------------------------------------
 *
 */
void MouseButton(int button,int state,int x, int y)
{
	if (!machine)
		return;
	/*
	 *	has the button been pressed or released?
	 */
	if (state == GLUT_DOWN) 
	{
		/*
		 *	Which button was pressed?
		 */
		switch(button) 
		{
		case GLUT_LEFT_BUTTON:
		/*{
			bool pressing = false;
			for(VertexUI& c : *g_pCircleUIs)
			{
				if (c.IsInside(x, winh - y))
				{
					pressing = true;
					g_pPressingUI = &c;
					c.OnClick();
				}
			}
			if (!pressing)
			{
				g_pCircleUIs->push_back(VertexUI(x, winh - y, 5));
			}							   
		
		}*/
			machine->GetInputHandler()->OnMouseClick(LEFT, x, winh -y);
			break;
		case GLUT_MIDDLE_BUTTON:
			break;
		case GLUT_RIGHT_BUTTON:
			machine->GetInputHandler()->OnMouseClick(RIGHT, x,winh- y);
			break;
		}

	}
	else 
	{
		/*
		 *	Which button was released?
		 */
		switch(button) 
		{
		case GLUT_LEFT_BUTTON:
			//{
			//	if (g_pPressingUI&&g_pPressingUI->IsPressing())
			//	{
			//		if (g_pPressingUI->IsInside(x, y))
			//			g_pPressingUI->Activate();
			//		else
			//			g_pPressingUI->Reset();
			//	}
			//}
			machine->GetInputHandler()->OnMouseRelease(LEFT, x,winh- y);
			break;
		case GLUT_MIDDLE_BUTTON:
			break;
		case GLUT_RIGHT_BUTTON:
			machine->GetInputHandler()->OnMouseRelease(RIGHT, x,winh- y);
			break;
		}
	}

	/*
	 *	Force a redraw of the screen
	 */
	glutPostRedisplay();
}

void MousePassiveMotion(int x, int y)
{
	if(machine)
		machine->GetInputHandler()->OnMouseMove(x, winh - y);
}

/*----------------------------------------------------------------------------------------
 *
 */

int main(int argc,char **argv)
{
	//testPolygon = new MyPolygon();
	winh = WIN_HEIGHT;
	winw = WIN_WIDTH;
	machine = new PolyFillSM();
	if(machine)
		machine->ChangeState<CreatePointState>();

	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_DEPTH|GLUT_DOUBLE);
	glutInitWindowSize(winw,winh);
	glutInitWindowPosition(200,100);
	glutCreateWindow("Polygon Fill");

	glutDisplayFunc(Draw);
	glutReshapeFunc(Resize);
	glutMouseFunc(MouseButton);
	glutMotionFunc(MousePassiveMotion);
	glutPassiveMotionFunc(MousePassiveMotion);
	

	glutMainLoop();

	delete testPolygon;
}






