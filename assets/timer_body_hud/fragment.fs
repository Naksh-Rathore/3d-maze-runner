#version 330 core

in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D texture1;

uniform float timerRatio;

void main()
{
    if (TexCoord.x < timerRatio)
        FragColor = texture(texture1, TexCoord);
    else
        FragColor = vec4(0.0f);
}
