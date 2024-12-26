#pragma once
#include <glad/glad.h>
#include <string>

class Texture{
public:
    enum class WrapMode {
        REPEAT = GL_REPEAT,
        MIRRORED_REPEAT = GL_MIRRORED_REPEAT,
        CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE,
        CLAMP_TO_BORDER = GL_CLAMP_TO_BORDER
    };

    enum class FilterMode {
        NEAREST = GL_NEAREST,
        LINEAR = GL_LINEAR,
        NEAREST_MIPMAP_NEAREST = GL_NEAREST_MIPMAP_NEAREST,
        LINEAR_MIPMAP_NEAREST = GL_LINEAR_MIPMAP_NEAREST,
        NEAREST_MIPMAP_LINEAR = GL_NEAREST_MIPMAP_LINEAR,
        LINEAR_MIPMAP_LINEAR = GL_LINEAR_MIPMAP_LINEAR
    };

    enum class TextureType {
        DIFFUSE,
        SPECULAR
    };


    Texture(const char* texturePath,TextureType textureType, WrapMode wrapS = WrapMode::REPEAT, WrapMode wrapT = WrapMode::REPEAT,
            FilterMode minFilter = FilterMode::LINEAR_MIPMAP_LINEAR, FilterMode magFilter = FilterMode::LINEAR);
    unsigned int GetTextureID() const;
    std::string GetType() const;
    ~Texture();
private:
    unsigned int m_textureID;
    TextureType m_textureType;
    
};