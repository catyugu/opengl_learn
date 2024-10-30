//
// Created by kali on 10/29/24.
//
#pragma once

#ifndef CAMERA_H
#define CAMERA_H

// GLEW
#define GLEW_STATIC
#include "myTools/Camera.h"
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>
// Other Libs
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "myTools/LinkShader.h"
#include <SOIL/SOIL.h>

// Function prototypes
// Window dimensions
static const GLuint WIDTH = 800, HEIGHT = 600;
inline Camera camera( WIDTH, HEIGHT, glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f),
              glm::vec3(0.0f, 0.0f, 0.0f));
inline void key_callback(GLFWwindow *window, int key, int scancode, int action,
                  int mode) {
  camera.key_callback(window, key, scancode, action, mode);
}
inline void mouse_callback(GLFWwindow *window, double xpos, double ypos) {
  camera.mouse_callback(window, xpos, ypos);
}
inline void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
  camera.scroll_callback(window, xoffset, yoffset);
}
// Set up vertex data (and buffer(s)) and attribute pointers
inline float vertices[] = {
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.5f,  -0.5f, -0.5f, 1.0f, 0.0f,
    0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
    -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

    -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 0.5f,  -0.5f, 0.5f,  1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f, 0.5f,  0.5f,  0.0f, 1.0f, -0.5f, -0.5f, 0.5f,  0.0f, 0.0f,

    -0.5f, 0.5f,  0.5f,  1.0f, 0.0f, -0.5f, 0.5f,  -0.5f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, -0.5f, 0.5f,  0.5f,  1.0f, 0.0f,

    0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
    0.5f,  -0.5f, -0.5f, 0.0f, 1.0f, 0.5f,  -0.5f, -0.5f, 0.0f, 1.0f,
    0.5f,  -0.5f, 0.5f,  0.0f, 0.0f, 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.5f,  -0.5f, -0.5f, 1.0f, 1.0f,
    0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, 0.5f,  -0.5f, 0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

    -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, 0.5f,  0.5f,  0.0f, 0.0f, -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f};
inline glm::vec3 cubePositions[] = {
  glm::vec3( 0.0f,  0.0f,  0.0f),
  glm::vec3( 2.0f,  5.0f, -15.0f),
  glm::vec3(-1.5f, -2.2f, -2.5f),
  glm::vec3(-3.8f, -2.0f, -12.3f),
  glm::vec3( 2.4f, -0.4f, -3.5f),
  glm::vec3(-1.7f,  3.0f, -7.5f),
  glm::vec3( 1.3f, -2.0f, -2.5f),
  glm::vec3( 1.5f,  2.0f, -2.5f),
  glm::vec3( 1.5f,  0.2f, -1.5f),
  glm::vec3(-1.3f,  1.0f, -1.5f)
};
// The MAIN function, from here we start the application and run the game loop
inline int UseCamera() {
  // Init GLFW
  glfwInit();
  camera.MouseSensitivity = 0.1f;

  // Create a GLFWwindow object that we can use for GLFW's functions
  GLFWwindow *window =
      glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
  glfwMakeContextCurrent(window);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  // Set the required callback functions
  glfwSetKeyCallback(window, key_callback);
  glfwSetCursorPosCallback(window, mouse_callback);
  glfwSetScrollCallback(window, scroll_callback);

  // Set this to true so GLEW knows to use a modern approach to retrieving
  // function pointers and extensions
  glewExperimental = GL_TRUE;
  // Initialize GLEW to setup the OpenGL Function pointers
  glewInit();

  // Define the viewport dimensions
  glViewport(0, 0, WIDTH, HEIGHT);

  // Build and compile our shader program
  GLuint vertexShader =
      UseVertexShader("../Shaders/UseCamera/VertexShader.glsl");
  GLuint fragmentShader =
      UseFragmentShader("../Shaders/UseCamera/FragmentShader.glsl");

  // Activate z-buffer
  glEnable(GL_DEPTH_TEST);
  GLuint VBO, VAO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // Position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat),
                        (GLvoid *)0);
  glEnableVertexAttribArray(0);
  // TexCoord attribute
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat),
                        (GLvoid *)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(2);

  glBindVertexArray(0); // Unbind VAO

  // Load and create a texture
  GLuint texture1;
  GLuint texture2;
  // ====================
  // Texture 1
  // ====================
  glGenTextures(1, &texture1);
  glBindTexture(GL_TEXTURE_2D,
                texture1); // All upcoming GL_TEXTURE_2D operations now have
                           // effect on our texture object
  // Set our texture parametersz
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                  GL_REPEAT); // Set texture wrapping to GL_REPEAT
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  // Set texture filtering
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  // Load, create texture and generate mipmaps
  int width, height;
  unsigned char *image = SOIL_load_image("../img/container.png", &width,
                                         &height, nullptr, SOIL_LOAD_RGB);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
               GL_UNSIGNED_BYTE, image);
  glGenerateMipmap(GL_TEXTURE_2D);
  SOIL_free_image_data(image);
  glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't
                                   // accidentily mess up our texture.
  // ===================
  // Texture 2
  // ===================
  glGenTextures(1, &texture2);
  glBindTexture(GL_TEXTURE_2D, texture2);
  // Set our texture parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  // Set texture filtering
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  // Load, create texture and generate mipmaps
  image = SOIL_load_image("../img/awesomeface.png", &width, &height, 0,
                          SOIL_LOAD_RGB);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
               GL_UNSIGNED_BYTE, image);
  glGenerateMipmap(GL_TEXTURE_2D);
  SOIL_free_image_data(image);
  glBindTexture(GL_TEXTURE_2D, 0);
  GLuint shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);


  // Game loop
  while (!glfwWindowShouldClose(window)) {
    auto currentFrame = glfwGetTime();
    auto lastFrame = 0;
    auto deltaTime = currentFrame - lastFrame;
    camera.CameraSpeed = std::min(0.005 * deltaTime, 0.01);
    // Check if any events have been activiated (key pressed, mouse moved etc.)
    // and call corresponding response functions
    glfwPollEvents();
    camera.key_movement();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Render
    // Clear the colorbuffer
    glClearColor(1.0f, 0.9f, 0.9f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Activate shader
    glUseProgram(shaderProgram);

    // Bind Textures using texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture1"), 0);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture2"), 1);

    // Create transformations
    glm::mat4 view;
    view = camera.getViewMatrix();
    glm::mat4 projection;
    projection = camera.getProjectionMatrix();
    GLint modelLoc = glGetUniformLocation(shaderProgram, "model");

    GLint viewLoc = glGetUniformLocation(shaderProgram, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

    GLint projectionLoc = glGetUniformLocation(shaderProgram, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));


      glBindVertexArray(VAO);
      for(GLuint i = 0; i < 10; i++)
      {
          auto model = glm::mat4(1.0f);
          model = glm::translate(model, cubePositions[i]);
          GLfloat angle = 20.0f * i;
          model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
          model = glm::rotate(model, (GLfloat)glfwGetTime() * 3.0f,
                    glm::vec3(0.5f, 1.0f, 0.0f));
          glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

          glDrawArrays(GL_TRIANGLES, 0, 36);
      }
      glBindVertexArray(0);

    // Swap the screen buffers
    glfwSwapBuffers(window);
  }
  // Properly de-allocate all resources once they've outlived their purpose
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  // Terminate GLFW, clearing any resources allocated by GLFW.
  glfwTerminate();
  return 0;
}

#endif //CAMERA_H
