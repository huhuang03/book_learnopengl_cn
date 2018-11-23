// 创建相同的两个三角形，但对它们的数据使用不同的VAO和VBO
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <chrono>

const int W_WIDTH = 800;
const int W_HEIGHT = 600;

const int VERTEX_SIZE = 6;

void processInput(GLFWwindow *window);

void pritnTime();

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  std::cout << "change window size to " << width << "*" << height << std::endl;;
  glViewport(0, 0, width, height);
}

int createVertexShader() {
  unsigned int vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  
  const char* vertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;"
    "void main()"
    "{"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.y, 1.0);"
    "}";

  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);

  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader,GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "ERROR:SHADER::VERTEX::COMPLATIION_FAILED\n" << infoLog << std::endl;
  }
  return vertexShader;
}

int createFragmentShader1() {
  const char* fragmentShaderSource =
    "#version 330 core\n"
    "out vec4 FragColor;"
    "void main()"
    "{"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);"
    "}";

  unsigned int fragmentShader;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);
  return fragmentShader;
}

int createFragmentShader2() {
  const char* fragmentShaderSource =
    "#version 330 core\n"
    "out vec4 FragColor;"
    "void main()"
    "{"
    "   FragColor = vec4(0.5f, 1.0f, 0.2f, 1.0f);"
    "}";

  unsigned int fragmentShader;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);
  return fragmentShader;
}

int main() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  GLFWwindow *window = glfwCreateWindow(W_WIDTH, W_HEIGHT, "LearnOpenGL", NULL, NULL);
  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initial GLAD" << std::endl;
    return -1;
  }

  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  int vertexShader = createVertexShader();
  int fragmentShader1 = createFragmentShader1();
  int fragmentShader2 = createFragmentShader2();

  unsigned int shaderProgram1;
  shaderProgram1 = glCreateProgram();
  glAttachShader(shaderProgram1, vertexShader);
  glAttachShader(shaderProgram1, fragmentShader1);
  glLinkProgram(shaderProgram1);

  unsigned int shaderProgram2;
  shaderProgram2 = glCreateProgram();
  glAttachShader(shaderProgram2, vertexShader);
  glAttachShader(shaderProgram2, fragmentShader2);
  glLinkProgram(shaderProgram2);

  float verticles[][9] = {
                         {
                       -.5f,   0,  0,
                        .5f,   0,  0,
                          0,  .5f, 0,
                         },
                         {
                       -.5f,   0,  0,
                        .5f,   0,  0,
                          0, -.5f, 0
                          
                         }
                       
  };

  unsigned int VBO[2];
  glGenBuffers(2, VBO);

  unsigned int VAO[2];
  glGenVertexArrays(2, VAO);

  for (int i = 0; i < 2; i++) {
    glBindVertexArray(VAO[i]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[i]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticles[i]), verticles[i], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);

    glEnableVertexAttribArray(0);
  }

  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);
    processInput(window);
    glUseProgram(shaderProgram1);

    glBindVertexArray(VAO[0]);
    glDrawArrays(GL_TRIANGLES, 0, VERTEX_SIZE);

    glUseProgram(shaderProgram2);
    glBindVertexArray(VAO[1]);
    glDrawArrays(GL_TRIANGLES, 0, VERTEX_SIZE);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glDeleteVertexArrays(2, VAO);
  glDeleteBuffers(2, VBO);

  glfwTerminate();
  return 0;
}

void processInput(GLFWwindow *window) {
  if (glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    std::cout << "press esc" << std::endl;
    glfwSetWindowShouldClose(window, true);
  }
}

void printTime() {
  using namespace std::chrono;
  auto now = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
  std::cout << now << std::endl;
}
