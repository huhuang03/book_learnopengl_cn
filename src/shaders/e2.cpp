#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <chrono>
#include <math.h>

const int W_WIDTH = 800;
const int W_HEIGHT = 600;

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
    "uniform vec4 ourColor;\n"
    "uniform float offx;\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()"
    "{"
    "   gl_Position = vec4(aPos.x + offx, aPos.y, aPos.z, 1.0);"
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

int createFragmentShader() {
  const char* fragmentShaderSource =
    "#version 330 core\n"
    "out vec4 FragColor;"
    "uniform vec4 ourColor;"
    "void main()"
    "{"
    "   FragColor = ourColor;"
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

  float verticles[] = {
                       -.5f, -.5f, 0,
                       .5f, -.5f, 0,
                       0, .5f, 0,
  };
  int vertexShader = createVertexShader();
  int fragmentShader = createFragmentShader();

  unsigned int shaderProgram;
  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  unsigned int VBO;
  glGenBuffers(1, &VBO);

  unsigned int VAO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(verticles), verticles, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  while (!glfwWindowShouldClose(window)) {
    processInput(window);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);

    // update uniform color
    float timeValue = glfwGetTime();
    float greenValue = sin(timeValue) / 2.0f + 0.5f;
    int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
    glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

    int offxLocation = glGetUniformLocation(shaderProgram, "offx");
    glUniform1f(offxLocation, greenValue);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

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
