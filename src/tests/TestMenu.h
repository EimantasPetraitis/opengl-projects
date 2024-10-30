#pragma once

#include <functional>
#include <vector>

#include "Test.h"

namespace tests
{

    class TestMenu : public Test
    {

    public:

        TestMenu(
            Test*& currentTestPointer, GLFWwindow* window
        );
        ~TestMenu() override;

        void OnImGuiRender() override;

        template<typename T>
        void AddTest(const std::string& name)
        {
            testList.push_back(std::make_pair(name, []() { return new T(); }));
        }

    private:

        Test*& currentTest;
        std::vector<std::pair<std::string, std::function<Test*()>>> testList;
        GLFWwindow* window;

    };

};