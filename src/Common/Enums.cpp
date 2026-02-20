#include "Common/Enums.h"

namespace tartarus {

const char* GetBufferName(BufferName id){
    switch((BufferName)id){
        case BufferName::kRectangleColor:
            return "RectangleColor";
        case BufferName::kRectangleTexture:
            return "RectangleTexture";
        case BufferName::kRectangleTextureNormInstanced:
            return "RectangleTextureNorm";
        case BufferName::kTriangleColor:
            return "TriangleColor";
        case BufferName::kTriangleTexture:
            return "TriangleTexture";
        case BufferName::kTriangleTextureNorm:
            return "TriangleTextureNorm";
        case BufferName::kCubeTexture:
            return "CubeTexture";
        case BufferName::kCubeTextureNorm:
            return "CubeTextureNorm";
    }
    return "Check Enums.cpp";
}

const char* GetShaderName(ShaderName id){
    switch(id){
        case ShaderName::kDefault:
            return "Default";
        case ShaderName::kPointLight:
            return "PointLight";
        case ShaderName::kInstanced:
            return "Instanced";
    }
    return "Check Enums.cpp";
}

const char* GetAssetPathName(AssetName id){
    switch(id){
        case AssetName::kFloor_0:
            return "../../assets/Tartarus/Floor_0.png";
            break;
        case AssetName::kWall_0:
            return "../../assets/Tartarus/Wall_0.png";
            break;
        case AssetName::kLowWall_0:
            return "../../assets/Tartarus/LowWall_0.png";
            break;
        case AssetName::kBlood_0:
            return "../../assets/Tartarus/Blood_0.png";
            break;
        case AssetName::kBarrel_0:
            return "../../assets/Tartarus/Barrel_0.png";
            break;
        case AssetName::kBarrelSpecular_0:
            return "../../assets/Tartarus/BarrelSpecular_0.png";
            break;
        case AssetName::kMonster_0:
            return "../../assets/Tartarus/monster_0.png";
            break;
        case AssetName::kCount:
            return "../../assets/vibe_cat.png";
            break;        
    }
    return "../../assets/vibe_cat.png";
}

}