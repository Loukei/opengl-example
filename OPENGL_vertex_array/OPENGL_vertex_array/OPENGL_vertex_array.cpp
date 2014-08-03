// OPENGL_vertex_array.cpp : 定義主控台應用程式的進入點。
// 練習/示範 opengl 各種繪圖方式
//Draw_glvertex(); 傳統的glbegin/end 模式
//Draw_glvertex_with_array(); 使用事先定義好array的方式，減少一個個人工填入參數
//Draw_VA(); 使用vertex array，會畫得更快(更少的function call)
//Draw_VA_with_Vector(); 利用C++的標準樣板vector保存，實現動態的保存數據

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

// 使用最傳統的glBegin()/glEnd() 畫方塊, 24次function call
// 缺點是每次都要手動去填入資料，而且function call太多會拖慢速度
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

// 利用先定義好頂點與顏色的方式來畫會更有效率,只需要定義8個頂點與顏色
// 再以編號紀錄每個面的頂點順序即可
// 還是使用24次 function call,太多點的時候繪製速度會變慢
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

// 現在換成使用vertex array 來畫方塊,使用的資料大致上一樣(靜態陣列)
// 但是一次送進去會快很多
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

// 同樣是使用vertex array ，但是引入的方式使用C++樣板的vector
// 可以更好的達成模型引入的作法(動態增加大小)
// 每次輸入值的時候使用vertex_list.push_back() 或 vertex_list.insert()即可
// 缺點是容器是使用GLfloat,代表vertex_list.size()存的是 (8個頂點 * 3個軸) = 24
// 而非直觀的代表頂點數目 => index_list 的索引值不好算
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

// 使用vertex array + vector的方式，同時vector內存的是使用glm::
//void Draw_VA_with_glm(){
//	std::vector<glm::vec3> vertex_list;
//	std::vector<glm::vec4> color_list;
//	std::vector<GLuint> index_list;
//
//}

//畫XYZ軸
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