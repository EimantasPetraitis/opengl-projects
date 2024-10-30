#include "TestMenu.h"

#include <GL/glew.h>
#include <imgui.h>

namespace tests
{

    TestMenu::TestMenu(
        Test*& currentTestPointer, GLFWwindow* window
    )
        : currentTest(currentTestPointer),
        window(window)
    {}

    TestMenu::~TestMenu()
    {}

    void TestMenu::OnImGuiRender()
    {

        for (int i = 0; i < testList.size(); i++)
        {
            if (ImGui::Button(testList[i].first.c_str()))
            {
                currentTest = testList[i].second();
                currentTest->WindowInit(window);
            }
        }

    }

}