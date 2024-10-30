#pragma once

#include "glm.hpp"

struct DirectionalLight
{

    glm::vec3 direction;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    DirectionalLight(
        glm::vec3 direction, glm::vec3 ambient,
        glm::vec3 diffuse, glm::vec3 specular
    )
        : direction(direction), ambient(ambient),
        diffuse(diffuse), specular(specular)
    {}

    DirectionalLight()
        : direction(0.0f, -1.0f, 0.0f), ambient(0.2f),
        diffuse(0.5f), specular(1.0f)
    {}

};