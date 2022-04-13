#include <stdio.h>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
using namespace std;
const GLint WIDTH = 800, HEIGHT = 600;
bool direction = true;
//creating indentifiers for VAO, VBO and shaders
GLuint shader, VAO, VBO, xMoveUniformRef;  // VAO holds VBOs
float xIncrement = 0.0f;
const float xMaxLimt = 0.7f;
const float incrementFactor = 0.0003f;

static const char* vShader = " \n\
#version 330				\n\
							\n\
layout (location = 0) in  vec3 pos;						\n\
														\n\
uniform float xMove;									\n\
														\n\
void main()	\n\
{									\n\
    gl_Position = vec4(0.4 * pos.x + xMove, 0.4 * pos.y, 0.4 * pos.z , 1.0);										\n\
}									\n\
";

static const char* fShader = "\n\
#version 330						\n\
										\n\
out vec4 colour;									\n\
										\n\
void main()										\n\
{											\n\
	colour = vec4(1.0, 0.0, 0.0, 1.0);		\n\
}"; 

void CreateTriangle()
{
	const GLfloat vertices[] = {
		-1.0f,-1.0f,0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),vertices, GL_STATIC_DRAW);
		
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


}

void AddShaders(GLint theProgram, const char* shaderCode, GLenum shaderType)
{
	GLuint theShader = glCreateShader(shaderType);

	const GLchar* theShaderCode[1];
	theShaderCode[0] = shaderCode;

	GLint theCodeSize[1];
	theCodeSize[0] = strlen(shaderCode);
	

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glShaderSource(theShader, 1, theShaderCode, theCodeSize);
	glCompileShader(theShader);


	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(shader, sizeof(eLog), NULL, eLog);
		fprintf(stderr, "Error compiling the %d shader: '%s'\n", shaderType, eLog);
		return;
	}
	glAttachShader(theProgram, theShader);
}

void CompileShaders()
{
	shader = glCreateProgram();
	
	if (!shader)
	{
		cout << "error creating shaders Program" << endl;
		return;
	}

	AddShaders(shader, vShader, GL_VERTEX_SHADER);
	AddShaders(shader, fShader, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };
	
	glLinkProgram(shader);
	glGetProgramiv(shader, GL_LINK_STATUS, &result);
	
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		cout << "error linking Program" << eLog;
		return;
	}

	glValidateProgram(shader);
	glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);

	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		cout << "error validating Program" << eLog;
		return;
	}
	xMoveUniformRef = glGetUniformLocation(shader, "xMove");
}

int main()
{
	if (!glfwInit())
	{
		std::cout << "glfw failed to initialize!";
		glfwTerminate();
		return 1;
	}

	//Set GLFW Windows Properties 
	//OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// No backward compatibility
	glfwWindowHint(GLFW_OPENGL_COMPAT_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Allowing foward compatibility
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* renderWindow = glfwCreateWindow(WIDTH, HEIGHT,"Sample Scene", nullptr, nullptr);
	if (!renderWindow)
	{
		std::cout << "glfw failed to create Window!";
		glfwTerminate();
		return 1;
	}

	// retrieving buffer size information
	int bufferHeight, bufferWidth;
	glfwGetFramebufferSize(renderWindow, &bufferWidth, &bufferHeight);
	
	//set context for GLEW to use
	glfwMakeContextCurrent(renderWindow);

	//Allow latest extensive OpenGL features
	glewExperimental = GL_TRUE;
	
	if (glewInit()!= GLEW_OK)
	{
		std::cout << "glew failed to intialize";
		glfwDestroyWindow(renderWindow);
		glfwTerminate();
		return 1;
	}

	// Set Viewport size
	glViewport(0, 0, bufferWidth, bufferHeight);
	
	CreateTriangle();
	CompileShaders();
	//game looping 
	while (!glfwWindowShouldClose(renderWindow))
	{
		// Get + Handle Window Input
		glfwPollEvents();
		if (direction) 
		{
			xIncrement += incrementFactor;
		}
		else 
		{
			xIncrement -= incrementFactor;
		}

		if (abs(xIncrement) >= xMaxLimt)
		{
			direction = !direction;
		}
		// Clear Window 
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shader);
		glUniform1f(xMoveUniformRef, xIncrement);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
		glUseProgram(0);
		glfwSwapBuffers(renderWindow);
	}
	return 0;
}

