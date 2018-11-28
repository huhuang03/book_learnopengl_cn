#include "camera.hpp"
#include <stdio.h>

Camera::Camera() {
    Camera(true);
}

Camera::Camera(bool canUpDown) {
    this->canUpDown = canUpDown;
}

glm::mat4 Camera::getView() {
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    return view;
}

float Camera::getFov() {
    return fov;
}

void Camera::handleMouse(GLFWwindow *window, double xPos, double yPos) {
    float xoffset = xPos - this->lastX;
    float yoffset = -(yPos - lastY);
    lastX = xPos;
    lastY = yPos;

    float sensitivity = 0.05f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;
}

void Camera::processInput(GLFWwindow *window) {
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    glm::vec3 front = glm::vec3();
    front.y = sin(glm::radians(pitch));
    front.z = -cos(glm::radians(pitch)) * cos(glm::radians(yaw));
    front.x = cos(glm::radians(pitch)) * sin(glm::radians(yaw));

    float cameraSpeed = 2.5 * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp))  * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp))  * cameraSpeed;

    cameraFront = glm::normalize(front);

    if (!canUpDown) {
        cameraPos.y = 0;
    }
}


void Camera::handleScroll(GLFWwindow *window, double xoffset, double yoffset) {
    if (fov >= 1.0 && fov <= 45.0f) {
        fov += yoffset;
    }
    if (fov <= 1.0f)
        fov = 1.0f;
    if (fov >= 45.0f)
        fov = 45.0f;
}
