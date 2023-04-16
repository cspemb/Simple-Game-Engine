// Local Headers
#define STB_IMAGE_IMPLEMENTATION
#include "glitter.hpp"
#include "ShaderHelpers.h"
#include "ModelLoader.h"

// System Headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Standard Headers
#include <cstdio>
#include <cstdlib>

using glm::vec2;
using glm::vec3;
using glm::mat4;

void setHouseUniforms(GLuint shader, vec3 translation, vec3 scale, vec3 colorMask) {
    mat4 transform = glm::translate(mat4(1.0f), translation);
    transform = glm::scale(transform, scale);
    GLuint vTransform = glGetUniformLocation(shader, "vTransform");
    glUniformMatrix4fv(vTransform, 1, GL_FALSE, glm::value_ptr(transform));

    GLuint colorMaskLocation = glGetUniformLocation(shader, "colorMask");
    glUniform3fv(colorMaskLocation, 1, glm::value_ptr(colorMask));
}

int main(int argc, char * argv[]) {

    // Load GLFW and Create a Window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    auto mWindow = glfwCreateWindow(mWidth, mHeight, "OpenGL", nullptr, nullptr);

    // Check for Valid Context
    if (mWindow == nullptr) {
        fprintf(stderr, "Failed to Create OpenGL Context");
        return EXIT_FAILURE;
    }

    // Create Context and Load OpenGL Functions
    glfwMakeContextCurrent(mWindow);
    gladLoadGL();
    fprintf(stderr, "OpenGL %s\n", glGetString(GL_VERSION));

    glEnable(GL_DEPTH_TEST);

    // **************************************
    // Setup Vertex arrays here
    // **************************************
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    GLuint VBO;
    glGenBuffers(1, &VBO);  
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    vec2 positions[] = { vec2( -0.25f,  0.25f), vec2(-0.25f,  -0.25f), vec2(0.25f, -0.25f), vec2(0.25f, 0.25f), vec2(0.0f, 0.5f) };
    vec3 colors[] = { vec3(.8f, .4f, .0f), vec3(.6f, .2f, .8f), vec3(.4f, .0f, .6f), vec3(.2f, .8f, .4f), vec3(0.0f, .6f, .2f) };
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions) + sizeof(colors), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(positions), positions);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(positions), sizeof(colors), colors);

    GLuint houseShader = LoadProgram("Glitter\\Shaders\\basic.vert", "Glitter\\Shaders\\basic.frag");
    glUseProgram(houseShader);

    GLuint vPosition = glGetAttribLocation(houseShader, "vPosition");
    glEnableVertexAttribArray(vPosition);
    glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), ((void*)(0)));

    GLuint vColor = glGetAttribLocation(houseShader, "vColor");
    glEnableVertexAttribArray(vColor);
    glVertexAttribPointer(vColor, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), ((void*)(sizeof(positions))));

    

    // **************************************

    // Rendering Loop
    while (glfwWindowShouldClose(mWindow) == false) {
        if (glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(mWindow, true);

        // Background Fill Color
        glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // **********************************
        // Add rendering code here
        
        setHouseUniforms(houseShader, vec3(-.5f, -.5f, 0.0f), vec3(1.5f, 1.5f, 0.0f), vec3(1.25f, 0.5f, 0.75f));
        glDrawArrays(GL_TRIANGLE_FAN, 0, std::size(positions));

        setHouseUniforms(houseShader, vec3(0.0f, 0.0f, 0.0f), vec3(1.0f, 1.0f, 0.0f), vec3(.75f, 1.25f, 0.5f));
        glDrawArrays(GL_TRIANGLE_FAN, 0, std::size(positions));

        setHouseUniforms(houseShader, vec3(0.5f, 0.25f, 0.0f), vec3(0.75f, .75f, 0.0f), vec3(.5f, 0.75f, 1.25f));
        glDrawArrays(GL_TRIANGLE_FAN, 0, std::size(positions));

        // **********************************

        // Flip Buffers and Draw
        glfwSwapBuffers(mWindow);
        glfwPollEvents();
    }   glfwTerminate();

    return EXIT_SUCCESS;
}