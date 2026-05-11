#define GLFW_DLL
#define GLEW_DLL

#include <iostream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"

float vertex[] = {0.0, 0.5, 0.0,
				0.0, -0.5, 0.0,
				-0.5, -0.5, 0.0};
int main()
{
	if (!glfwInit())
	{
		fprintf(stderr, "Error");
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* MyWindow = glfwCreateWindow(512, 512, "Ignatkov", NULL, NULL);

	if (!MyWindow)
	{
		glfwTerminate();
		return -2;
	}
	glfwMakeContextCurrent(MyWindow);
	glewExperimental = GL_TRUE;

	GLenum ret = glewInit();
	if (GLEW_OK != ret)
	{
		fprintf(stderr, "error: glew");
		return -3;
	}

	GLuint VBO, VAO, EBO;
	
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex),vertex, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), vertex);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	
	const char* vert_shader =
		"#version 410 core\n"
		"layout (location=0) in vec3 vp;"
		"void main() {"
		" gl_Position = vec4(vp, 1.0);"
		"}";

	const char* frag_shader =
		"#version 410 core\n"
		"out vec4 frag_colour;"
		"void main() {"
		" frag_colour = vec4( 0.2, 0.7, 0.5, 1.0);"
		"}";

	GLuint vertS = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragS = glCreateShader(GL_FRAGMENT_SHADER);
	
	glShaderSource(vertS, 1, &vert_shader, NULL);
	glShaderSource(fragS, 1, &frag_shader, NULL);
	
	glCompileShader(vertS);
	glCompileShader(fragS);
	
	
	GLuint shader_program = glCreateProgram();
	glAttachShader(shader_program, fragS);
	glAttachShader(shader_program, vertS);
	glLinkProgram(shader_program);


	while (!glfwWindowShouldClose(MyWindow))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(1.0, 0.2, 0.3, 1);
		/*/glBegin(GL_TRIANGLES);

		glColor3f(0.4, 1.0, 1.0); glVertex3f(0.0, 0.5, 0.0);
		glColor3f(0.4, 1.0, 1.0); glVertex3f(0.0, -0.5, 0.0);
		glColor3f(0.4, 1.0, 1.0); glVertex3f(-0.5, -0.5, 0.0);
		glEnd();*/

		glUseProgram(shader_program);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(MyWindow);
		glfwPollEvents();


	}
	glfwTerminate();
}

