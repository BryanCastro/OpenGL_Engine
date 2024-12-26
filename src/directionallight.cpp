#include "directionalLight.h"
#include <glad/glad.h> // Include glad to get all the required OpenGL headersp
#include "GLFW/glfw3.h"

DirectionalLight::DirectionalLight(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float intensity){
    m_direction = direction;
    m_ambient = ambient;
    m_diffuse = diffuse;
    m_specular = specular;
    m_intensity = intensity;

}

void DirectionalLight::Update(){
    // Update the light
}

void DirectionalLight::Render(){
    // Render the light

}   


glm::vec3 DirectionalLight::GetDirection() const{
    return m_direction;
}

glm::vec3 DirectionalLight::GetAmbient() const{
    return m_ambient;
}
glm::vec3 DirectionalLight::GetDiffuse() const{
    return m_diffuse;
}
glm::vec3 DirectionalLight::GetSpecular() const{
    return m_specular;
}