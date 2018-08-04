#pragma once

#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include <iostream>
#include <map>


class ShaderLoader
{
	// Functions
	private:

		std::string ReadShader(char *filename);
		GLuint CreateShader(GLenum shaderType,
							std::string source,
							char* shaderName);

	public:
		ShaderLoader(void);
		~ShaderLoader(void);
		GLuint CreateProgram(char* VertexShaderFilename,
							char* FragmentShaderFilename);

	// Variables
	private:
		std::map<std::string, GLuint> savedVertexShaders;
		std::map<std::string, GLuint> savedFragmentShaders;
		std::map<std::string, GLuint> savedPrograms;


};
