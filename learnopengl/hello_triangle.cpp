
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

const char*  fragmentShaderSource = "#version 330 core\n"
  "out vec4 FragColor;\n"
  "void main()\n"
  "{\n"
  "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
  "}\0";

int main() {
  glfwInit();
  // 我们需要告诉GLFW我们要使用的版本, 这样GLFW会在创建OPENGL上下文时做出适当的调整
  // 这样也确保用户在没有适当的OpenGL版本支持的情况下无法运行
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  // 我们明确告诉GLFW我们使用的是核心模式(Core-Profile),意味着我们使用OpenGL功能的一个子集
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  // 创建窗口对象
  GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  // 告诉GLFW我们希望每当窗口跳这个调整大小的时候调用这个函数
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // GLAD是用来管理OpenGL的函数指针的，所以调用任何OpenGL的函数之前我们需要初始化GLAD
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);
  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
  }
  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
  }

  unsigned int shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
  }
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  float vertices[] = {
    -0.75f, -0.75f, -1.0f, //left
    0.75f,  -0.75f, -1.0f, // right
    0.0f,  0.75f,  -1.0f  // top
  };
  unsigned int VBO, VAO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glBindVertexArray(VAO);

  // 把顶点数组复制到缓冲中供OpenGL使用
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // 设置顶点属性指针
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // 你可以unbind VAO，这样其他VAO就不会意外修改此VAO（其实基本不会发生）
  // 因为在使用其他VAO之前，都是需要调用glBindVertexArray进行绑定的
  glBindVertexArray(0);

  while (!glfwWindowShouldClose(window)) { 
    // Render Loop渲染循环
    processInput(window);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // 使用着色器程序
    glUseProgram(shaderProgram);

    // 其实这里只有一个VAO，不需要每次都去绑定它，只是这样做更像正常的开发流程
    glBindVertexArray(VAO);

    // 绘制物体
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // 交换颜色缓冲(它是一个存储着GLFW窗口每一个像素颜色值的大缓冲)
    glfwSwapBuffers(window);
    // 检查有没有触发什么事件，更新窗口状态，并调用对应的回调函数
    glfwPollEvents();
  }

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteProgram(shaderProgram);

  glfwTerminate();
  return 0;
}

void processInput(GLFWwindow* window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  // 告诉OpenGL渲染窗口的尺寸大小
  // 在这里我们将大小设置为窗口大小一样大，当然也可以设置小点，这样空余出来的地方可以绘制其他数据
  // glViewport(0, 0, width, height);
  // glViewport(0, 0, 800, 600);
  glViewport((width-SCR_WIDTH)/2, (height-SCR_HEIGHT)/2, SCR_WIDTH, SCR_HEIGHT);
}