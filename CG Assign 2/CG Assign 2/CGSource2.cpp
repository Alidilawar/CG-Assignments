#include <string.h>
#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
const GLint WIDTH = 600, HEIGHT = 600;
using namespace std;
GLuint VAO, VBO, shader, uniformXMove;
bool direction = true;
float triOffSet = 0.0f, triMaxOffSet = 2.0f, triIncrement = 0.05f;
//VERTEX SHADER
static const char* vShader = " \n\
#version 330 \n\
\n\
layout(location=0) in vec3 pos; \n\
uniform float xMove; \n\
void main() \n\
{ \n\
gl_Position = vec4(0.4 * pos.x*xMove, 0.4 * pos.y, pos.z, 1.0); \n\
}";
//FRAGMENT SHADER
static const char* fShader = " \n\
#version 330 \n\
\n\
out vec4 colour; \n\
\n\
void main() \n\
{ \n\
colour = vec4(0.0, 0.120, 0.240, 0.255); \n\
}";
//CREATE TRIANGLE FUNCTION 1ST METHOD COMPLETE
void CreateTrianlge() {
	GLfloat vertices[] = {
		-0.5f,-0.5f,0.0f,
		0.5,-0.5,1.0f,
		0.0f,0.5f,-0.0f,
	};
	glGenVertexArrays(1, &VAO); glBindVertexArray(VAO); glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
void AddShader(GLuint theProgram, const char* shadercode, GLenum shadertype) {
	GLuint theshader = glCreateShader(shadertype);
	const char* theCode[1];
	theCode[0] = shadercode;
	GLint CodeLength[1];
	CodeLength[0] = strlen(shadercode); glShaderSource(theshader, 1, theCode, CodeLength);
	glCompileShader(theshader);
	GLint result = 0;
	GLchar eLog[1024] = { 0 };
	glGetShaderiv(theshader, GL_COMPILE_STATUS, &result); if (!result)
	{
		glGetShaderInfoLog(theshader, sizeof(eLog), NULL, eLog);
		printf("Error compiling the %d Shader:'%s'\n", shadertype, eLog); return;
	}
	glAttachShader(theProgram, theshader);
}
void CompileShader() {
	shader = glCreateProgram();
	if (!shader)
	{
		printf("Error creating Shader Program");
		return;
	}
	glBindAttribLocation(shader, 0, "Position");
	AddShader(shader, vShader, GL_VERTEX_SHADER);
	AddShader(shader, fShader, GL_FRAGMENT_SHADER);
	GLint result = 0;
	GLchar eLog[1024] = { 0 };
	glLinkProgram(shader);
	glGetProgramiv(shader, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("Error Linking Program : %s \n", eLog);
		return;
	}
	glValidateProgram(shader);
	glGetProgramiv(shader, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("Error Validating Program : %s \n", eLog);
		return;
	}
	uniformXMove = glGetUniformLocation(shader, "xMove");
	glUseProgram(shader);
}
int main()
{
	if (!glfwInit())
	{
		printf("GLFW initialization failed!");
		glfwTerminate();
		return 1;
	}
	//SETTING GLFW WINDOW PROPERTIES
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	GLFWwindow* mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "S M ALI DILAWAR", NULL, NULL);
	if (!mainWindow)
	{
		printf("GLFW window creation failed!");
		glfwTerminate();
		return 1;
	}
	//PROVIDING BUFFER SIZE INFORMATION
	int bufferWidth, bufferHeight;
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);
	glfwMakeContextCurrent(mainWindow);
	glewExperimental = GL_TRUE;
	if (glewInit())
	{
		printf("GLEW initialization failed!");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}
	//VIEWPORT SIZE
	glViewport(0, 0, bufferWidth, bufferHeight);
	CreateTrianlge();
	CompileShader();
	while (!glfwWindowShouldClose(mainWindow))
	{
		glfwPollEvents();
		if (direction)
		{
			triOffSet += triIncrement;
		}
		else
		{
			triOffSet -= triIncrement;
		}
		if (abs(triOffSet) >= triMaxOffSet)
		{
			direction = !direction;
		}
		glClearColor(1.0f, 1.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shader);
		glUniform1f(uniformXMove, triOffSet);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
		glUseProgram(0);
		glfwSwapBuffers(mainWindow);
	}
	return 0;
}
