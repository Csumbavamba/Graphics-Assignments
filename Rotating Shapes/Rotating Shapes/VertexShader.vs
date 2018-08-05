#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;

out vec3 fragColor;
out vec2 fragTexCoord;

uniform float currentTime;

void main(void)
{

	
	if (color.g == 1.0f && color.b == 1.0f && color.r == 0)
	{
		vec3 scaledSizePosition = position * 0.5;
		float movedX = scaledSizePosition.x - (sin(currentTime) / 2);
		float movedY = scaledSizePosition.y - (cos(currentTime) / 2);
		gl_Position = vec4(movedX, movedY, 0, 1.0);
	}
	else
	{
		vec3 scaledSizePosition = position * 0.25;
		scaledSizePosition.x = scaledSizePosition.x + (sin(currentTime) / 2);
		scaledSizePosition.y = scaledSizePosition.y + (cos(currentTime) / 2);
		gl_Position = vec4(scaledSizePosition, 1.0);
	}
	

	fragColor = color;
	fragTexCoord = texCoord;
}