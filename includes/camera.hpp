#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Camera {
public:
    Camera();
    Camera(bool caUpDown);
    void handleMouse(GLFWwindow *window, double xPos, double yPos);
    void handleScroll(GLFWwindow *window, double xoffset, double yoffset);
    void processInput(GLFWwindow *window);
    glm::mat4 getView();
    float getFov();

private:
    bool canUpDown = true;
    float lastX  = 400, lastY = 300;
    float yaw = 0, pitch = 0;
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    float fov = 45.0f;
};


#endif /* CAMERA_H */
