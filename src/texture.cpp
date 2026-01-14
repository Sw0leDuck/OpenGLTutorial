#include "texture.h"
#include "glad/glad.h"

#include "image_loader.h"

imageLoader::ImageLoaderManager g_image_manager;

namespace graphic {

    void Texture2D::exit() {
        if(textureId != -1)
            glDeleteTextures(1, &textureId);
    }

    void Texture2D::init(const std::string& filePath, GLenum type){
        glGenTextures(1, &textureId);
        g_image_manager.insertImage(filePath, textureId);
        this->type = type;
    }

    void Texture2D::loadTexture(bool clamp) {
        glBindTexture(GL_TEXTURE_2D, textureId);

        if(!clamp){
            glTextureParameteri(textureId, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTextureParameteri(textureId, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTextureParameteri(textureId, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTextureParameteri(textureId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        }else{
            glTextureParameteri(textureId, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTextureParameteri(textureId, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTextureParameteri(textureId, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTextureParameteri(textureId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        }

        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            type,
            g_image_manager.image_map[textureId].width,
            g_image_manager.image_map[textureId].height,
            0,
            type,
            GL_UNSIGNED_BYTE,
            g_image_manager.image_map[textureId].data
        );
        glGenerateMipmap(GL_TEXTURE_2D);

        g_image_manager.image_map[textureId].unloadImage();
    }

    

};