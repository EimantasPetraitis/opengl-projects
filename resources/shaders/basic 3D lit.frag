#version 460 core

struct Material
{

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;

};

struct Light
{

    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

};

layout(location = 0) out vec4 o_Color;

in vec3 v_Normal;
in vec3 v_FragmentPosition;

uniform Material u_Material;
uniform Light u_Light;

uniform vec3 u_ViewerPosition;

void main()
{

    vec3 ambientLight = u_Material.ambient * u_Light.ambient;

    vec3 normal = normalize(v_Normal);
    vec3 lightDirection = normalize(
        u_Light.position - v_FragmentPosition
    );
    float diffuse = max(dot(normal, lightDirection), 0.0);
    vec3 diffuseLight
        = diffuse * u_Material.diffuse * u_Light.diffuse;

    vec3 viewDirection = normalize(
        u_ViewerPosition - v_FragmentPosition
    );
    vec3 reflectionDirection = reflect(-lightDirection, normal);
    float specular = pow(
        max(dot(viewDirection, reflectionDirection), 0.0),
        u_Material.shininess
    );
    vec3 specularLight = specular * u_Material.specular * u_Light.specular;
        
    vec3 finalColor = ambientLight + diffuseLight + specularLight;
    o_Color = vec4(finalColor, 1.0);

}