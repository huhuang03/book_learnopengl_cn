#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <chrono>
#include <math.h>
#include "../comm/Shader.hpp"
#include "std_image.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

const int W_WIDTH = 800;
const int W_HEIGHT = 600;

const int ATTR_LEN = 8;

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

  Shader ourShader("./src/trans/trans.vs", "./src/trans/trans.fs");

  float vertices[] = {
                       // lcoation   // color  // 纹理
                       .5f,   .5f, 0,  1, 0, 0,  1, 1, // 右上
                       .5f,  -.5f, 0,  0, 1, 0,  1, 0, //右下
                       -.5f, -.5f, 0,  0, 0, 1,  0, 0, //左下
                       -.5f,  .5f, 0,  1, 1, 0,  0, 1   // 左上
  };

  unsigned int indices[] = {
                           0, 1, 3,
                           1, 2, 3
  };


  unsigned int VAO, VBO, EBO;

  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  // pos
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, ATTR_LEN * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  // color
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, ATTR_LEN * sizeof(float), (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  // texture
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, ATTR_LEN * sizeof(float), (void*)(6 * sizeof(float)));
  glEnableVertexAttribArray(2);

  unsigned int texture1, texture2;
  // texture1
  glGenTextures(1, &texture1);
  glBindTexture(GL_TEXTURE_2D, texture1);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_FILTER_CONTROL, GL_NEAREST);
  // 在两个最匹配像素大小的多级渐远纹理之间进行线性插值，使用邻近插值进行采样
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_FILTER_CONTROL, GL_NEAREST_MIPMAP_NEAREST);

  int width, height, nrChannels;
  stbi_set_flip_vertically_on_load(true);
  unsigned char *data = stbi_load("imgs/container.jpg", &width, &height, &nrChannels, 0);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);
  stbi_image_free(data);


  glGenTextures(1, &texture2);
  glBindTexture(GL_TEXTURE_2D, texture2);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_FILTER_CONTROL, GL_NEAREST);
  // 在两个最匹配像素大小的多级渐远纹理之间进行线性插值，使用邻近插值进行采样
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_FILTER_CONTROL, GL_NEAREST_MIPMAP_NEAREST);
  stbi_set_flip_vertically_on_load(true);
  data = stbi_load("imgs/awesomeface.png", &width, &height, &nrChannels, 0);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);
  stbi_image_free(data);


  ourShader.use();
  ourShader.setInt("texture1", 0);
  ourShader.setInt("texture2", 1);


  while (!glfwWindowShouldClose(window)) {

    processInput(window);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);


    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::translate(trans, glm::vec3(0.5f, -0.5, 0.0));
    trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0, 0.0, 1.0f));
    unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    trans = glm::mat4(1.0f);
    trans = glm::translate(trans, glm::vec3(-0.5f, 0.5f, 0));
    float scaleAmout = sin(glfwGetTime());
    trans = glm::scale(trans, glm::vec3(scaleAmout, scaleAmout, scaleAmout));
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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
