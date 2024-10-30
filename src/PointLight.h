#pragma once

#include "glm.hpp"

struct PointLight
{

    glm::vec3 position;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    float constant;
    float linear;
    float quadratic;

    PointLight(
        glm::vec3 position, glm::vec3 ambient,
        glm::vec3 diffuse, glm::vec3 specular,
        float constant = 1.0f,
        float linear = 0.09f,
        float quadratic = 0.035f
    )
        : position(position), ambient(ambient),
        diffuse(diffuse), specular(specular),
        constant(constant), linear(linear), quadratic(quadratic)
    {}

    PointLight()
        : position(0.0f), ambient(0.2f),
        diffuse(0.5f), specular(1.0f),
        constant(1.0f), linear(0.09f), quadratic(0.035f)
    {}

};