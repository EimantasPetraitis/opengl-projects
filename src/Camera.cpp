#include "Camera.h"

#include <GLFW/glfw3.h>

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

Camera* Camera::current;

Camera::Camera(
    CameraParameters parameters
)
    : position(parameters.position), up(parameters.up),
    fov(parameters.fov), yaw(parameters.yaw), pitch(parameters.pitch),
    movementInputEnabled(parameters.movementInputEnabled),
    rotationInputEnabled(parameters.rotationInputEnabled),
    zoomInputEnabled(parameters.zoomInputEnabled),
    cameraSpeed(parameters.cameraSpeed),
    mouseSensitivity(parameters.mouseSensitivity),
    zoomSpeed(parameters.zoomSpeed),
    forward(0.0f, 0.0f, -1.0f), firstMouseInput(true)
{

    right = glm::normalize(glm::cross(up, forward));

    current = this;

}

Camera::~Camera()
{

    if (current == this)
        current = nullptr;

}

void Camera::InitializeInput(GLFWwindow *window)
{

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetScrollCallback(window, ScrollCallback);

}

void Camera::ProcessInput(GLFWwindow *window, float deltaTime)
{

    if (rotationInputEnabled)
    {

        double newMouseX, newMouseY;
        glfwGetCursorPos(window, &newMouseX, &newMouseY);

        if (firstMouseInput)
        {
            lastMouseX = newMouseX;
            lastMouseY = newMouseY;
            firstMouseInput = false;
        }

        float deltaX = newMouseX - lastMouseX;
        float deltaY = lastMouseY - newMouseY;

        lastMouseX = newMouseX;
        lastMouseY = newMouseY;

        yaw += deltaX * mouseSensitivity;
        pitch += deltaY * mouseSensitivity;

        if (pitch > 89.5f)
            pitch = 89.5f;
        if (pitch < -89.5f)
            pitch = -89.5f;

        forward.x = cos(glm::radians(yaw))
            * cos(glm::radians(pitch));
        forward.y = sin(glm::radians(pitch));
        forward.z = sin(glm::radians(yaw))
            * cos(glm::radians(pitch));
        forward = glm::normalize(forward);

        right = glm::normalize(glm::cross(up, forward));

    }

    if (movementInputEnabled)
    {

        float distanceMoved = cameraSpeed * deltaTime;

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            position += distanceMoved * forward;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            position -= distanceMoved * forward;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            position -= distanceMoved * right;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            position += distanceMoved * right;
    
    }

}

void Camera::SetInputFOV(float newFOV)
{

    if (!zoomInputEnabled)
        return;

    fov = newFOV;

    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 45.0f)
        fov = 45.0f;

}

void Camera::IncreaseInputFOV(float fovIncrease)
{

    if (!zoomInputEnabled)
        return;
    
    fov += fovIncrease;

    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 45.0f)
        fov = 45.0f;

}

glm::mat4 Camera::ViewMatrix()
{

    glm::mat4 view = glm::lookAt(
        position, position + forward, up
    );
    return view;

}

void ScrollCallback(GLFWwindow* window, double x, double y)
{

    Camera::current->IncreaseInputFOV(-(float)y);

}