#pragma once

#include <GLFW/glfw3.h>

#include "glm.hpp"

struct CameraParameters
{

    glm::vec3 position = glm::vec3(0.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

    float fov = 45.0f;
    float yaw = 0.0f;
    float pitch = 0.0f;

    bool movementInputEnabled = true;
    bool rotationInputEnabled = true;
    bool zoomInputEnabled = false;

    float cameraSpeed = 2.0f;
    float mouseSensitivity = 0.1f;
    float zoomSpeed = 1.0f;

};

class Camera
{

public:

    static Camera* current;
    
    float fov;
    glm::vec3 position;

    bool movementInputEnabled;
    bool rotationInputEnabled;
    bool zoomInputEnabled;

    Camera(CameraParameters parameters);
    ~Camera();

    void InitializeInput(GLFWwindow* window);
    void ProcessInput(GLFWwindow* window, float deltaTime);

    void SetInputFOV(float newFOV);
    void IncreaseInputFOV(float fovIncrease);

    glm::mat4 ViewMatrix();

private:

    bool firstMouseInput;
    float lastMouseX;
    float lastMouseY;

    float yaw;
    float pitch;

    glm::vec3 forward;
    glm::vec3 right;
    glm::vec3 up;

    float cameraSpeed;
    float mouseSensitivity;
    float zoomSpeed;

};

void ScrollCallback(GLFWwindow* window, double x, double y);