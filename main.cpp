#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "ModelLoader.h"
#include "Shader.h"

// Function prototypes
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window, float& scale, float& rotationAngle, int& shadingMode, glm::vec3& lightPos);

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(800, 600, "Deformation Transfer Visualizer", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Initialize GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1f, 0.1f, 0.1f, 0.1f);

    // Load model
    ModelLoader model;
    model.loadModel("t1.obj");

    // Load shaders
    Shader shader(
        "shaders/vertex_shader.glsl",
        "shaders/fragment_shader.glsl"
    );

    // Set up transformation matrices
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.0f, -3.0f)); // Move camera back
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f); // Perspective projection

    // Get uniform locations
    GLuint modelLoc = glGetUniformLocation(shader.getProgram(), "model");
    GLuint viewLoc = glGetUniformLocation(shader.getProgram(), "view");
    GLuint projectionLoc = glGetUniformLocation(shader.getProgram(), "projection");

    // Set light and view positions
    shader.use();
    glUniform3f(glGetUniformLocation(shader.getProgram(), "lightPos"), 1.0f, -2.0f, 3.0f);
    glUniform3f(glGetUniformLocation(shader.getProgram(), "viewPos"), 0.0f, 1.0f, 3.0f);
    glUniform3f(glGetUniformLocation(shader.getProgram(), "lightColor"), 1.0f, 1.0f, 1.0f);

    // Set shading mode (0 for Gouraud, 1 for Phong)
    int shadingMode = 1;
    glUniform1i(glGetUniformLocation(shader.getProgram(), "shadingMode"), shadingMode);

    // Set object color to orange
    shader.use();
    glUniform3f(glGetUniformLocation(shader.getProgram(), "objectColor"), 1.0f, 0.5f, 0.0f);

    // Initial scale factor and rotation angle
    float scale = 1.0f;
    float rotationAngle = 0.0f;

    // Initialize light position
    glm::vec3 lightPos( 1.0f, -2.0f, 3.0f);

    // Rendering loop
    while (!glfwWindowShouldClose(window)) {
        // Process input
        processInput(window, scale, rotationAngle, shadingMode, lightPos);

        // Clear color and depth buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Use shader program
        shader.use();

        // Update light position
        glUniform3f(glGetUniformLocation(shader.getProgram(), "lightPos"), lightPos.x, lightPos.y, lightPos.z);

        // Update model matrix with scaling and rotation
        glm::mat4 modelMatrix = glm::mat4(1.0f);
        modelMatrix = glm::scale(modelMatrix, glm::vec3(scale, scale, scale));
        modelMatrix = glm::rotate(modelMatrix, glm::radians(rotationAngle), glm::vec3(0.0f, 1.0f, 0.0f)); // Rotate around Y-axis

        // Pass matrices to the shader
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        // Toggle shading mode
        glUniform1i(glGetUniformLocation(shader.getProgram(), "shadingMode"), shadingMode);

        // Render the model
        model.render();

        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window, float& scale, float& rotationAngle, int& shadingMode, glm::vec3& lightPos) {
    // Sale
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        scale += 0.005f; 
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        scale -= 0.005f; 
        if (scale < 0.01f) scale = 0.01f;
    }

    // Rotate the model
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        rotationAngle -= 1.0f; 
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        rotationAngle += 1.0f;
    }

    // Change shading mode
    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) {
        shadingMode = 0; // Gouraud
        std::cout << "Gouraud shading mode" << std::endl;
    }
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
        shadingMode = 1; // Phong
        std::cout << "Phong shading mode" << std::endl;
    }

    // Control light position
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        lightPos.y += 0.01f;
        std::cout << "Light position: (" << lightPos.x << ", " << lightPos.y << ", " << lightPos.z << ")" << std::endl;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        lightPos.y -= 0.01f;
        std::cout << "Light position: (" << lightPos.x << ", " << lightPos.y << ", " << lightPos.z << ")" << std::endl;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        lightPos.x -= 0.01f;
        std::cout << "Light position: (" << lightPos.x << ", " << lightPos.y << ", " << lightPos.z << ")" << std::endl;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        lightPos.x += 0.01f;
        std::cout << "Light position: (" << lightPos.x << ", " << lightPos.y << ", " << lightPos.z << ")" << std::endl;
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        lightPos.z -= 0.01f;
        std::cout << "Light position: (" << lightPos.x << ", " << lightPos.y << ", " << lightPos.z << ")" << std::endl;
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        lightPos.z += 0.01f;
        std::cout << "Light position: (" << lightPos.x << ", " << lightPos.y << ", " << lightPos.z << ")" << std::endl;
    }
}
