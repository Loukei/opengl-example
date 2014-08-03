// OPENGL_vertex_array.cpp : �w�q�D���x���ε{�����i�J�I�C
// �m��/�ܽd opengl �U��ø�Ϥ覡
//Draw_glvertex(); �ǲΪ�glbegin/end �Ҧ�
//Draw_glvertex_with_array(); �ϥΨƥ��w�q�narray���覡�A��֤@�ӭӤH�u��J�Ѽ�
//Draw_VA(); �ϥ�vertex array�A�|�e�o���(��֪�function call)
//Draw_VA_with_Vector(); �Q��C++���зǼ˪Ovector�O�s�A��{�ʺA���O�s�ƾ�

////////////////////////////////////////
// Include librarys
////////////////////////////////////////
#include "stdafx.h"
#include < vector >
#include "GL/freeglut.h"
//#include "glm/glm.hpp"

////////////////////////////////////////
// Name space
////////////////////////////////////////

////////////////////////////////////////
// Function 
////////////////////////////////////////
void Initial_Scene(void);
void Render_Scene(void);
void Reshape(int width, int high);

void Draw_glvertex();
void Draw_glvertex_with_array();
void Draw_VA();
void Draw_VA_with_Vector();
//void Draw_VA_with_glm();

void Draw_axes();

////////////////////////////////////////
// Main function
////////////////////////////////////////
int main(int argc, char* argv[])
{
	//Initial GLUT window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 450);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Vertex Array DEMO");

	//Initial Scenes 
	Initial_Scene();

	//Register function call
	glutDisplayFunc(Render_Scene);
	glutReshapeFunc(Reshape);

	//Send to GLUT main loops
	glutMainLoop();

	return 0;
}

void Initial_Scene(void){
	// 1.background color
	glClearColor(0.75f, 0.75f, 0.75f, 0.75f);

	// 2.camera
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(150.0f, 150.0f, 150.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
}

void Render_Scene(void){
	// 1.Open depth_test,then clear color buffer and depth buffer
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// 2.Draw cube in scene
	// there is 4 way to draw a cube, uncomment any subfunction you want 
	//    v4----- v5
	//   /|      /|
	//  v6------v7|
	//  | |     | |
	//  | |v0---|-|v1
	//  |/      |/
	//  v2------v3
	
	Draw_axes();
	//Draw_glvertex();
	//Draw_glvertex_with_array();
	//Draw_VA();
	Draw_VA_with_Vector();


	// 3.Swap buffers
	glutSwapBuffers();
}

void Reshape(int width, int high){
	// 1.force canvas minimal size
	if (width < 160 | high < 90){
		width = 160;
		high = 90;
	}

	// 2.resize canvas size
	glViewport(0, 0, width, high);

	// 3.setup camera
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75, float(width) / high, 0.1f, 1000);
}

