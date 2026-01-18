#ifndef BACKEND_H
#define BACKEND_H

namespace backend {

    bool Init();
    bool Exit();

    void BeginFrame();
    void UpdateFrame();
    void EndFrame();

    // GLFW Window methods
    void* GetWindow();
    bool IsWindowClose();

    void TestLoadWorld();
    void UpdateTestWorld(float delta_time);

} // namespace backend

#endif