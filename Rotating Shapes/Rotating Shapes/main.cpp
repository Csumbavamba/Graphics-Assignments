#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "ShaderLoader.h"
#include "Dependencies\soil\SOIL.h"

GLuint program;
GLuint VBO; // Vertex buffer Object
GLuint VAO; // vertex array object
GLuint EBO; // Element Buffer Object


// Create 6 triangles to form a hexagon



void Render();
void Initialise();
void Update();


int main (int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Rotating Shapes");

	glClearColor(1.0, 0.0, 0.0, 1.0); // Clear Window

	glewInit();
	Initialise();

	// Register callbacks
	glutDisplayFunc(Render);
	//glutIdleFunc(/*Update*/);
	glutMainLoop();
	return 0;


}

void Render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0, 0.0, 0.0, 1.0); // clear red

	/*glUseProgram(program);

	glUseProgram(0);*/

	glutSwapBuffers();
}

void Initialise()
{
	ShaderLoader shaderLoader;
	//program = shaderLoader.CreateProgram((char*)"VertexShader.vs", (char*)"FragmentShader.fs");
}

//void Update()
//{
//	glutPostRedisplay();
//}

