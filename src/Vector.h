#pragma once

#include <glm.hpp>

struct Vector2
{

    float x, y;
    
    glm::vec2 GLMVector();

    float SquareMagnitude();
    float Magnitude();

    void Normalize();

};

struct Vector3
{

    float x, y, z;

    glm::vec3 GLMVector();

    float SquareMagnitude();
    float Magnitude();

    void Normalize();

};

struct Vector4
{

    float x, y, z, w;

    glm::vec4 GLMVector();

    float SquareMagnitude();
    float Magnitude();

    void Normalize();

};