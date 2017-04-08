#version 330 core

layout(location = 0) in vec2 vertPosition;
layout(location = 1) in vec4 vertColor;
layout(location = 2) in vec2 vertTexCoord;
layout(location = 3) in float vertTextureID;
layout(location = 4) in float depth;

out vec2 fragPosition;
out vec4 fragColor;
out vec2 fragTexCoord;
out float fragTextureID;

void main()
{
	gl_Position = vec4(vertPosition.xy, depth, 1.0f);
	fragPosition = vertPosition;
	fragColor = vertColor;
	fragTexCoord = vertTexCoord;
	fragTextureID = vertTextureID;
}