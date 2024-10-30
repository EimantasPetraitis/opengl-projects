#version 460 core

struct Material
{

    sampler2D diffuseMap;
    sampler2D specularMap;
    sampler2D emissionMap;
    float shininess;
    float emissionIntensity;

};

struct PointLight
{

    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;

};

struct DirectionalLight
{

    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

};

vec3 CalculateDirectionalLight(
    DirectionalLight light, vec3 normal, vec3 viewDirection
);

vec3 CalculatePointLight(
    PointLight light, vec3 normal,
    vec3 fragmentPosition, vec3 viewDirection
);


#define NUM_POINT_LIGHTS 3

layout(location = 0) out vec4 o_Color;

in vec3 v_Normal;
in vec3 v_FragmentPosition;
in vec2 v_TextureCoordinates;

uniform Material u_Material;
uniform PointLight u_PointLights[NUM_POINT_LIGHTS];
uniform DirectionalLight u_DirectionalLight;

uniform vec3 u_ViewerPosition;

void main()
{

    vec3 result = vec3(0.0);

    vec3 normal = normalize(v_Normal);
    vec3 viewDirection = normalize(
        u_ViewerPosition - v_FragmentPosition
    );

    result += CalculateDirectionalLight(
        u_DirectionalLight, normal, viewDirection
    );

    // Other lights

    for (int i = 0; i < NUM_POINT_LIGHTS; i++)
    {
        result += CalculatePointLight(
            u_PointLights[i], normal, v_FragmentPosition, viewDirection
        );
    }

    vec3 emissionLight = vec3(0.0);

    if (u_Material.emissionIntensity > 0.0)
    {

        emissionLight
            = u_Material.emissionIntensity
            * vec3(
                texture(u_Material.emissionMap, v_TextureCoordinates)
            );

    }

    result += emissionLight;
    o_Color = vec4(result, 1.0);

}

vec3 CalculateDirectionalLight(
    DirectionalLight light, vec3 normal, vec3 viewDirection
)
{

    vec3 lightDirection = normalize(-light.direction);

    vec3 diffuseMapValue = vec3(texture(u_Material.diffuseMap, v_TextureCoordinates));
    
    // Ambient
    vec3 ambientLight = diffuseMapValue * light.ambient;

    // Diffuse
    float diffuse = max(dot(normal, lightDirection), 0.0);
    vec3 diffuseLight
        = diffuse * diffuseMapValue
        * light.diffuse;

    // Specular
    vec3 reflectionDirection = reflect(-lightDirection, normal);
    float specular = pow(
        max(dot(viewDirection, reflectionDirection), 0.0),
        u_Material.shininess
    );
    vec3 specularLight
        = specular * light.specular
        * vec3(texture(u_Material.specularMap, v_TextureCoordinates));

    return (diffuseLight + specularLight);

}

vec3 CalculatePointLight(
    PointLight light, vec3 normal,
    vec3 fragmentPosition, vec3 viewDirection
)
{

    vec3 lightDirection = normalize(
        light.position - fragmentPosition
    );

    vec3 diffuseMapValue = vec3(
        texture(u_Material.diffuseMap, v_TextureCoordinates)
    );

    // Attenuation
    float distance = length(light.position - v_FragmentPosition);
    float attenuation = 1.0 / (
        light.constant + light.linear * distance
        + light.quadratic * distance * distance
    );
    
    // Ambient
    vec3 ambientLight = diffuseMapValue * light.ambient;

    // Diffuse
    float diffuse = max(dot(normal, lightDirection), 0.0);
    vec3 diffuseLight = diffuse * diffuseMapValue * light.diffuse;

    // Specular
    vec3 reflectionDirection = reflect(-lightDirection, normal);
    float specular = pow(
        max(dot(viewDirection, reflectionDirection), 0.0),
        u_Material.shininess
    );
    vec3 specularLight
        = specular * light.specular
        * vec3(texture(u_Material.specularMap, v_TextureCoordinates));

    return (ambientLight + diffuseLight + specularLight) * attenuation;

}