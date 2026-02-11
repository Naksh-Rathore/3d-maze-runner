#version 330 core

in vec2 TexCoord;
in vec3 Normal;

out vec4 FragColor;

uniform sampler2D texture1;

void main()
{
    FragColor = texture(texture1, TexCoord);
}
