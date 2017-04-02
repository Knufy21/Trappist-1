#version 330 core

layout(location = 0) in vec2 vertPosition;
layout(location = 1) in vec4 vertColor;
layout(location = 2) in vec2 vertTexCoord;
layout(location = 3) in float vertTextureID;

out vec2 fragPosition;
out vec4 fragColor;
out vec2 fragTexCoord;
out float fragTextureID;

void main()
{
	//while(true){}
	gl_Position = vec4(vertPosition.xy, 0.0f, 1.0f);
	fragPosition = vertPosition;
	fragColor = vertColor;
	fragTexCoord = vertTexCoord;
	fragTextureID = vertTextureID;
}