#include "glad/glad.h"
#include "API/OpenGL/GLTexture.h"

namespace tartarus {

bool GLTexture2D::Init(uint textureId){
    _textureId = textureId;
    return true;
}

bool GLTexture2D::Exit(){
    return true;
}

void GLTexture2D::BindTexture(){
    glBindTexture(GL_TEXTURE_2D, _textureId);
}

void GLTexture2D::UnbindTexture(){
    glBindTexture(GL_TEXTURE_2D, 0);
}

void GLTexture2D::SetTextureMetadata(RawImage data, uint target, uint type){
    _texArgs._imageData = data;
    _texArgs._target = target;
    _texArgs._type = type;
}

void GLTexture2D::LoadImage(){
    this->BindTexture();

    glTextureParameteri(_textureId, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTextureParameteri(_textureId, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTextureParameteri(_textureId, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTextureParameteri(_textureId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        _texArgs._type,
        _texArgs._imageData._width,
        _texArgs._imageData._height,
        0,
        _texArgs._type,
        GL_UNSIGNED_BYTE,
        _texArgs._imageData._data
    );

    this->UnbindTexture();
}


}