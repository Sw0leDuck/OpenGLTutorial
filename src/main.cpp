#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "glsl_compiler.h"
#include "mesh.h"
#include "texture.h"
#include "common/algorithm.h"

#define window_width 640
#define window_height 480

GLFWwindow* window;
compiler::context glslContext;
graphic::mesh rectShape;
graphic::texture2D image2D_0;
graphic::texture2D image2D_1;
float mix = 0.5;

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
        std::string("../../../shaders/texture2D_location.vert"),
        GL_VERTEX_SHADER,
        0
    );

    glslContext.compileShader(
        std::string("../../../shaders/texture2D_location.frag"),
        GL_FRAGMENT_SHADER,
        0x1000
    );
    glslContext.linkProgram(0, 0, 0x1000);
    glslContext.useProgram(0);
    glslContext.setInt("ourTexture0", 0, 0);
    glslContext.setInt("ourTexture1", 0, 1);

    image2D_0.init("../../../assets/rect_stone_wall.jpg", GL_RGB);
    image2D_0.loadTexture(false);

    image2D_1.init("../../../assets/vibe-cat.png", GL_RGBA);
    image2D_1.loadTexture(false);

    rectShape.init();
    rectShape.load2DRectangle_2DImage(
        graphic::vert_2DRectangle_2DImage, sizeof(graphic::vert_2DRectangle_2DImage), 
        graphic::indices, sizeof(graphic::indices), 8*sizeof(float));

        
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
            
        glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
            
        glActiveTexture(GL_TEXTURE0);
        image2D_0.bindTexture();
        glActiveTexture(GL_TEXTURE1);
        image2D_1.bindTexture();
        
        glslContext.useProgram(0);
        glslContext.setFloat("mix_percentage", 0, mix);
        rectShape.draw2DRectangle_2DImage();

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

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        mix = common::max(mix-0.0005f, 0.1f);
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        mix = common::min(mix+0.0005f, 0.9f);
    }
}