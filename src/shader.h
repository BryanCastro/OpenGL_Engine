#pragma once
#include <string>
#include <glm/glm.hpp>

struct MaterialClassic;
class PointLight;
class DirectionalLight;
class SpotLight;

class Shader{
    public:
    Shader(const char* vertexShaderSource, const char* fragmentShaderSource);
    unsigned int GetShaderID() const;
    
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const; 
    void setFloat(const std::string &name, float value) const;
    void setVec3(const std::string &name, const glm::vec3 &value) const;
    void setVec4(const std::string &name, const glm::vec4 &value) const;
    void setMat4(const std::string &name, const glm::mat4 &value) const; 
    void setMaterialClassic(MaterialClassic material);
    void setPointLight(PointLight* light, int index);
    void setDirectionalLight(DirectionalLight* light);  
    void setSpotLight(SpotLight* light);    
    private:
    unsigned int m_shaderProgram;
    std::string ReadShaderFile(const char* shaderFilePath);
};