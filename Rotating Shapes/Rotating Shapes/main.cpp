#include "Dependencies\soil\SOIL.h"
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "ShaderLoader.h"
#include <math.h>

GLuint program;
GLuint hexagonVBO, quadVBO; // Vertex buffer Object
GLuint hexagonVAO, quadVAO; // vertex array object
GLuint hexagonEBO, quadEBO; // Element Buffer Object
GLfloat currentTime;

GLuint texture, texture2;
std::string raymanFilePath = "Sprites/Rayman.jpg";
std::string smileyFilePath = "Sprites/AwesomeFace.png";


// Create 6 triangles to form a hexagon
GLfloat hexagon[] =
{
	// position				// color
	0.0f, 0.0f, 0.0f,		1.0f, 1.0f, 1.0f,	// Middle
	-0.5f, 1.0f, 0.0f,		0.0f, 1.0f, 0.0f,	// Top Left
	+0.5f, 1.0f, 0.0f,		0.0f, 0.0f, 1.0f,	// Top Right
	1.0f, 0.0f, 0.0f,		1.0f, 1.0f, 0.0f,	// Mid Right
	-1.0f, 0.0f, 0.0f,		1.0f, 0.0f, 1.0f,	// Mid Left
	0.5f, -1.0f, 0.0f,		0.5f, 0.5f, 0.2f,	// Bottom Right
	-0.5f, -1.0f, 0.0f,		0.1f, 0.9f, 0.6f	// Bottom Left

};

GLfloat quad[] =
{
	// position				// color			// Tex Coords
	-0.5f,  0.5f, 0.0f,		0.0f, 1.0f, 1.0f,	0.0f, 0.0f,		// Top Left
	+0.5f,  0.5f, 0.0f,		0.0f, 1.0f, 1.0f,	1.0f, 0.0f,		// Top Right
	-0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 1.0f,	0.0f, 1.0f,		// Bottom Left
	+0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 1.0f,	1.0f, 1.0f		// Bottom Right
};

GLuint hexagonIndices[] =
{

	0, 1, 4,	// Top Left
	0, 3, 2,	// Top Right
	0, 2, 1,	// Top
	0, 6, 5,	// Bottom
	0, 4, 6,	// Bottom Left
	0, 5, 3		// Bottom Right
};

GLuint quadIndices[] =
{
	0, 2, 1,	// Top Left
	2, 3, 1		// Bottom Right
};

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
	glutIdleFunc(Update);
	glutMainLoop();
	return 0;


}

void Render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0, 0.0, 0.0, 1.0); // clear red

	glUseProgram(program);

	// Draw hexagon
	glBindVertexArray(hexagonVAO);
	glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);

	// Add texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(program, "tex"), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glUniform1i(glGetUniformLocation(program, "tex2"), 1);

	// Draw quad with texture
	glBindVertexArray(quadVAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	GLint currentTimeLocation = glGetUniformLocation(program, "currentTime");
	glUniform1f(currentTimeLocation, currentTime);

	glBindVertexArray(0); // Unbind VAO
	glUseProgram(0);


	glutSwapBuffers();
}

void Initialise()
{
	ShaderLoader shaderLoader;
	program = shaderLoader.CreateProgram("VertexShader.vs", "FragmentShader.fs");

	//@@@ HEXAGON

	// Create hexagon VBO - VAO
	glGenVertexArrays(1, &hexagonVAO);
	glBindVertexArray(hexagonVAO);	

	glGenBuffers(1, &hexagonVBO);
	glBindBuffer(GL_ARRAY_BUFFER, hexagonVBO);
	glBufferData(
		GL_ARRAY_BUFFER,
		sizeof(hexagon),
		hexagon,
		GL_STATIC_DRAW
		);

	// Position
	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,				// not normalized
		6 * sizeof(GLfloat),	// Stride
		(GLvoid*)0				// Offset
	);

	// Color
	glVertexAttribPointer(
		1,
		3,
		GL_FLOAT,
		GL_FALSE,
		6 * sizeof(GLfloat),
		(GLvoid*)(3 * sizeof(GLfloat))
	);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	// Add EBO after enabling
	glGenBuffers(1, &hexagonEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, hexagonEBO);
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,
		sizeof(hexagonIndices),
		hexagonIndices,
		GL_STATIC_DRAW
		);




	// @@@@ QUAD
	// Create quad VBO - VAO
	glGenVertexArrays(1, &quadVAO);
	glBindVertexArray(quadVAO);

	glGenBuffers(1, &quadVBO);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(
		GL_ARRAY_BUFFER,
		sizeof(quad),
		quad,
		GL_STATIC_DRAW
	);

	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,				// not normalized
		8 * sizeof(GLfloat),	// Stride
		(GLvoid*)0				// Offset
	);

	glVertexAttribPointer(
		1,
		3,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(GLfloat),
		(GLvoid*)(3 * sizeof(GLfloat))
	);

	glVertexAttribPointer(
		2,
		2,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(GLfloat),
		(GLvoid*)(6 * sizeof(GLfloat))
	);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	// ADD EBO for quad
	glGenBuffers(1, &quadEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadEBO);
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,
		sizeof(quadIndices),
		quadIndices,
		GL_STATIC_DRAW
	);

	// Add textures
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	int width, height, channels;
	unsigned char* raymanImage = SOIL_load_image(raymanFilePath.c_str(), &width, &height, &channels, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, raymanImage);

	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(raymanImage);
	glBindTexture(GL_TEXTURE_2D, 0);

	// Generate 2nd texture
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);

	unsigned char* smileyImage = SOIL_load_image(smileyFilePath.c_str(), &width, &height, &channels, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, smileyImage);

	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(smileyImage);
	glBindTexture(GL_TEXTURE_2D, 0);

}


void Update()
{
	// Update game information
	currentTime = glutGet(GLUT_ELAPSED_TIME);
	currentTime = currentTime / 1000.0f; // Now it's seconds instead of miliseconds

	glutPostRedisplay();
}

