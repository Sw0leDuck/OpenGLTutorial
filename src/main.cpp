#include "Backend/backend.h"

int main(void) {
    if(!backend::Init())
        return -1;
    
    backend::TestLoadWorld();
    
    while(!backend::IsWindowClose()){
        backend::BeginFrame(); // checks inputs
        backend::UpdateFrame(); // opengl calls mostly
        backend::EndFrame(); // Swap buffers and poll events
    }

    backend::Exit();
    return 0;
}