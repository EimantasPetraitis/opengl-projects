#version 440 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TextureCoord;
layout(location = 3) in float a_TextureIndex;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

out vec4 v_Color;
out vec2 v_TextureCoordinates;
out float v_TextureIndex;

void main()
{

    v_Color = a_Color;
    v_TextureCoordinates = a_TextureCoord;
    v_TextureIndex = a_TextureIndex;

    gl_Position = u_Projection * u_View * u_Model * vec4(a_Position, 1.0);

}