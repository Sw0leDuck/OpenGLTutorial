#include "Backend/Editor/Editor.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

namespace tartarus::imgui {

bool Editor::Init(GLFWwindow* window){
    _used = true;
    _window = window;
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    // Enable Keyboard Controlsc
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    // io.WantCaptureMouse = true;
    // io.WantCaptureKeyboard = true;

    ImGui_ImplGlfw_InitForOpenGL(_window, true);
    ImGui_ImplOpenGL3_Init();
    return true;
}

void Editor::PreFrame(){
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGui::ShowDemoWindow(); // Show demo window! :)
}

void Editor::PostFrame(){
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

bool Editor::Exit(){
    if(!_used)
        return true;
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    return true;
}

}