#version 460 core

layout(location = 0) in vec4 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TextureCoord;
layout(location = 3) in float a_TextureIndex;

uniform mat4 u_MVPMatrix;

out vec4 v_Color;
out vec2 v_TextureCoordinates;
out float v_TextureIndex;

void main()
{

    v_Color = a_Color;
    v_TextureCoordinates = a_TextureCoord;
    v_TextureIndex = a_TextureIndex;

    gl_Position = u_MVPMatrix * a_Position;

}