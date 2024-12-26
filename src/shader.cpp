#include "shader.h"
#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include "logs.h"
#include <glm/gtc/type_ptr.hpp> 
#include "materials.h"
#include "pointlight.h"
#include "directionallight.h"
#include "spotlight.h"

Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath){
    
    std::string vertexCode = ReadShaderFile(vertexShaderPath);
    std::string fragmentCode = ReadShaderFile(fragmentShaderPath);
    const char* vertexShaderSource = vertexCode.c_str();
    const char* fragmentShaderSource = fragmentCode.c_str();
    
    unsigned int vertexShader;
    unsigned int fragmentShader;
    
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    
    //Check compilation errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        Logs::log("Shader.cpp: Vertex shader compilation failed\n" + std::string(infoLog), Logs::LogType::Error);
    }

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    //Check compilation errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        Logs::log("Shader.cpp: Fragment shader compilation failed\n" + std::string(infoLog), Logs::LogType::Error);
    }

    m_shaderProgram = glCreateProgram();

    glAttachShader(m_shaderProgram, vertexShader);
    glAttachShader(m_shaderProgram, fragmentShader);
    glLinkProgram(m_shaderProgram);

    glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(m_shaderProgram, 512, nullptr, infoLog);
        Logs::log("Shader.cpp: Shader program linking failed\n" + std::string(infoLog), Logs::LogType::Error);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

unsigned int Shader::GetShaderID() const{
    return m_shaderProgram;
}

std::string Shader::ReadShaderFile(const char* shaderFilePath){
    std::ifstream shaderFile;
    std::stringstream shaderStream;

    shaderFile.open(shaderFilePath);
    if (shaderFile.is_open()) {
        shaderStream << shaderFile.rdbuf();
        shaderFile.close();
    } else {
        Logs::log("Shader.cpp: Failed to open shader file: " + std::string(shaderFilePath), Logs::LogType::Error);
    }

    return shaderStream.str();
}

void Shader::setBool(const std::string &name, bool value) const
{         
    glUniform1i(glGetUniformLocation(m_shaderProgram, name.c_str()), (int)value); 
}

void Shader::setInt(const std::string &name, int value) const
{ 
    glUniform1i(glGetUniformLocation(m_shaderProgram, name.c_str()), value); 
}

void Shader::setFloat(const std::string &name, float value) const
{ 
    glUniform1f(glGetUniformLocation(m_shaderProgram, name.c_str()), value); 
} 

void Shader::setVec3(const std::string &name, const glm::vec3 &value) const {
    glUniform3fv(glGetUniformLocation(m_shaderProgram, name.c_str()), 1, glm::value_ptr(value));
}

void Shader::setVec4(const std::string &name, const glm::vec4 &value) const {
    glUniform4fv(glGetUniformLocation(m_shaderProgram, name.c_str()), 1, glm::value_ptr(value));
}

void Shader::setMat4(const std::string &name, const glm::mat4 &value) const { // New function
    glUniformMatrix4fv(glGetUniformLocation(m_shaderProgram, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setMaterialClassic(MaterialClassic material){
    setVec3("material.ambient", material.ambient);
    setVec3("material.diffuse", material.diffuse);
    setVec3("material.specular", material.specular);
    setFloat("material.shininess", material.shininess);
}


void Shader::setPointLight(PointLight* light, int index) {
    std::stringstream ss;
    
    ss << "pointLights[" << index << "].position";
    setVec3(ss.str(), light->GetPosition());
    ss.str(""); ss.clear(); // Clear the stringstream

    ss << "pointLights[" << index << "].ambient";
    setVec3(ss.str(), light->GetAmbient());
    ss.str(""); ss.clear(); // Clear the stringstream

    ss << "pointLights[" << index << "].diffuse";
    setVec3(ss.str(), light->GetDiffuse());
    ss.str(""); ss.clear(); // Clear the stringstream

    ss << "pointLights[" << index << "].specular";
    setVec3(ss.str(), light->GetSpecular());
    ss.str(""); ss.clear(); // Clear the stringstream

    ss << "pointLights[" << index << "].constant";
    setFloat(ss.str(), 1.0f);
    ss.str(""); ss.clear(); // Clear the stringstream

    ss << "pointLights[" << index << "].linear";
    setFloat(ss.str(), 0.09f);
    ss.str(""); ss.clear(); // Clear the stringstream

    ss << "pointLights[" << index << "].quadratic";
    setFloat(ss.str(), 0.032f);
}

void Shader::setDirectionalLight(DirectionalLight* light){
    setVec3("dirLight.direction", light->GetDirection());
    setVec3("dirLight.ambient", light->GetAmbient());
    setVec3("dirLight.diffuse", light->GetDiffuse());
    setVec3("dirLight.specular", light->GetSpecular());
}

void Shader::setSpotLight(SpotLight* light){
    setVec3("spotLight.position",  light->GetPosition());
    setVec3("spotLight.direction", light->GetDirection());  
    setFloat("spotLight.cutOff",  glm::cos(glm::radians(light->GetCutOff())));    
    setFloat("spotLight.outerCutOff", glm::cos(glm::radians(light->GetOuterCutOff())));
    
    setVec3("spotLight.ambient", light->GetAmbient());
    setVec3("spotLight.diffuse", light->GetDiffuse());
    setVec3("spotLight.specular", light->GetSpecular());

    setFloat("spotLight.constant", 1.0f);
    setFloat("spotLight.linear", 0.09f);
    setFloat("spotLight.quadratic", 0.032f);
}