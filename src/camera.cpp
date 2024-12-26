#include "camera.h"
#include "GLFW/glfw3.h"
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp> 
#include <algorithm>

Camera::Camera(glm::vec3 position, unsigned int scr_width, unsigned int scr_height){
    m_lastX = m_src_width/2;
    m_lastY = m_src_height/2;

    m_position = position;
    m_worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    m_src_width = scr_width;
    m_src_height = scr_height;

    glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    m_cameraForward = glm::vec3(0.0f, 0.0f, -1.0f);
    m_cameraRight = glm::normalize(glm::cross(m_worldUp, m_cameraForward));
    m_cameraUp = glm::cross(m_cameraForward, m_cameraRight);

    m_view = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    m_projection = glm::mat4(1.0f);
    m_projection = glm::perspective(glm::radians(45.0f), (float)m_src_width / (float)m_src_height, 0.1f, 100.0f);

}

void Camera::Input(GLFWwindow *window, float deltaTime){
    float cameraSpeed = m_cameraSpeed * deltaTime;
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        m_position += cameraSpeed * m_cameraForward;
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        m_position -= cameraSpeed * m_cameraForward;
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        m_position -= glm::normalize(glm::cross(m_cameraForward, m_cameraUp)) * cameraSpeed;
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        m_position += glm::normalize(glm::cross(m_cameraForward, m_cameraUp)) * cameraSpeed;    
}

void Camera::MouseInput(double xpos, double ypos){

    if(b_firstMouse){
        m_lastX = xpos;
        m_lastY = ypos;
        b_firstMouse = false;
    }

    float xoffset = xpos - m_lastX;
    float yoffset = m_lastY - ypos;
    m_lastX = xpos;
    m_lastY = ypos;

    xoffset *= m_sensitivity;
    yoffset *= m_sensitivity;

    m_yaw += xoffset;
    m_pitch += yoffset;

    if(m_pitch >89.0f)
        m_pitch = 89.0f;
    if(m_pitch <-89.0f)
        m_pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    direction.y = sin(glm::radians(m_pitch));
    direction.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_cameraForward = glm::normalize(direction);
}

void Camera::MouseScroll(double xoffset, double yoffset){
    float new_fov = m_fov - (float)yoffset;
    UpdateFOV(new_fov);
}

void Camera::Update(){

    const float radius = 10.0f;
    float camX = static_cast<float>(sin(glfwGetTime())) * radius;
    float camZ = static_cast<float>(cos(glfwGetTime())) * radius;

    m_view = glm::lookAt(m_position, m_position + m_cameraForward, m_cameraUp);

    //m_view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), m_worldUp);  
}

void Camera::Render(){

}
glm::mat4 Camera::GetView() const { return m_view; }
glm::mat4 Camera::GetProjection() const { return m_projection; }

void Camera::UpdateProjectionMatrix(unsigned int scr_width, unsigned int scr_height){
    m_src_width = scr_width;
    m_src_height = scr_height;
    m_projection = glm::perspective(glm::radians(45.0f), (float)m_src_width / (float)m_src_height, 0.1f, 100.0f);
}

void Camera::UpdateFOV(float fov){
    m_fov = std::clamp(fov, 1.0f, m_maxFOV);
    m_projection = glm::perspective(glm::radians(m_fov), (float)m_src_width / (float)m_src_height, 0.1f, 100.0f);
}

glm::vec3 Camera::GetPosition() const{
    return m_position;
}

glm::vec3 Camera::GetForward() const{
    return m_cameraForward;
}

glm::vec3 Camera::GetRight() const{
    return m_cameraRight;
}

glm::vec3 Camera::GetUp() const{
    return m_cameraUp;
}
