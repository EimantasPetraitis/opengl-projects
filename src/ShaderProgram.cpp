#include "ShaderProgram.h"

#include "gtc/type_ptr.hpp"

ShaderProgram::ShaderProgram(
    const std::string& vertexShaderPath,
    const std::string& fragmentShaderPath
)
    : id(0),
    vertexShaderFilePath(vertexShaderPath),
    fragmentShaderFilePath(fragmentShaderPath)
{

    auto vertexShader = ReadFile(vertexShaderFilePath);
    auto fragmentShader = ReadFile(fragmentShaderFilePath);
    
    id = CreateShaderProgram(vertexShader, fragmentShader);

}

ShaderProgram::~ShaderProgram()
{

    glDeleteProgram(id);

}

void ShaderProgram::Bind() const
{

    glUseProgram(id);

}

void ShaderProgram::Unbind() const
{

    glUseProgram(0);

}

void ShaderProgram::SetUniform1Int(
    const std::string& name, int value
)
{

    glUniform1i(GetUniformLocation(name), value);

}

void ShaderProgram::SetUniform1Float(
    const std::string& name, float value
)
{

    glUniform1f(GetUniformLocation(name), value);

}

void ShaderProgram::SetUniform3Floats(
    const std::string& name,
    float v0, float v1, float v2
)
{

    glUniform3f(GetUniformLocation(name), v0, v1, v2);

}

void ShaderProgram::SetUniform3Floats(const std::string &name, glm::vec3 v)
{

    glUniform3f(
        GetUniformLocation(name), v.x, v.y, v.z
    );

}

void ShaderProgram::SetUniform4Floats(
    const std::string& name,
    float v0, float v1, float v2, float v3
)
{

    glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);

}

void ShaderProgram::SetUniform4Floats(const std::string &name, glm::vec4 v)
{

    glUniform4f(
        GetUniformLocation(name), v.x, v.y, v.z, v.w
    );

}

void ShaderProgram::SetUniformMatrix3Floats(
    const std::string& name, glm::mat3& matrix
)
{

    glUniformMatrix3fv(
        GetUniformLocation(name), 1, GL_FALSE,
        glm::value_ptr(matrix)
    );

}

void ShaderProgram::SetUniformMatrix4Floats(
    const std::string& name, glm::mat4& matrix
)
{

    glUniformMatrix4fv(
        GetUniformLocation(name), 1, GL_FALSE,
        glm::value_ptr(matrix)
    );

}

void ShaderProgram::SetUniform1IntArray(
    const std::string& name, int count, int* array
)
{

    glUniform1iv(GetUniformLocation(name), count, array);

}

void ShaderProgram::SetUniformMaterialPlain(
    const std::string &name, MaterialPlain &material
)
{

    SetUniform3Floats(
        name + ".ambient", material.ambient
    );
    SetUniform3Floats(
        name + ".diffuse", material.diffuse
    );
    SetUniform3Floats(
        name + ".specular", material.specular
    );
    SetUniform1Float(
        name + ".shininess", material.shininess
    );

}

void ShaderProgram::SetUniformMaterial(
    const std::string &name, Material &material,
    int diffuseMapSlot, int specularMapSlot,
    int emissionMapSlot /* = -1*/
)
{

    SetUniform1Int(
        name + ".diffuseMap", diffuseMapSlot
    );
    material.diffuseMap->Bind(diffuseMapSlot);

    SetUniform1Int(
        name + ".specularMap", specularMapSlot
    );
    material.specularMap->Bind(specularMapSlot);

    SetUniform1Float(
        name + ".shininess", material.shininess
    );
    SetUniform1Float(
        name + ".emissionIntensity", material.emissionIntensity
    );

    if (emissionMapSlot >= 0)
    {
        SetUniform1Int(
            name + ".emissionMap", emissionMapSlot
        );
        material.emissionMap->Bind(emissionMapSlot);
    }

}

void ShaderProgram::SetUniformPointLight(
    const std::string &name, PointLight &light,
    bool setAttenuationParameters /* = true */
)
{

    SetUniform3Floats(
        name + ".ambient", light.ambient
    );
    SetUniform3Floats(
        name + ".diffuse", light.diffuse
    );
    SetUniform3Floats(
        name + ".specular", light.specular
    );
    SetUniform3Floats(
        name + ".position", light.position
    );

    if (setAttenuationParameters)
    {

        SetUniform1Float(
            name + ".constant", light.constant
        );
        SetUniform1Float(
            name + ".linear", light.linear
        );
        SetUniform1Float(
            name + ".quadratic", light.quadratic
        );
    
    }

}

void ShaderProgram::SetUniformDirectionalLight(
    const std::string &name, DirectionalLight &light
)
{

    SetUniform3Floats(
        name + ".ambient", light.ambient
    );
    SetUniform3Floats(
        name + ".diffuse", light.diffuse
    );
    SetUniform3Floats(
        name + ".specular", light.specular
    );
    SetUniform3Floats(
        name + ".direction", light.direction
    );

}

int ShaderProgram::GetUniformLocation(const std::string& name)
{

    if (uniformLocationCache.find(name) != uniformLocationCache.end())
        return uniformLocationCache[name];

    int location = glGetUniformLocation(id, name.c_str());

    if (location == -1)
        std::cout << "Warning: uniform '" << name << "' does not exist.\n";

    uniformLocationCache[name] = location;
    return location;

}

std::string ShaderProgram::ReadFile(const std::string& path)
{

    std::ifstream fileStream(path);
    std::ostringstream stringStream;
    stringStream << fileStream.rdbuf();
    return stringStream.str();

}

unsigned int ShaderProgram::CompileShader(
    unsigned int type, const std::string& source
)
{

    unsigned int shaderID = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(shaderID, 1, &src, nullptr);
    glCompileShader(shaderID);

    // Error handling
    
    int compilationResult;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compilationResult);

    if (compilationResult == GL_FALSE)
    {

        int messageLenght;
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &messageLenght);
        char* message = (char*)alloca(messageLenght * sizeof(char));
        glGetShaderInfoLog(shaderID, messageLenght, &messageLenght, message);

        std::string shaderTypeString;
        if (type == GL_VERTEX_SHADER)
            shaderTypeString = "vertex";
        else if (type == GL_FRAGMENT_SHADER)
            shaderTypeString = "fragment";
        else
            shaderTypeString = "unknown type";
        
        std::cout << "Error: Failed to compile " << shaderTypeString << " shader.\n";
        std::cout << message << "\n";

        glDeleteShader(shaderID);
        return 0;

    }

    return shaderID;

}

unsigned int ShaderProgram::CreateShaderProgram(
    const std::string& vertexShader, const std::string& fragmentShader
)
{

    unsigned int programID = glCreateProgram();
    unsigned int vertexShaderID = CompileShader(
        GL_VERTEX_SHADER, vertexShader
    );
    unsigned int fragmentShaderID = CompileShader(
        GL_FRAGMENT_SHADER, fragmentShader
    );

    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, fragmentShaderID);
    glLinkProgram(programID);

    glValidateProgram(programID);

    int validationResult;
    glGetProgramiv(programID, GL_VALIDATE_STATUS, &validationResult);

    if (validationResult == GL_FALSE)
    {

        int messageLenght;
        glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &messageLenght);
        char* message = (char*)alloca(messageLenght * sizeof(char));
        glGetProgramInfoLog(programID, messageLenght, &messageLenght, message);

        std::cout << "Error: Failed to validate program.\n";
        std::cout << message << "\n";

        glDeleteProgram(programID);
        return 0;

    }

    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);

    return programID;

}