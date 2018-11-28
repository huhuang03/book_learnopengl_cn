#include "Game.hpp"
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  std::cout << "change window size to " << width << "*" << height << std::endl;;
  glViewport(0, 0, width, height);
}

Game::Game(GLuint width, GLuint height)
    :State(GAME_ACTIVE),
     Keys(),
     Width(width), Height(height)
{
    
}

Game::~Game() {
}

void Game::Init() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  
  #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  #endif
  
    GLFWwindow *window = glfwCreateWindow(Width, Height, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
      std::cout << "Failed to create GLFW window" << std::endl;
      glfwTerminate();
      return;
    }
  
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      std::cout << "Failed to initial GLAD" << std::endl;
      return;
    }
  
      while (!glfwWindowShouldClose(window)) {
          glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
          glClear(GL_COLOR_BUFFER_BIT);
          glfwSwapBuffers(window);
          glfwPollEvents();
    }
  
    glfwTerminate();
    return;
}

void Game::Update(GLfloat dt) {
    
}

void Game::ProcessInput(GLfloat dt) {
    
}

void Game::Render() {
    
}

using namespace std;

const int W_WIDTH = 800;
const int W_HEIGHT = 600;


int main(int argc, char *argv[argc])
{
    Game game(W_WIDTH, W_HEIGHT);
    game.Init();
    
    return 0;
}
