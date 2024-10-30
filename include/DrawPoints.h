#pragma once

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>
#include <random>
#include "myTools/LinkShader.h"
inline std::vector<GLfloat> vertex;
inline std::vector<GLfloat> radius;
inline std::vector<GLfloat> colorR;
inline std::vector<GLfloat> colorG;
inline std::vector<GLfloat> colorB;
// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void leftmouse_drag_callback(GLFWwindow* window, int button, int action, int mods);
// Window dimensions
constexpr GLuint WIDTH = 700, HEIGHT = 700;

inline std::random_device rd;
inline std::mt19937 gen(rd());
inline std::uniform_real_distribution<float> dis(-0.5, 0.5);
inline GLfloat x = dis(gen);
inline GLfloat y = dis(gen);
inline GLfloat z = dis(gen);
// Shaders
// The MAIN function, from here we start the application and run the game loop
inline int DrawPoints()
{
    // Init GLFW
    if (!glfwInit()) {
      int error = glfwGetError(nullptr);
      std::cerr << "GLFW initialization failed: " << error << std::endl;
      return -1;
    }

    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    // Set the required callback functions
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, leftmouse_drag_callback);

    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to set up the OpenGL Function pointers
    glewInit();


    // Define the viewport dimensions
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    // Build and compile our shader program
    GLuint vertexShader = UseVertexShader("../Shaders/DrawPoints/VertexShader.glsl");
    GLuint fragmentShader = UseFragmentShader("../Shaders/DrawPoints/FragmentShader.glsl");
    GLuint geometryShader = UseGeometryShader("../Shaders/DrawPoints/GeometryShader.glsl");

    // Link shaders
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, geometryShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // Check for linking errors
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteShader(geometryShader);

    glEnable(GL_POINT_SPRITE);
    glPointParameterf(GL_POINT_SPRITE_COORD_ORIGIN, GL_UPPER_LEFT);
    glPointSize( 25.0f );
    glLineWidth( 5.0f);
    glBegin(GL_POINTS);

    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        GLuint VBO, VAO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(vertex.size()) * sizeof(GLfloat), static_cast<const void*>(vertex.data()),  GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), static_cast<GLvoid *>(nullptr));
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind
        glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)

        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
        glBindVertexArray(VAO);

        // Render
        // Clear the colorbuffer
        glClearColor(0.9f, 0.9f, 1.0f, 0.8f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);

        GLfloat TimeValue = sin(glfwGetTime());
        if (TimeValue <  0.0001f && TimeValue > -0.0001f) {
            x = dis(gen);
            y = dis(gen);
            z = dis(gen);
        }
        for (int i = 0; i < vertex.size()/3; i++) {
            GLint thisRadius = glGetUniformLocation(shaderProgram, "pointRadius");
            GLint vertexColorLocation = glGetUniformLocation(shaderProgram, "myColor");
            glUniform4f(vertexColorLocation, colorR[i]+x*TimeValue, colorG[i]+y*TimeValue,
                colorB[i]+z*TimeValue, 1.0f);
            glUniform1f(thisRadius, radius[i]);
            glDrawArrays(GL_POINTS, i, 1);

        }
        glBindVertexArray(0);
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        // Swap the screen buffers
        glfwSwapBuffers(window);
    }
    // Properly de-allocate all resources once they've outlived their purpose
    // Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate();
    return 0;
}

// Is called whenever a key is pressed/released via GLFW
inline void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}
inline void leftmouse_drag_callback(GLFWwindow* window, int button, int action, int mods) {

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double xpos, ypos;
        int height, width;
        glfwGetCursorPos(window, &xpos, &ypos);
        glfwGetWindowSize(window, &width, &height);
        xpos = (xpos - static_cast<double>(width)/2)*2/width;
        ypos = -(ypos - static_cast<double>(height)/2)*2/height;
        vertex.push_back(static_cast<GLfloat>(xpos));
        vertex.push_back(static_cast<GLfloat>(ypos));
        vertex.push_back(static_cast<GLfloat>(0.0f));
        auto radius_rand = dis(gen);
        radius.push_back(radius_rand * 0.2f+0.15f);
        auto R_rand = dis(gen);
        auto G_rand = dis(gen);
        auto B_rand = dis(gen);
        colorR.push_back(0.5f+R_rand);
        colorG.push_back(0.5f+G_rand);
        colorB.push_back(0.5f+B_rand);
    }
}