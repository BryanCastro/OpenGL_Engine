#pragma once
#include "glfw/glfw3.h"
#include "glm/glm.hpp"

class Camera{
public:
    Camera(glm::vec3 position, unsigned int scr_width, unsigned int scr_height);
    glm::mat4 GetView() const;
    glm::mat4 GetProjection() const;
    void Input(GLFWwindow *window, float deltaTime);
    void MouseInput(double xpos, double ypos);
    void MouseScroll(double xoffset, double yoffset);
    void Update();
    void Render();
    void UpdateProjectionMatrix(unsigned int scr_width, unsigned int scr_height);
    void UpdateFOV(float fov);
    
    glm::vec3 GetPosition() const;
    glm::vec3 GetForward() const;
    glm::vec3 GetRight() const;
    glm::vec3 GetUp() const;

private:
    glm::vec3 m_position; 
    glm::vec3 m_cameraForward;
    glm::vec3 m_cameraRight;
    glm::vec3 m_cameraUp;
    glm::vec3 m_worldUp;

    glm::mat4 m_view;
    glm::mat4 m_projection;

    unsigned int m_src_width;
    unsigned int m_src_height;

    const float m_cameraSpeed = 25.0f; 
    const float m_sensitivity = 0.1f;
    
    float m_lastX;
    float m_lastY;
    float m_pitch=0.0f;
    float m_yaw = -90.0f;
    bool b_firstMouse = true;

    float m_fov = 45.0f;
    const float m_maxFOV = 90.0f;
};