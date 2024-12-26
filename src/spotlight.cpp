#include "spotlight.h"
#include <glad/glad.h> // Include glad to get all the required OpenGL headersp
#include "GLFW/glfw3.h"
#include "shader.h"
#include "shadermanager.h"
#include "camera.h"


SpotLight::SpotLight(glm::vec3 position, glm::vec3 direction, float cutOff, float outerCutOff, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float intensity, bool visible){
    m_position = position;
    m_direction = m_direction;
    m_cutOff = cutOff;
    m_outerCutOff = outerCutOff;

    m_ambient = ambient;
    m_diffuse = diffuse;
    m_specular = specular;
    m_intensity = intensity;
    m_bVisible = visible;

    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    glGenBuffers(1, &m_VBO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    m_shader = ShaderManager::GetShader("PointLight");
}

void SpotLight::Update(Camera* camera){
    // Update the light
    model = glm::mat4(1.0f);
    model = glm::translate(model, m_position);
    m_position = camera->GetPosition();
    m_direction = camera->GetForward();

    //m_diffuse = glm::vec3(sin(glfwGetTime()*2.0f), sin(glfwGetTime()*0.7f), sin(glfwGetTime()*1.3f)) * glm::vec3(0.5f);
    //m_ambient = m_diffuse * glm::vec3(0.2f);
}

void SpotLight::Render(Camera* camera){
    // Render the light

    if(m_bVisible){
        glUseProgram(m_shader->GetShaderID());

        m_shader->setVec3("diffuse", m_diffuse);
        m_shader->setMat4("model", model);
        m_shader->setMat4("view", camera->GetView());
        m_shader->setMat4("projection", camera->GetProjection());

        glBindVertexArray(m_VAO);
        //glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
    }

}   


glm::vec3 SpotLight::GetPosition() const{
    return m_position;
}

glm::vec3 SpotLight::GetDirection() const{
    return m_direction;
}

glm::vec3 SpotLight::GetAmbient() const{
    return m_ambient;
}
glm::vec3 SpotLight::GetDiffuse() const{
    return m_diffuse;
}
glm::vec3 SpotLight::GetSpecular() const{
    return m_specular;
}

float SpotLight::GetCutOff() const{
    return m_cutOff;
}

float SpotLight::GetOuterCutOff() const{
    return m_outerCutOff;
}
