#include "texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "logs.h"

Texture::Texture(const char* texturePath, TextureType textureType, WrapMode wrapS, WrapMode wrapT, FilterMode minFilter, FilterMode magFilter){
    m_textureType = textureType;
    
    glGenTextures(1, &m_textureID);
    glBindTexture(GL_TEXTURE_2D, m_textureID);

    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    unsigned char *data = stbi_load(texturePath, &width, &height, &nrChannels, 0);
     if (data) {
        GLenum format;
        if (nrChannels == 1)
            format = GL_RED;
        else if (nrChannels == 3)
            format = GL_RGB;
        else if (nrChannels == 4)
            format = GL_RGBA;
        else {
            Logs::log("Texture.cpp: Unsupported number of channels", Logs::LogType::Error);
            stbi_image_free(data);
            return;
        }

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_set_flip_vertically_on_load(true);  
    } else {
        Logs::log("Texture.cpp: Failed to load texture", Logs::LogType::Error);
    }

    stbi_image_free(data);
}

Texture::~Texture(){
    glDeleteTextures(1, &m_textureID);
}

unsigned int Texture::GetTextureID() const{
    return m_textureID;
}

std::string Texture::GetType() const{
    switch(m_textureType){
        case TextureType::DIFFUSE:
            return "texture_diffuse";
        case TextureType::SPECULAR:
            return "texture_specular";
        default:
            return "NULL_TEXTURE_TYPE";
    }
}
