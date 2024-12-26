#include "cube.h"
#include "glad/glad.h"
#include "shader.h"
#include "texture.h"
#include "shadermanager.h"
#include "texturemanager.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "logs.h"
#include <cstdlib>
#include <ctime>
#include "materials.h"
#include "pointlight.h"
#include "directionallight.h"
#include "spotlight.h"
#include "camera.h"

Cube::Cube(glm::vec3 position){

    m_position = position;
    rotation_vector = glm::vec3(
        (float(rand()) / RAND_MAX), // x: [-1, 1]
        (float(rand()) / RAND_MAX), // y: [-1, 1]
        (float(rand()) / RAND_MAX)  // z: [-1, 1]
    );
    // Generate the VAO
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    // Generate the VBO
    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_STATIC_DRAW);

    // Generate the EBO
    
    /*
    glGenBuffers(1, &m_EBO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_indices), m_indices, GL_STATIC_DRAW); 
    */

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);  

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 

    m_shader = ShaderManager::GetShader("Cube");
    m_texture[0] = TextureManager::GetTexture("Container2");
    m_texture[1] = TextureManager::GetTexture("Container2Specular");

    m_material = new Material(0, 1, 64.0f);
}

void Cube::Render(Camera* camera, PointLight* pointLights[], DirectionalLight* directionalLight, SpotLight* spotLight){
    //float timeValue = glfwGetTime();
    ///float greenValue = (sin(timeValue) / 2.0f) + 0.5f; 
    // m_shader->setVec4("ourColor", glm::vec4(0.0f, greenValue, 0.0f, 1.0f));

    //Both
    m_shader->setVec3("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));

    m_shader->setVec3("viewPos", camera->GetPosition());
    m_shader->setMat4("model", model);
    m_shader->setMat4("view", camera->GetView());
    m_shader->setMat4("projection", camera->GetProjection());    

    //Directional Lighting
    m_shader->setDirectionalLight(directionalLight);
    
    //Point Lighting
    for(int i=0;i<4;i++){
        m_shader->setPointLight(pointLights[i], i);
    }
    //Spot Lighting
    m_shader->setSpotLight(spotLight);

    //Material & textures
    m_shader->setInt("material.diffuse", 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_texture[0]->GetTextureID());
    m_shader->setInt("material.specular", 1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, m_texture[1]->GetTextureID());
    m_shader->setFloat("material.shininess", m_material->shininess);

    glUseProgram(m_shader->GetShaderID());
    //glBindTexture(GL_TEXTURE_2D, m_texture->GetTextureID());
    glBindVertexArray(m_VAO);
    //glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}

void Cube::Update(){

    model = glm::mat4(1.0f);
    model = glm::translate(model, m_position);
    model = glm::rotate(model, (float)glfwGetTime(),rotation_vector);
}

