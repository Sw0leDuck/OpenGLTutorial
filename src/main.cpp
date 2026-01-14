#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "glsl_compiler.h"
#include "mesh3D.h"
#include "common/algorithm.h"
#include "common/primitive_vertices.h"

#define window_width 640
#define window_height 480

static constexpr float g_fov = 45.0f;

GLFWwindow* window;
compiler::Context glslContext;
graphic::Mesh3D mesh;
float mix = 0.01;
float rotate = 0.0;
float g_time = 0;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main(void)
{
    /* Initialize the library */
    if (!glfwInit())
        return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(window_width, window_height, "Hello World :D!", NULL, NULL);
    if (!window) {
        std::cout << "Failed to create the GLFW window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD\n"; 
        return -1;
    }
    glEnable(GL_DEPTH_TEST);

    // glViewport(0, 0, window_width, window_height);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

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
    
    mesh.load2DTexture("../../../assets/doggo.jpg", GL_RGB);
    mesh.load2DTexture("../../../assets/john-joint.jpg", GL_RGB);
    mesh.load2DTexture("../../../assets/vibe-cat.png", GL_RGBA);
    
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
            
        glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        g_time = glfwGetTime();

        mesh.draw10Cubes(glslContext.getProgram(0), g_time);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    mesh.exit();

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window){
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        mix = common::max(mix-0.005f, 0.01f);
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        mix = common::min(mix+0.005f, 0.99f);
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        rotate += 1;
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        rotate -= 1;
    }
}