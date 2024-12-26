#include "model.h"
#include "mesh.h"
#include "shader.h"
#include "logs.h"
#include <iostream>
#include <string>

Model::Model(const char* path){
    loadModel(path);
}

void Model::Draw(Shader& shader){
    for(unsigned int i=0;i<m_Meshes.size();i++){
        m_Meshes[i].Draw(shader);
    }
};

void Model::loadModel(const std::string& path){
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode){
        Logs::log(std::format("Model.cpp: Assimp error: {}", importer.GetErrorString()), Logs::LogType::Error);

        return;
    }
    m_Directory = path.substr(0, path.find_last_of('/'));

    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene){
    for(unsigned int i=0;i<node->mNumMeshes;i++){
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        m_Meshes.push_back(processMesh(mesh,scene));
    }
    for(unsigned int i=0;i<node->mNumChildren;i++){
        processNode(node->mChildren[i], scene);
    }
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene){
    
}