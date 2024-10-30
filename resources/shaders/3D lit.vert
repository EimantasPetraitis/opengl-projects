#version 460 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TextureCoordinates;
layout(location = 2) in vec3 a_Normal;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;
uniform mat3 u_NormalMatrix;

out vec3 v_FragmentPosition;
out vec3 v_Normal;
out vec2 v_TextureCoordinates;

void main()
{

    // mat3 normalMatrix = mat3(transpose(inverse(u_Model)));
    
    v_FragmentPosition = vec3(u_Model * vec4(a_Position, 1.0));
    v_Normal = u_NormalMatrix * a_Normal;
    v_TextureCoordinates = a_TextureCoordinates;
    
    gl_Position = u_Projection * u_View * u_Model * vec4(a_Position, 1.0);

}