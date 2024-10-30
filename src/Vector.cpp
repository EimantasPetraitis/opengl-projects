#include "Vector.h"

#include <cmath>

glm::vec2 Vector2::GLMVector()
{
    return glm::vec2(x, y);
}

float Vector2::SquareMagnitude()
{
    return pow(x, 2.0f) + pow(y, 2.0f);
}

float Vector2::Magnitude()
{
    return sqrt(SquareMagnitude());
}

void Vector2::Normalize()
{
    float magnitude = Magnitude();
    x /= magnitude;
    y /= magnitude;
}

glm::vec3 Vector3::GLMVector()
{
    return glm::vec3(x, y, z);
}

float Vector3::SquareMagnitude()
{
    return pow(x, 2.0f) + pow(y, 2.0f) + pow(z, 2.0f);
}

float Vector3::Magnitude()
{
    return sqrt(SquareMagnitude());
}

void Vector3::Normalize()
{
    float magnitude = Magnitude();
    x /= magnitude;
    y /= magnitude;
    z /= magnitude;
}

glm::vec4 Vector4::GLMVector()
{
    return glm::vec4(x, y, z, w);
}

float Vector4::SquareMagnitude()
{
    return pow(x, 2.0f) + pow(y, 2.0f)
        + pow(z, 2.0f) + pow(w, 2.0f);
}

float Vector4::Magnitude()
{
    return sqrt(SquareMagnitude());
}

void Vector4::Normalize()
{
    float magnitude = Magnitude();
    x /= magnitude;
    y /= magnitude;
    z /= magnitude;
    w /= magnitude;
}