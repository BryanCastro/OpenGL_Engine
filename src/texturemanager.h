#pragma once

#include <map>
#include <string>
#include "texture.h"

class TextureManager{
    public:
    TextureManager();
    ~TextureManager();
    static Texture* CreateTexture(std::string textureName, const char* texutrePath, Texture::TextureType textureType);
    static Texture* GetTexture(std::string textureName);
    private:
    static std::map<std::string, Texture*> m_textures;
};