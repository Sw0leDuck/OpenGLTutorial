#include "glad/glad.h"
#include "API/OpenGL/GLTexture.h"
#include "API/OpenGL/GLTextureManager.h"

namespace tartarus {

bool GLTexture2D::Init(AssetName name, GLTextureManager* managerPtr){
    glGenTextures(1, &_textureId);
    _assetName = name;
    _manager = managerPtr;
    return true;
}

bool GLTexture2D::Exit(){
    glDeleteTextures(1, &_textureId);
    return true;
}

void GLTexture2D::BindTexture(){
    glActiveTexture(GL_TEXTURE0+_attachIndex);
    glBindTexture(GL_TEXTURE_2D, _textureId);
}

void GLTexture2D::UnbindTexture(){
    glBindTexture(GL_TEXTURE_2D, 0);
}

uint GLTexture2D::ConfirmAttachment(){
    auto index = _manager->ConfirmAttachment(this);
    if(index==-1)
        return index;
    _attachIndex = index;
    return index;
}

void GLTexture2D::SetTextureMetadata(RawImage* data, uint target, uint type){
    _texArgs._imageData = data;
    _texArgs._target = target;
    _texArgs._type = type;

    _height = _texArgs._imageData->_height;
    _width = _texArgs._imageData->_width;
    _nrChannels = _texArgs._imageData->_nrChannels;
}

void GLTexture2D::LoadImage(){
    this->BindTexture();

    glTextureParameteri(_textureId, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTextureParameteri(_textureId, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTextureParameteri(_textureId, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTextureParameteri(_textureId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(
        _texArgs._target,
        0,
        _texArgs._type,
        _texArgs._imageData->_width,
        _texArgs._imageData->_height,
        0,
        _texArgs._type,
        GL_UNSIGNED_BYTE,
        _texArgs._imageData->_data
    );
    glGenerateMipmap(_texArgs._target);

    this->UnbindTexture();

    // TODO: probably fix this when i implement changing levels
    _texArgs._imageData = nullptr;
}


}