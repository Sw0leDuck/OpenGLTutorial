#include "texture.h"
#include "glad/glad.h"

#include "image_loader.h"

imageLoader::ImageLoaderManager g_image_manager;

namespace graphic {

    void Texture2D::Exit() {
        if(_textureId != -1)
            glDeleteTextures(1, &_textureId);
    }

    void Texture2D::Init(const std::string& filePath, GLenum type){
        glGenTextures(1, &_textureId);
        g_image_manager.InsertImage(filePath, _textureId);
        this->_type = type;
    }

    void Texture2D::BindTexture(){
        glBindTexture(GL_TEXTURE_2D, _textureId);
    }

    void Texture2D::LoadTexture(bool clamp) {
        glBindTexture(GL_TEXTURE_2D, _textureId);

        if(!clamp){
            glTextureParameteri(_textureId, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTextureParameteri(_textureId, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTextureParameteri(_textureId, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTextureParameteri(_textureId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        }else{
            glTextureParameteri(_textureId, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTextureParameteri(_textureId, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTextureParameteri(_textureId, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTextureParameteri(_textureId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        }

        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            _type,
            g_image_manager._imageMap[_textureId]._width,
            g_image_manager._imageMap[_textureId]._height,
            0,
            _type,
            GL_UNSIGNED_BYTE,
            g_image_manager._imageMap[_textureId]._data
        );
        glGenerateMipmap(GL_TEXTURE_2D);

        g_image_manager._imageMap[_textureId].UnloadImage();
    }

    

};