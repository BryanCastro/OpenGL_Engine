#pragma once
#include "glm/glm.hpp"
#include <vector>
#include <string>

class Shader;
class Texture;


struct Vertex{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

class Mesh{
public: 
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
    void Draw(Shader &shader);

    std::vector<Vertex> m_vertices;
    std::vector<unsigned int> m_indices;
    std::vector<Texture> m_textures;

private:
    void setupMesh();

    unsigned int m_VAO, m_VBO, m_EBO;
};