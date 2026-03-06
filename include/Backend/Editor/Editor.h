#ifndef EDITOR_H
#define EDITOR_H

#include "glfw/glfw3.h"

namespace tartarus::imgui {

struct Editor {
    bool Init(GLFWwindow* window);
    bool Exit();

    void PreFrame();
    void PostFrame();


    GLFWwindow* _window;
    bool _used = false;
};

}

#endif