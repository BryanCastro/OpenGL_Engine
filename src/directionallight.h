#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
class Shader;

class DirectionalLight{
public:
    DirectionalLight(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float intensity);

    void Update();
    void Render();
    glm::vec3 GetDirection() const;
    glm::vec3 GetAmbient() const;
    glm::vec3 GetDiffuse() const;
    glm::vec3 GetSpecular() const;

private:
    glm::vec3 m_direction;

    float m_intensity;
    glm::vec3 m_ambient;
    glm::vec3 m_diffuse;
    glm::vec3 m_specular;

    unsigned int m_VAO;
    unsigned int m_VBO;


};