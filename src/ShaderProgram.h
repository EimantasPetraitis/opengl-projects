#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <unordered_map>

#include <GL/glew.h>
#include <glm.hpp>

#include "MaterialPlain.h"
#include "Material.h"
#include "PointLight.h"
#include "DirectionalLight.h"

class ShaderProgram
{

private:

    unsigned int id;

    std::string vertexShaderFilePath;
    std::string fragmentShaderFilePath;

    std::unordered_map<std::string, int> uniformLocationCache;

public:

    ShaderProgram(
        const std::string& vertexShaderPath,
        const std::string& fragmentShaderPath
    );
    ShaderProgram() = default;

    ~ShaderProgram();

    void Bind() const;
    void Unbind() const;

    void SetUniform1Int(const std::string& name, int value);
    void SetUniform1Float(const std::string& name, float value);

    void SetUniform3Floats(
        const std::string& name,
        float v0, float v1, float v2
    );
    void SetUniform3Floats(
        const std::string& name, glm::vec3 v
    );

    void SetUniform4Floats(
        const std::string& name,
        float v0, float v1, float v2, float v3
    );
    void SetUniform4Floats(
        const std::string& name, glm::vec4 v
    );

    void SetUniformMatrix3Floats(
        const std::string& name, glm::mat3& matrix
    );
    void SetUniformMatrix4Floats(
        const std::string& name, glm::mat4& matrix
    );

    void SetUniform1IntArray(
        const std::string& name, int count, int* array
    );

    void SetUniformMaterialPlain(
        const std::string& name, MaterialPlain& material
    );
    void SetUniformMaterial(
        const std::string& name, Material& material,
        int diffuseMapSlot, int specularMapSlot,
        int emissionMapSlot = -1
    );

    void SetUniformPointLight(
        const std::string& name, PointLight& light,
        bool setAttenuationParameters = true
    );
    void SetUniformDirectionalLight(
        const std::string& name, DirectionalLight& light
    );

private:

    int GetUniformLocation(const std::string& name);
    
    static std::string ReadFile(const std::string& path);
    
    static unsigned int CompileShader(
        unsigned int type, const std::string& source
    );

    static unsigned int CreateShaderProgram(
        const std::string& vertexShader, const std::string& fragmentShader
    );

};