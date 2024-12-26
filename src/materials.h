#pragma once

#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

struct MaterialClassic {
    glm::vec3 ambient;  // Ambient color (R, G, B)
    glm::vec3 diffuse;  // Diffuse color (R, G, B)
    glm::vec3 specular; // Specular color (R, G, B)
    float shininess;    // Shininess factor
};

struct Material{
    int glTextureDiffuseID;
    int glTextureSpecularID; // Specular color (R, G, B)
    float shininess;
};

class Materials{
public:


    static const std::unordered_map<std::string, MaterialClassic> materials;

};