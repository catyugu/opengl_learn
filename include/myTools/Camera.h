#ifndef MYCAMERA_H
#define MYCAMERA_H
#include "LinkShader.h"
#define GLEW_STATIC
#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Camera {
public:
        explicit Camera(
                unsigned int width = 800, unsigned int height = 600,
                glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f),
                glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
                glm::vec3 yaw = glm::vec3(0.0f, 0.0f, 0.0f)
                ) {
                CameraPos = position;
                WorldUp = up;
                Width = width;
                Height = height;
                lastX = width / 2.0f;
                lastY = height / 2.0f;
                firstMouse = true;
                updateCameraVectors();
        }
        [[nodiscard]] glm::mat4 GetViewMatrix() const {
                return glm::lookAt(CameraPos, CameraPos + CameraFront, CameraUp);
        }
        void updateCameraVectors() {
                glm::vec3 front;
                front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
                front.y = sin(glm::radians(Pitch));
                front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
                CameraFront = glm::normalize(front);

        }
        void key_callback(GLFWwindow *window, int key, int scancode,
          int action, int mode) {
                if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
                        glfwSetWindowShouldClose(window, GL_TRUE);
                if (action == GLFW_PRESS)
                        keys[key] = true;
                else if (action == GLFW_RELEASE)
                        keys[key] = false;
        }
        void mouse_callback(GLFWwindow *window, double xpos, double ypos) {
                if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) !=
                    GLFW_PRESS) {
                        firstMouse = true;
                        return;
                }
                if (firstMouse) {
                        lastX = xpos;
                        lastY = ypos;
                        firstMouse = false;
                }
                float xoffset = xpos - lastX;
                float yoffset = lastY - ypos;
                lastX = xpos;
                lastY = ypos;
                xoffset *= MouseSensitivity;
                yoffset *= MouseSensitivity;
                Yaw += xoffset;
                Pitch += yoffset;
                if (Pitch > 89.9f)
                        Pitch = 89.9f;
                if (Pitch < -89.9f)
                        Pitch = -89.9f;
                updateCameraVectors();
        }
        void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
                if (Zoom >= 5.0f && Zoom <= 55.0f)
                        Zoom -= yoffset;
                if (Zoom <= 5.0f)
                        Zoom = 5.0f;
                if (Zoom >= 55.0f)
                        Zoom = 55.0f;
        }
        void key_movement() {
                if (keys[GLFW_KEY_W])
                        CameraPos += CameraSpeed * CameraFront;
                if (keys[GLFW_KEY_S])
                        CameraPos -= CameraSpeed * CameraFront;
                if (keys[GLFW_KEY_A])
                        CameraPos -= glm::normalize(glm::cross(CameraFront, CameraUp)) * CameraSpeed;
                if (keys[GLFW_KEY_D])
                        CameraPos += glm::normalize(glm::cross(CameraFront, CameraUp)) * CameraSpeed;

        }
        glm::vec3 CameraPos{ 0.0f, 0.0f, 3.0f };
        glm::vec3 CameraFront{ 0.0f, 0.0f, -1.0f };
        glm::vec3 CameraUp{ 0.0f, 1.0f, 0.0f };
        glm::vec3 CameraRight{ 1.0f, 0.0f, 0.0f };
        glm::vec3 WorldUp{ 0.0f, 1.0f, 0.0f };
        bool keys[1024]{};
        int Width{ 800 };
        int Height{ 600 };
        float Yaw { -90.0f };
        float Pitch { 0.0f };
        float CameraSpeed { 0.01f };
        float MouseSensitivity{ 0.002f };
        float Zoom{ 45.0f };
        float lastX{};
        float lastY{};
        bool firstMouse{ true };
        void updateCameraPos() {
                glm::vec3 front;
                front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
                front.y = sin(glm::radians(Pitch));
                front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
                CameraFront = glm::normalize(front);
        }
        [[nodiscard]] glm::mat4 getViewMatrix() const {
                return glm::lookAt(CameraPos, CameraPos + CameraFront, CameraUp);

        }
        [[nodiscard]] glm::mat4 getProjectionMatrix() const{
                return glm::perspective(glm::radians(Zoom),
                        static_cast<float>(Width) / static_cast<float>(Height),
                        0.1f, 100.0f);
        }
};
#endif //MYCAMERA_H
