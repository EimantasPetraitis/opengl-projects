#pragma once

#include "glm.hpp"

struct MaterialPlain
{

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;

    MaterialPlain(
        glm::vec3 ambient, glm::vec3 diffuse,
        glm::vec3 specular, float shininess
    )
        : ambient(ambient), diffuse(diffuse),
        specular(specular), shininess(shininess)
    {}

    MaterialPlain()
        : ambient(0.2f), diffuse(0.5f),
        specular(1.0f), shininess(32.0f)
    {}

};