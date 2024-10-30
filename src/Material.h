#pragma once

#include "glm.hpp"

#include "Texture.h"

struct Material
{

    Texture* diffuseMap;
    Texture* specularMap;
    float shininess;
    Texture* emissionMap;
    float emissionIntensity;

    Material(
        Texture* diffuseMap, Texture* specularMap,
        float shininess, Texture* emissionMap = nullptr,
        float emissionIntensity = 0.0f
    )
        : diffuseMap(diffuseMap), specularMap(specularMap),
        shininess(shininess), emissionMap(emissionMap),
        emissionIntensity(emissionIntensity)
    {}

    Material()
        : diffuseMap(nullptr), specularMap(nullptr),
        shininess(64.0f), emissionMap(nullptr),
        emissionIntensity(0.0f)
    {}

};