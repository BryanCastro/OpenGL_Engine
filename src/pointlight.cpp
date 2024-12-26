#include "pointlight.h"
#include <glad/glad.h> // Include glad to get all the required OpenGL headersp
#include "GLFW/glfw3.h"
#include "shader.h"
#include "shadermanager.h"
#include "camera.h"

PointLight::PointLight(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float intensity){
    m_position = position;
    m_ambient = ambient;
    m_diffuse = diffuse;
    m_specular = specular;
    m_intensity = intensity;

    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    glGenBuffers(1, &m_VBO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    m_shader = ShaderManager::GetShader("PointLight");
}

void PointLight::Update(){
    // Update the light
    model = glm::mat4(1.0f);
    model = glm::translate(model, m_position);

    m_diffuse = glm::vec3(sin(glfwGetTime()*2.0f), sin(glfwGetTime()*0.7f), sin(glfwGetTime()*1.3f)) * glm::vec3(0.5f);
    m_ambient = m_diffuse * glm::vec3(0.2f);
}

void PointLight::Render(Camera* camera){
    // Render the light

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


glm::vec3 PointLight::GetPosition() const{
    return m_position;
}

glm::vec3 PointLight::GetAmbient() const{
    return m_ambient;
}
glm::vec3 PointLight::GetDiffuse() const{
    return m_diffuse;
}
glm::vec3 PointLight::GetSpecular() const{
    return m_specular;
}