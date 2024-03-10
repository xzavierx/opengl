## glfwWindowHint - 设置选项
```cpp
  // 我们需要告诉GLFW我们要使用的版本, 这样GLFW会在创建OPENGL上下文时做出适当的调整
  // 这样也确保用户在没有适当的OpenGL版本支持的情况下无法运行
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  // 我们明确告诉GLFW我们使用的是核心模式(Core-Profile),意味着我们使用OpenGL功能的一个子集
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
```

## glfwCreateWindow - 创建窗口对象
```cpp
  GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
```

## glfwSetFramebufferSizeCallback
// 设置GLFW我们希望每当窗口调整大小的回调函数
```cpp
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // 告诉OpenGL渲染窗口的尺寸大小
    // 在这里我们将大小设置为窗口大小一样大，当然也可以设置小点，这样空余出来的地方可以绘制其他数据
    // glViewport(0, 0, width, height);
    // glViewport(0, 0, 800, 600);
    glViewport((width-SCR_WIDTH)/2, (height-SCR_HEIGHT)/2, SCR_WIDTH, SCR_HEIGHT);
  }
```

## gladLoadGLLoader
// 初始化GLAD
// GLAD是用来管理OpenGL的函数指针的，所以调用任何OpenGL的函数之前我们需要初始化GLAD
```cpp
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }
```

## glfwWindowShouldClose
// 在我们每次进行渲染循环的开始前检查一次GLFW是否被要求退出，如果是的话，该函数返回为true
```cpp
  while(!glfwWindowShouldClose(window)) {
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
```

## glfwSwapBuffers
// 交换颜色缓冲（它是一个存储着GLFW窗口每一个像素颜色值的大缓冲）
```cpp
  glfwSwapBuffers(window);
```

## glfwPollEvents
// 检查有没有触发什么事件，更新窗口状态，并调用对应的回调函数
```cpp
  glfwPollEvents();
```


## glfwGetKey
// 接受按键输入
```cpp
  while (!glfwWindowShouldClose(window)) {
    processInput(window);
  }
  void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      glfwSetWindowShouldClose(window, true);
    }
  }
```

## glClearColor, glClear
glClearColor - 设置清空屏幕的颜色
glClear - 清除颜色缓冲，整个颜色会被填充为glClearColor里设置的颜色。
glClearColor函数是一个状态设置函数，而glClear则是要一个状态使用的函数，它使用了当前的状态来获取应该清除为的颜色
```cpp
while(Render Loop) {
  // 每次渲染时都清除屏幕，否则我们仍能看到上一次迭代的渲染结果
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}
```

## glGenBuffers, glBindBuffer
glGenBuffers - 生成一个VBO对象
  * 第一个参数为缓冲ID 

glBindBuffer - 将新创建缓冲绑定到指定目标上，如GL_ARRAY_BUFFER。
```cpp
unsigned int VBO;
glGenBuffers(1, &VBO);

glBindBuffer(GL_ARRAY_BUFFER, VBO);
```

## glBufferData
将定义的顶点数据从CPU复制到GPU的内存中
```cpp
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
```
特殊参数说明：  
第一个参数是目标缓冲的类型：GL_ARRAY_BUFFER(已绑定过顶点缓冲对象)   
第四个参数指定了我们希望显卡如何管理给定的数据。
  * GL_STATIC_DRAW:数据不会或几乎不会改变
  * GL_DYNAMIC_DRAW:数据会改变很多, 确保显卡把数据放在能够高速写入的内存部分
  * GL_STREAM_DRAW:数据绘制时都会改变，同上

## glCreateShader, glShaderSource, glCompileShader
glCreateShader - 创建一个着色器对象
glShaderSource - 将着色器源码附加到着色器对象上
glCompileShader - 编译着色器
* 参数2 - 字符串数量
* 参数3 - 字符串地址
```cpp
const char* vertexShaderSource = "#version 330 core...";

unsigned int vetexShader;
vertexShader = glCreateShader(GL_VERTEX_SHADER);

glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);

glCompileShader(vertexShader);
```

## glGetShaderiv, glGetShaderInfoLog
在glCompileShader后面调用
glGetShaderiv - 获取编译结果
glGetShaderInfoLog - 获取错误信息
```cpp
int success;
char infoLog[512];
glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

if (!success) {
  glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
  cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
}
```

## glCreateProgram, glAttachShader, glLinkProgram
glCreateProgram - 创建一个程序
glAttachShader - 将之前编译的着色器附加到程序对象上
glLinkProgram - 链接程序
```cpp
unsigned int shaderProgram;
shaderProgram = glCreateProgram();

glAttachShader(shaderProgram, vertexShader);
glAttachShader(shaderProgram, fragmentShader);

glLinkProgram(shaderProgram);
```

## glGetProgram, glGetShaderInfoLog
glLinkProgram之后调用
glGetProgram