// �ϥγ̶ǲΪ�glBegin()/glEnd() �e���, 24��function call
// ���I�O�C�����n��ʥh��J��ơA�ӥBfunction call�Ӧh�|��C�t��
void Draw_glvertex(){

	glFrontFace(GL_CCW);
	glEnable(GL_BACK);

	glBegin(GL_QUADS);
	//down
	glVertex3f(-50.0, -50.0, -50.0); glColor3f(0.0, 0.0, 0.0); //v0
	glVertex3f( 50.0, -50.0, -50.0); glColor3f(1.0, 0.0, 0.0); //v1
	glVertex3f( 50.0,  50.0, -50.0); glColor3f(1.0, 1.0, 0.0); //v3
	glVertex3f(-50.0,  50.0, -50.0); glColor3f(0.0, 1.0, 0.0); //v2
	//right
	glVertex3f( 50.0, -50.0, -50.0); glColor3f(1.0, 0.0, 0.0); //v1
	glVertex3f( 50.0, -50.0,  50.0); glColor3f(1.0, 0.0, 1.0); //v5
	glVertex3f( 50.0,  50.0,  50.0); glColor3f(1.0, 1.0, 1.0); //v7
	glVertex3f( 50.0,  50.0, -50.0); glColor3f(1.0, 1.0, 0.0); //v3
	//front
	glVertex3f(-50.0,  50.0, -50.0); glColor3f(0.0, 1.0, 0.0); //v2
	glVertex3f( 50.0,  50.0, -50.0); glColor3f(1.0, 1.0, 0.0); //v3
	glVertex3f( 50.0,  50.0,  50.0); glColor3f(1.0, 1.0, 1.0); //v7
	glVertex3f(-50.0,  50.0,  50.0); glColor3f(0.0, 1.0, 1.0); //v6
	//left
	glVertex3f(-50.0, -50.0, -50.0); glColor3f(0.0, 0.0, 0.0); //v0
	glVertex3f(-50.0,  50.0, -50.0); glColor3f(0.0, 1.0, 0.0); //v2
	glVertex3f(-50.0,  50.0,  50.0); glColor3f(0.0, 1.0, 1.0); //v6
	glVertex3f(-50.0, -50.0,  50.0); glColor3f(0.0, 0.0, 1.0); //v4
	//back
	glVertex3f( 50.0, -50.0,  50.0); glColor3f(1.0, 0.0, 1.0); //v5
	glVertex3f( 50.0, -50.0, -50.0); glColor3f(1.0, 0.0, 0.0); //v1
	glVertex3f(-50.0, -50.0, -50.0); glColor3f(0.0, 0.0, 0.0); //v0
	glVertex3f(-50.0, -50.0,  50.0); glColor3f(0.0, 0.0, 1.0); //v4
	//top
	glVertex3f(-50.0, -50.0,  50.0); glColor3f(0.0, 0.0, 1.0); //v4
	glVertex3f(-50.0,  50.0,  50.0); glColor3f(0.0, 1.0, 1.0); //v6
	glVertex3f( 50.0,  50.0,  50.0); glColor3f(1.0, 1.0, 1.0); //v7
	glVertex3f( 50.0, -50.0,  50.0); glColor3f(1.0, 0.0, 1.0); //v5
	glEnd();

	glDisable(GL_BACK);
}

// �Q�Υ��w�q�n���I�P�C�⪺�覡�ӵe�|�󦳮Ĳv,�u�ݭn�w�q8�ӳ��I�P�C��
// �A�H�s�������C�ӭ������I���ǧY�i
// �٬O�ϥ�24�� function call,�Ӧh�I���ɭ�ø�s�t�׷|�ܺC
void Draw_glvertex_with_array(){
	//8 vertex
	GLfloat vertex_list[][3] = {
		-50.0, -50.0, -50.0,	//v0
		 50.0, -50.0, -50.0,	//v1
		-50.0,  50.0, -50.0,	//v2
		 50.0,  50.0, -50.0,	//v3
		-50.0, -50.0,  50.0,	//v4
		 50.0, -50.0,  50.0,	//v5
		-50.0,  50.0,  50.0,	//v6
		 50.0,  50.0,  50.0,	//v7
	};
	// 8 color to 8 vertex
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
	// 6 face for cube
	GLint index_list[][4] = {
		0, 1, 3, 2,	//down
		1, 5, 7, 3,	//right
		2, 3, 7, 6,	//front
		0, 2, 6, 4,	//left
		5, 1, 0, 4,	//back
		4, 6, 7, 5,	//top
	};

	glFrontFace(GL_CCW);
	glEnable(GL_BACK);

	glBegin(GL_QUADS);
	for (int i = 0; i < 6; i++){	//6 face
		for (int j = 0; j < 4; j++){	// 4 vertex each face
			glVertex3fv( vertex_list[ index_list[i][j] ] );
			glColor3fv(color_list[ index_list[i][j] ]);
		}
	}
	glEnd();

	glDisable(GL_BACK);
}

