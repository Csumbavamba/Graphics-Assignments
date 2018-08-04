#version 450 core

in vec2 fragTexCoord;
in vec3 fragColor;

out vec4 color;

uniform float currentTime;

uniform sampler2D tex;
uniform sampler2D tex2;

void main (void)
{
    if (fragColor.g == 1.0f)
    {
        color = mix(texture(tex, fragTexCoord), texture(tex2, fragTexCoord), abs(sin(currentTime)));
    }
    else
    {
        vec3 colorTemp = fragColor * (abs(sin(currentTime)) + 1) / 2;
        color = vec4(colorTemp, 1.0f);
    }
   //  color = vec4(colorTemp, 1.0f);
}