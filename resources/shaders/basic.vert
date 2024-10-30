#version 440 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 textureCoord;

out vec2 v_textureCoordinates;

uniform mat4 u_MVPMatrix;

void main()
{

    gl_Position = u_MVPMatrix * position;
    v_textureCoordinates = textureCoord;
    
};