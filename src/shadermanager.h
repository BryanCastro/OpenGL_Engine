#pragma once
#include <map>
#include <string>

class Shader;

class ShaderManager{
public:
    ~ShaderManager();
    static Shader* CreateShader(std::string shaderName, const char* vertexShaderPath, const char* fragmentShaderPath);
    static Shader* GetShader(std::string shaderName);
private:
    static std::map<std::string, Shader*> m_shaders;
};