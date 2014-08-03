// OPENGL-a_simple_cube.cpp : 定義主控台應用程式的進入點。
//

//Include library
#include "stdafx.h"
#include "GL\freeglut.h"

//function protype
void Initial_Scene(void);
void Render_Scene(void);
void reshape(int width, int high);

//main function
int main(int argc, char* argv[])
{
	//glut initial
	glutInit(&argc, argv);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,450);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("A simple cube");

	//initialize scene
	Initial_Scene();

	//register glut callback function
	glutDisplayFunc(Render_Scene);
	glutReshapeFunc(reshape);

	//glut mainloop
	glutMainLoop();

	return 0;
}

void Initial_Scene(void){
	// 1.backgroung color
	glClearColor(0.75f, 0.75f, 0.75f, 0.0f);
}

void Render_Scene(void){
	// 1.initial gl
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// 2.camera from(150,150,150) lookat (0,0,0)
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(150.0f, 150.0f, 150.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	// 3.initial cube

	//    v4----- v5
	//   /|      /|
	//  v6------v7|
	//  | |     | |
	//  | |v0---|-|v1
	//  |/      |/
	//  v2------v3
	GLfloat vertex_list[][3] = {
		-50.0, -50.0, -50.0,	//v0
		50.0, -50.0, -50.0,	//v1
		-50.0, 50.0, -50.0,	//v2
		50.0, 50.0, -50.0,	//v3
		-50.0, -50.0, 50.0,	//v4
		50.0, -50.0, 50.0,	//v5
		-50.0, 50.0, 50.0,	//v6
		50.0, 50.0, 50.0,	//v7
	};
	GLfloat color_list[][3] = {
		0.0, 0.0, 0.0,	//v0
		1.0, 0.0, 0.0,	//v1
		0.0, 1.0, 0.0,	//v2
		1.0, 1.0, 0.0,	//v3
		0.0, 0.0, 1.0,	//v4
		1.0, 0.0, 1.0,	//v5
		0.0, 1.0, 1.0,	//v6
		1.0, 1.0, 1.0,	//v7
	};
	GLint index_list[][4] = {
		0, 1, 3, 2,	//down
		1, 5, 7, 3,	//right
		2, 3, 7, 6,	//front
		0, 2, 6, 4,	//left
		5, 1, 0, 4,	//back
		4, 6, 7, 5,	//top
	};

	// 4.draw cube
	glBegin(GL_QUADS);
	for (int i = 0; i < 6; i++){	//6 face
		for (int j = 0; j < 4; j++){	// 4 vertex each face
			glVertex3fv(vertex_list[index_list[i][j]]);
			glColor3fv(color_list[index_list[i][j]]);
		}
	}
	glEnd();

	// 5.swap buffers
	glutSwapBuffers();
}

void reshape(int width, int high){
	glViewport(0, 0, width, high);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75, float(width) / high, 0.1f, 1000);
}