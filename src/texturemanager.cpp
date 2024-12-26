#include "texturemanager.h"
#include "logs.h"

std::map<std::string, Texture*> TextureManager::m_textures;

TextureManager::TextureManager(){}

TextureManager::~TextureManager(){
    for(auto& texture : m_textures){
        delete texture.second;
    }
    m_textures.clear();
}

Texture* TextureManager::CreateTexture(std::string textureName, const char* texturePath, Texture::TextureType textureType){
    Texture* texture = new Texture(texturePath, textureType);
    if(texture){
        auto found_texture= m_textures.find(textureName);
        if(found_texture != m_textures.end()){
            Logs::log(std::format("TextureManager.cpp: Texture with name {} already exists", textureName), Logs::LogType::Warning);
            return found_texture->second;
        }
        else{
            Logs::log(std::format("TextureManager.cpp: Texture with name {} created", textureName), Logs::LogType::Success);
            m_textures[textureName] = texture;
            return texture;
        }
    }
    Logs::log(std::format("TextureManager.cpp: Failed to create Texture with name {}", textureName), Logs::LogType::Warning);
    return nullptr;

}

Texture* TextureManager::GetTexture(std::string textureName){
    auto found_texture = m_textures.find(textureName);
    if(found_texture!=m_textures.end()){
        return found_texture->second;
    }
    Logs::log(std::format("TextureManager.cpp: Texture with name {} not found", textureName), Logs::LogType::Warning);
    return nullptr;
}   

