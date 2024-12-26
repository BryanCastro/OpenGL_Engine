#include "shadermanager.h"
#include "shader.h"
#include "logs.h"

std::map<std::string, Shader*> ShaderManager::m_shaders;

Shader* ShaderManager::CreateShader(std::string shaderName, const char* vertexPath, const char* fragmentPath){
    Shader* shader = new Shader(vertexPath, fragmentPath);
    if(shader){
        auto found_shader = m_shaders.find(shaderName);
        if(found_shader != m_shaders.end()){
            Logs::log(std::format("ShaderManager.cpp: Shader with name {} already exists", shaderName), Logs::LogType::Warning);
            return found_shader->second;
        }
        else{
            Logs::log(std::format("ShaderManager.cpp: Shader with name {} created", shaderName), Logs::LogType::Success);
            m_shaders[shaderName] = shader;
            return shader;
        }
    }
    Logs::log(std::format("ShaderManager.cpp: Failed to create Shader with name {}", shaderName), Logs::LogType::Warning);
    return nullptr;
}

Shader* ShaderManager::GetShader(std::string shaderName){

   auto found_shader = m_shaders.find(shaderName);
   
   if(found_shader != m_shaders.end()){
       return found_shader->second;
   }
   Logs::log(std::format("ShaderManager.cpp: Shader with name {} not found", shaderName), Logs::LogType::Warning);
   return nullptr;
}

ShaderManager::~ShaderManager(){
    for(auto& shader : m_shaders){
        delete shader.second;
    }
    m_shaders.clear();
}