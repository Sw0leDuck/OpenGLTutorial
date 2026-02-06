#include "API/OpenGL/GLUtil.h"
#include "API/OpenGL/GLTexture.h"
#include "API/OpenGL/GLTextureManager.h"

namespace tartarus {

bool GLTexture2D::Init(AssetName name, GLTextureManager* managerPtr){
    GL_CHECK_CALL(glGenTextures(1, &_textureId));
    _assetName = name;
    _manager = managerPtr;
    return true;
}

bool GLTexture2D::Exit(){
    GL_CHECK_CALL(glDeleteTextures(1, &_textureId))
    return true;
}

void GLTexture2D::BindTexture(){
    GL_CHECK_CALL(glActiveTexture(GL_TEXTURE0+_attachIndex))
    GL_CHECK_CALL(glBindTexture(GL_TEXTURE_2D, _textureId))
}

void GLTexture2D::UnbindTexture(){
    GL_CHECK_CALL(glBindTexture(GL_TEXTURE_2D, 0))
}

uint GLTexture2D::ConfirmAttachment(){
    auto index = _manager->ConfirmAttachment(this);
    if(index==-1)
        return index;
    _attachIndex = index;
    return index;
}

void GLTexture2D::SetTextureMetadata(RawImage* data, uint target){
    _texArgs._imageData = data;
    _texArgs._target = target;

    if(data->_nrChannels == 3)
        _texArgs._format = GL_RGB;
    else if(data->_nrChannels == 4)
        _texArgs._format = GL_RGBA;
    else
        SCREAM("Implement correct format recognition");

    _height = _texArgs._imageData->_height;
    _width = _texArgs._imageData->_width;
    _nrChannels = _texArgs._imageData->_nrChannels;
}

void GLTexture2D::LoadImage(){
    this->BindTexture();

    GL_CHECK_CALL(glTextureParameteri(_textureId, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE))
    GL_CHECK_CALL(glTextureParameteri(_textureId, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE))
    GL_CHECK_CALL(glTextureParameteri(_textureId, GL_TEXTURE_MIN_FILTER, GL_NEAREST))
    GL_CHECK_CALL(glTextureParameteri(_textureId, GL_TEXTURE_MAG_FILTER, GL_NEAREST))

    GL_CHECK_CALL(glTexImage2D(
        _texArgs._target,
        0,
        _texArgs._format,
        _texArgs._imageData->_width,
        _texArgs._imageData->_height,
        0,
        _texArgs._format,
        GL_UNSIGNED_BYTE,
        _texArgs._imageData->_data
    ))
    GL_CHECK_CALL(glGenerateMipmap(_texArgs._target))

    this->UnbindTexture();

    // TODO: probably fix this when i implement changing levels
    _texArgs._imageData = nullptr;
}


}