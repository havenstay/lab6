#define GLFW_DLL
#define GLEW_DLL

#include "Shader.h"
#include <iostream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"

using namespace std;

float vertex[] = { 0.0f, 0.5f, 0.0f,
                   0.0f, -0.5f, 0.0f,
                  -0.5f, -0.5f, 0.0f };
GLuint indices[] = { 0, 1, 2
};
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
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);




    Shader ourShader("vertex.glsl", "frag.glsl");

    while (!glfwWindowShouldClose(MyWindow))
    {
        glClearColor(1.0f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ourShader.Use();

        float timeValue = glfwGetTime();
        float green = (sin(timeValue) / 2.0f) + 0.5f;

        ourShader.setVec4("ourColor", 0.0f, green, 0.0f, 1.0f);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(MyWindow);
        glfwPollEvents();
    }

    glfwTerminate();
}