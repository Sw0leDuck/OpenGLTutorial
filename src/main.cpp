#include "Backend/backend.h"

#include "glsl_compiler.h"
#include "mesh3D.h"
#include "common/primitive_vertices.h"

compiler::Context glslContext;
graphic::Mesh3D mesh;

int main(void) {
    if(!backend::Init())
        return -1;

    glslContext.compileShader(
        std::string("../../../shaders/texture2D_location.vert"),
        GL_VERTEX_SHADER,
        0
    );

    glslContext.compileShader(
        std::string("../../../shaders/texture2D_location.frag"),
        GL_FRAGMENT_SHADER,
        0x1000
    );
    glslContext.linkProgram(ProgramType::kDefault, 0, 0x1000);
    glslContext.useProgram(ProgramType::kDefault);
    glslContext.setInt("ourTexture0", ProgramType::kDefault, 0);
    glslContext.setInt("ourTexture1", ProgramType::kDefault, 1);


    mesh.init();
    mesh.loadCube_TexCoords(graphic::cube_vertices, sizeof(graphic::cube_vertices), 5*sizeof(float));
    
    // mesh.load2DTexture("../../../assets/doggo.jpg", GL_RGB);
    // mesh.load2DTexture("../../../assets/john-joint.jpg", GL_RGB);
    mesh.load2DTexture("../../../assets/vibe-cat.png", GL_RGBA);
    
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while(!backend::IsWindowClose()){
        backend::BeginFrame(); // checks inputs
        backend::UpdateFrame(); // opengl calls mostly
        backend::EndFrame(); // Swap buffers and poll events
    }

    mesh.exit();
    backend::Exit();
    return 0;
}