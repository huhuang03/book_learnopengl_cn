#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <chrono>
#include <math.h>
#include "../comm/Shader.hpp"

const int W_WIDTH = 800;
const int W_HEIGHT = 600;

void processInput(GLFWwindow *window);

void pritnTime();

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  std::cout << "change window size to " << width << "*" << height << std::endl;;
  glViewport(0, 0, width, height);
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

  Shader ourShader("./src/shaders/shader.vs", "./src/shaders/shader.fs");
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

  float verticles[] = {
                       // lcoation     // color 
                        .5f, -.5f, 0,  1, 0, 0,
                       -.5f, -.5f, 0,  0, 1, 0,
                          0,  .5f, 0,  0, 0, 1
  };

  unsigned int VBO;
  glGenBuffers(1, &VBO);

  unsigned int VAO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(verticles), verticles, GL_STATIC_DRAW);

  // pos
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  // color
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  while (!glfwWindowShouldClose(window)) {
    processInput(window);
    glClear(GL_COLOR_BUFFER_BIT);

    ourShader.use();

    // update uniform color
    float timeValue = glfwGetTime();
    float greenValue = sin(timeValue) / 2.0f + 0.5f;
    ourShader.set4f("ourColor", 0, greenValue, 0, 1);

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
