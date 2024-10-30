#pragma once

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "src/Renderer.h"
#include "src/BatchRenderer.h"

namespace tests
{

    class Test
    {

    public:

        Test() {}
        virtual ~Test() {}

        virtual void OnUpdate(float deltaTime) {}
        virtual void OnRender() {}
        virtual void OnImGuiRender() {}

        virtual void WindowInit(GLFWwindow *window) {}
        virtual void ProcessInput(GLFWwindow *window) {}

    };

};