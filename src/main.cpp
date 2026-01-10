#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "glsl_compiler.h"
#include "mesh.h"

#define window_width 640
#define window_height 480

GLFWwindow* window;
compiler::context glslContext;
graphic::mesh firstTriangle;

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

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD\n"; 
        return -1;
    }

    // glViewport(0, 0, window_width, window_height);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glslContext.compileShader(
        std::string("../../../shaders/send_color_layout.vert"),
        GL_VERTEX_SHADER,
        0
    );

    glslContext.compileShader(
        std::string("../../../shaders/receive_color.frag"),
        GL_FRAGMENT_SHADER,
        0x1000
    );
    glslContext.linkProgram(0, 0, 0x1000);

    firstTriangle.init();
    firstTriangle.load2DTriangle_VBO_Rainbow(graphic::vert_2DTriangle_VBO_Rainbow,
        sizeof(graphic::vert_2DTriangle_VBO_Rainbow));

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        
        glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glslContext.useProgram(0);
        
        firstTriangle.draw2DTriangle_VBO();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

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
}