#pragma once

#include "Test.h"

namespace tests
{

    class TestClearColor : public Test
    {

    public:

        TestClearColor();
        ~TestClearColor() override;

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;

    private:

        float clearColor[4];

        int windowWidth;
        int windowHeight;

    };

};