#pragma once
#include <string>
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Mesh;
class Shader;
class Texture;

class Model{   
public:
    Model(const char* path);
    void Draw(Shader& shader);
private:
    std::vector<Mesh> m_Meshes;
    std::string m_Directory;

    void loadModel(const std::string& path);
    void processNode(aiNode* node, const aiScene *scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};