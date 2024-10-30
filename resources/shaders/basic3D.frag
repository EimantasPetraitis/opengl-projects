#version 460 core

layout(location = 0) out vec4 o_Color;

in vec4 v_Color;
in vec2 v_TextureCoordinates;
in float v_TextureIndex;

uniform sampler2D u_Texture;

void main()
{

    int index = int(v_TextureIndex);
    vec4 textureColor;

    if (index == -1)
        textureColor = v_Color;
    else
        textureColor = texture(u_Texture, v_TextureCoordinates);
        
    o_Color = textureColor;

}