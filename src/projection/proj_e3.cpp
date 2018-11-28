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

const float W_WIDTH = 800.0f;
const float W_HEIGHT = 600.0f;

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

  Shader ourShader("./src/projection/more3d.vs", "./src/projection/more3d.fs");

  float vertices[] = {
                      // 前
                       // lcoation   // color  // 纹理
                        .5f,  .5f, 0.5,  1, 0, 0,  1, 1, // 右上
                        .5f, -.5f, 0.5,  0, 1, 0,  1, 0, //右下
                       -.5f, -.5f, 0.5,  0, 0, 1,  0, 0, //左下
                       -.5f,  .5f, 0.5,  1, 1, 0,  0, 1,   // 左上

                      // 后
                       // lcoation   // color  // 纹理
                       -.5f,  .5f, -0.5,  1, 0, 0,  1, 1, // 右上
                       -.5f, -.5f, -0.5,  0, 1, 0,  1, 0, //右下
                        .5f, -.5f, -0.5,  0, 0, 1,  0, 0, //左下
                        .5f,  .5f, -0.5,  1, 1, 0,  0, 1,   // 左上

                      // 左
                       // lcoation   // color  // 纹理
                       -.5f,  .5f,  0.5,  1, 0, 0,  1, 1, // 右上
                       -.5f, -.5f,  0.5,  0, 1, 0,  1, 0, //右下
                       -.5f, -.5f, -0.5,  0, 0, 1,  0, 0, //左下
                       -.5f,  .5f, -0.5,  1, 1, 0,  0, 1,   // 左上

                      // 右
                       // lcoation   // color  // 纹理
                        .5f,  .5f, -0.5,  1, 0, 0,  1, 1, // 右上
                        .5f, -.5f, -0.5,  0, 1, 0,  1, 0, //右下
                        .5f, -.5f,  0.5,  0, 0, 1,  0, 0, //左下
                        .5f,  .5f,  0.5,  1, 1, 0,  0, 1,   // 左上
                        
                      // 上
                       // lcoation   // color  // 纹理
                        .5f,  .5f, -0.5,  1, 0, 0,  1, 1, // 右上
                        .5f,  .5f,  0.5,  0, 1, 0,  1, 0, //右下
                       -.5f,  .5f,  0.5,  0, 0, 1,  0, 0, //左下
                       -.5f,  .5f, -0.5,  1, 1, 0,  0, 1,   // 左上

                      // 下
                       // lcoation   // color  // 纹理
                         .5f, -.5f,  0.5,  1, 0, 0,  1, 1, // 右上
                         .5f, -.5f, -0.5,  0, 1, 0,  1, 0, //右下
                        -.5f, -.5f, -0.5,  0, 0, 1,  0, 0, //左下
                        -.5f, -.5f,  0.5,  1, 1, 0,  0, 1,   // 左上
  };

  unsigned int indices[] = {
                            // 前
                           0, 1, 3,
                           1, 2, 3,

                            // 前
                           0 + 4, 1 + 4, 3 + 4,
                           1 + 4, 2 + 4, 3 + 4,

                            // 左
                           0 + 8, 1 + 8, 3 + 8,
                           1 + 8, 2 + 8, 3 + 8,

                            // 右
                           0 + 12, 1 + 12, 3 + 12,
                           1 + 12, 2 + 12, 3 + 12,

                            // 上
                           0 + 16, 1 + 16, 3 + 16,
                           1 + 16, 2 + 16, 3 + 16,

                            // 下
                           0 + 20, 1 + 20, 3 + 20,
                           1 + 20, 2 + 20, 3 + 20,
  };

  glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f), 
    glm::vec3( 2.0f,  5.0f, -15.0f), 
    glm::vec3(-1.5f, -2.2f, -2.5f),  
    glm::vec3(-3.8f, -2.0f, -12.3f),  
    glm::vec3( 2.4f, -0.4f, -3.5f),  
    glm::vec3(-1.7f,  3.0f, -7.5f),  
    glm::vec3( 1.3f, -2.0f, -2.5f),  
    glm::vec3( 1.5f,  2.0f, -2.5f), 
    glm::vec3( 1.5f,  0.2f, -1.5f), 
    glm::vec3(-1.3f,  1.0f, -1.5f)  
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

  int indicesLen = sizeof(indices) / sizeof(unsigned int);

  glEnable(GL_DEPTH_TEST);

  while (!glfwWindowShouldClose(window)) {

    processInput(window);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);

    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    view = glm::translate(view, glm::vec3(0, 0, -3));
    projection = glm::perspective(glm::radians(45.0f), W_WIDTH / W_HEIGHT, 0.1f, 1000.0f);

    ourShader.setMat4("view", view);
    ourShader.setMat4("projection", projection);

    glBindVertexArray(VAO);
    for (unsigned int i = 0; i < 10; i++) {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, cubePositions[i]);
        float angle = 20 * i;
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

        if (i == 0 || (i % 3) == 0) {
            model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0));
        }
        ourShader.setMat4("model", model);
        glDrawElements(GL_TRIANGLES, indicesLen, GL_UNSIGNED_INT, 0);
    }

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
