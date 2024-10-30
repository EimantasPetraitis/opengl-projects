#version 440 core

layout(location = 0) out vec4 color;

in vec2 v_textureCoordinates;

uniform sampler2D u_Texture;

void main()
{

    vec4 textureColor = texture(u_Texture, v_textureCoordinates);
    color = textureColor;

};