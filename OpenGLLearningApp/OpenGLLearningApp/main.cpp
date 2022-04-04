#include <stdio.h>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

const GLint WIDTH = 800, HEIGHT = 600;
using namespace std;
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
	
	//game looping 
	while (!glfwWindowShouldClose(renderWindow))
	{
		// Get + Handle Window Input
		glfwPollEvents();

		// Clear Window 
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(renderWindow);
	}
	return 0;
}