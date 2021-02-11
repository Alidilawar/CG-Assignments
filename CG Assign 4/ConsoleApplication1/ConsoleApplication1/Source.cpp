#include <stdio.h>
#include <GL/glew.h>
#include <GLFW\glfw3.h>
  
// window dimensions
const GLint WIDTH = 500, HEIGHT = 350;


int main()
{
	//Initialise GLFW
	if (!glfwInit())
	{
		printf("GLEW initialisation failed!");
		glfwTerminate();
		return 1;
	}

	//Setup GLFW window properties
	//Open GL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Core profile = No Backwords compatibility
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//Allow forword compatibility
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow *mainwindow = glfwCreateWindow(WIDTH, HEIGHT, "ALI DILAWAR", NULL, NULL);
	if (!mainwindow)
	{
		printf("GLFW sindow creation failed");
		glfwTerminate();
		return 1;
	}

	// Get buffer size information
	int bufferWidth, bufferHeight;
	glfwGetFramebufferSize(mainwindow, &bufferWidth, &bufferHeight);

	// Set context for GLEW to use
	glfwMakeContextCurrent(mainwindow);

	//Allow modern extension features
	glewExperimental = GL_TRUE;

	if (!glewInit())
	{
		printf("GLEW initialisation failed!");
		glfwDestroyWindow(mainwindow);
		glfwTerminate();
		return 1;
	}

	// Setuo viewport size
	glViewport(0, 0, bufferWidth, bufferHeight);

	//Loop untill window closed
	while (!glfwWindowShouldClose(mainwindow))
	{
		//Get + Handle user input events
		glfwPollEvents();

		//Clear window
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(mainwindow);
	}

	return 0;
}