// �{�b�����ϥ�vertex array �ӵe���,�ϥΪ���Ƥj�P�W�@��(�R�A�}�C)
// ���O�@���e�i�h�|�֫ܦh
void Draw_VA(){
	// 8 vertex for 1 voxel
	GLfloat vertex_list[][3] = {
		-50.0f, -50.0f, -50.0f,	//v0
		50.0f, -50.0f, -50.0f,	//v1
		-50.0f, 50.0f, -50.0f,	//v2
		50.0f, 50.0f, -50.0f,	//v3
		-50.0f, -50.0f, 50.0f,	//v4
		50.0f, -50.0f, 50.0f,	//v5
		-50.0f, 50.0f, 50.0f,	//v6
		50.0f, 50.0f, 50.0f,	//v7
	};

	// 8 colors for each vertex
	GLubyte color_list[][4] = {
		0, 0, 0, 255,
		255, 0, 0, 255,
		0, 255, 0, 255,
		255, 255, 0, 255,
		0, 0, 255, 255,
		255, 0, 255, 255,
		0, 255, 255, 255,
		255, 255, 255, 255,
	};

	// 6 face for voxel
	GLuint index_list[][4] = {
		6, 2, 3, 7,	//front
		4, 5, 1, 0, //end
		4, 0, 2, 6, //left
		7, 3, 1, 5, //right
		4, 6, 7, 5, //top
		0, 1, 3, 2, //down
	};

	glFrontFace(GL_CCW);

	glEnable(GL_BACK);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, vertex_list);
	glColorPointer(4, GL_UNSIGNED_BYTE, 0, color_list);
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_INT, index_list); // 6*4 calls for glvertex

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisable(GL_BACK);
}

// �P�ˬO�ϥ�vertex array �A���O�ޤJ���覡�ϥ�C++�˪O��vector
// �i�H��n���F���ҫ��ޤJ���@�k(�ʺA�W�[�j�p)
// �C����J�Ȫ��ɭԨϥ�vertex_list.push_back() �� vertex_list.insert()�Y�i
// ���I�O�e���O�ϥ�GLfloat,�N��vertex_list.size()�s���O (8�ӳ��I * 3�Ӷb) = 24
// �ӫD���[���N���I�ƥ� => index_list �����ޭȤ��n��
void Draw_VA_with_Vector(){
	std::vector<GLfloat> vertex_list;
	std::vector<GLubyte> color_list;
	std::vector<GLuint> index_list;

	//load data
	vertex_list = {
		-50.0f, -50.0f, -50.0f,	//v0
		50.0f, -50.0f, -50.0f,	//v1
		-50.0f, 50.0f, -50.0f,	//v2
		50.0f, 50.0f, -50.0f,	//v3
		-50.0f, -50.0f, 50.0f,	//v4
		50.0f, -50.0f, 50.0f,	//v5
		-50.0f, 50.0f, 50.0f,	//v6
		50.0f, 50.0f, 50.0f,	//v7
	};

	color_list = {
		0, 0, 0, 255,
		255, 0, 0, 255,
		0, 255, 0, 255,
		255, 255, 0, 255,
		0, 0, 255, 255,
		255, 0, 255, 255,
		0, 255, 255, 255,
		255, 255, 255, 255,
	};

	index_list = {
		6, 2, 3, 7,	//front
		4, 5, 1, 0, //end
		4, 0, 2, 6, //left
		7, 3, 1, 5, //right
		4, 6, 7, 5, //top
		0, 1, 3, 2, //down
	};

	glFrontFace(GL_CCW);

	glEnable(GL_BACK);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, &vertex_list[0]);
	glColorPointer(4, GL_UNSIGNED_BYTE, 0, &color_list[0]);
	glDrawElements(GL_QUADS, index_list.size(), GL_UNSIGNED_INT, &index_list[0]); // 6*4 calls for glvertex

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisable(GL_BACK);
}

// �ϥ�vertex array + vector���覡�A�P��vector���s���O�ϥ�glm::
//void Draw_VA_with_glm(){
//	std::vector<glm::vec3> vertex_list;
//	std::vector<glm::vec4> color_list;
//	std::vector<GLuint> index_list;
//
//}

//�eXYZ�b
void Draw_axes(){
	glLineWidth(2.0f);
	glBegin(GL_LINES);
	// x-axis :red
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(150.0f, 0.0f, 0.0f);
	// y-axis :green
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 150.0f, 0.0f);
	// z-axis :blue
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 150.0f);
	glEnd();
}