#include <string.h>
#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <mat4x4.hpp>
#include <glm.hpp>
#include <cmath>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
const GLint WIDTH = 750, HEIGHT = 750;
const int steps = 50;
const float angle = 3.14159 * 2.0f / steps;
int main()
{
	GLFWwindow* window;
	if (!glfwInit())
	{
		printf("GLFW initialization failed!");
		glfwTerminate();
		return -1;
	}
	window = glfwCreateWindow(HEIGHT, WIDTH, "S M Ali Dilawar", 0, 0);
	if (!window)
	{
		printf("Window Creation Error");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	float xPos = 0; float yPos = 0; float radius = 0.40f;
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT);
		float prevX = xPos;
		float prevY = yPos - radius;
		for (int i = 0; i <= steps; i++)
		{
			float newX = radius * sin(angle * i);
			float newY = -radius * cos(angle * i);
			glBegin(GL_TRIANGLES);
			glColor3f(1.0, 1.75, 1.5);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(prevX, prevY, 0.0f);
			glVertex3f(newX, newY, 0.0f);
			glEnd();
			prevX = newX;
			prevY = newY;
		}
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
}