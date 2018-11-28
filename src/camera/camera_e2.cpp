#include "camera.hpp"
#include <stdio.h>

static glm::mat4 myLookAt(glm::vec3 position, glm::vec3 target, glm::vec3 worldUp) {
        // 1. Position = known
    // 2. Calculate cameraDirection
    glm::vec3 zaxis = glm::normalize(position - target);
    // 3. Get positive right axis vector
    glm::vec3 xaxis = glm::normalize(glm::cross(glm::normalize(worldUp), zaxis));
    // 4. Calculate camera up vector
    glm::vec3 yaxis = glm::cross(zaxis, xaxis);

    // Create translation and rotation matrix
    // In glm we access elements as mat[col][row] due to column-major layout
    glm::mat4 translation = glm::mat4(0.0f); // Identity matrix by default
    translation[0][0] = 1.0f;
    translation[1][1] = 1.0f;
    translation[2][2] = 1.0f;
    translation[3][3] = 1.0f;

    translation[3][0] = -position.x; // Third column, first row
    translation[3][1] = -position.y;
    translation[3][2] = -position.z;


    glm::mat4 rotation = glm::mat4(0.0f); // Identity matrix by default
    rotation[0][0] = 1.0f;
    rotation[1][1] = 1.0f;
    rotation[2][2] = 1.0f;
    rotation[3][3] = 1.0f;

    rotation[0][0] = xaxis.x; // First column, first row
    rotation[1][0] = xaxis.y;
    rotation[2][0] = xaxis.z;
    rotation[0][1] = yaxis.x; // First column, second row
    rotation[1][1] = yaxis.y;
    rotation[2][1] = yaxis.z;
    rotation[0][2] = zaxis.x; // First column, third row
    rotation[1][2] = zaxis.y;
    rotation[2][2] = zaxis.z; 

    // Return lookAt matrix as combination of translation and rotation matrix
    return rotation * translation; // Remember to read from right to left (first translation then rotation)
}

Camera::Camera() {
    Camera(true);
}

Camera::Camera(bool canUpDown) {
    this->canUpDown = canUpDown;
}

glm::mat4 Camera::getView() {
    glm::mat4 view = glm::mat4(1.0f);
    view = myLookAt(cameraPos, cameraPos + cameraFront, cameraUp);
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
