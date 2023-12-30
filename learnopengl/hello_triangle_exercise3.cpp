#include <glad/glad.h>
#include "GLFW/glfw3.h"
#include <iostream>
#include <stddef.h>
#include <vcruntime.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char* vertexShaderSource = "#version 330 core\n"
  "layout (location = 0) in vec3 aPos;\n"
  "void main()\n"
  "{\n"
  "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
  "}\0";

const char*  fragmentShader1Source = "#version 330 core\n"
  "out vec4 FragColor;\n"
  "void main()\n"
  "{\n"
  "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
  "}\0";
const char *fragmentShader2Source = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
    "}\n\0";

int main() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  unsigned int fragmentShaderOrange = glCreateShader(GL_FRAGMENT_SHADER);
  unsigned int fragmentShaderYellow = glCreateShader(GL_FRAGMENT_SHADER);
  unsigned int shaderProgramOrange = glCreateProgram();
  unsigned int shaderProgramYellow = glCreateProgram();

  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);
  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
  }
  glShaderSource(fragmentShaderOrange, 1, &fragmentShader1Source, NULL);
  glCompileShader(fragmentShaderOrange);
  glGetShaderiv(fragmentShaderOrange, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShaderOrange, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::ORANGE::COMPILATION_FAILED\n" << infoLog << std::endl;
  }
  glShaderSource(fragmentShaderYellow, 1, &fragmentShader2Source, NULL);
  glCompileShader(fragmentShaderYellow);
  glGetShaderiv(fragmentShaderYellow, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShaderYellow, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::YELLLOW::COMPILATION_FAILED\n" << infoLog << std::endl;
  }

  glAttachShader(shaderProgramOrange, vertexShader);
  glAttachShader(shaderProgramOrange, fragmentShaderOrange);
  glLinkProgram(shaderProgramOrange);
  glGetProgramiv(shaderProgramOrange, GL_LINK_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shaderProgramOrange, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::ORANGE::LINKING_FAILED\n" << infoLog << std::endl;
  }

  glAttachShader(shaderProgramYellow, vertexShader);
  glAttachShader(shaderProgramYellow, fragmentShaderYellow);
  glLinkProgram(shaderProgramYellow);
  glGetProgramiv(shaderProgramYellow, GL_LINK_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shaderProgramYellow, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::YELLOW::LINKING_FAILED\n" << infoLog << std::endl;
  }
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShaderOrange);
  glDeleteShader(fragmentShaderYellow);

  float firstTriangle[] = {
      -0.9f, -0.5f, 0.0f,  // left 
      -0.0f, -0.5f, 0.0f,  // right
      -0.45f, 0.5f, 0.0f,  // top 
  };
  float secondTriangle[] = {
      0.0f, -0.5f, 0.0f,  // left
      0.9f, -0.5f, 0.0f,  // right
      0.45f, 0.5f, 0.0f   // top 
  };
  unsigned int VBOs[2], VAOs[2];
  glGenVertexArrays(2, VAOs);
  glGenBuffers(2, VBOs);

  // 把顶点数组复制到缓冲中供OpenGL使用
  glBindVertexArray(VAOs[0]);
  glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
  // 设置顶点属性指针
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  // 把顶点数组复制到缓冲中供OpenGL使用
  glBindVertexArray(VAOs[1]);
  glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
  // 设置顶点属性指针
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  while (!glfwWindowShouldClose(window)) {
    processInput(window);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // 使用着色器程序
    glUseProgram(shaderProgramOrange);
    glBindVertexArray(VAOs[0]);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glUseProgram(shaderProgramYellow);
    glBindVertexArray(VAOs[1]);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glDeleteVertexArrays(2, VAOs);
  glDeleteBuffers(2, VBOs);
  glDeleteProgram(shaderProgramOrange);
  glDeleteProgram(shaderProgramYellow);

  glfwTerminate();
  return 0;
}

void processInput(GLFWwindow* window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}