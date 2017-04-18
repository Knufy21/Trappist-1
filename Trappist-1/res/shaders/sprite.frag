#version 330 core

in vec2 fragPosition;
in vec4 fragColor;
in vec2 fragTexCoord;
in float fragTextureID;

out vec4 color;

uniform sampler2D textures[32]; // glActiveTexture 0 .. 31
//uniform sampler2D textures2[32]
//{
//	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31
//};

uniform sampler2D lightMap;
uniform int useLightMap;

void main()
{
	if(fragTextureID == 0.0f)
		color = fragColor;
	else
		color = fragColor * texture(textures[int(fragTextureID)], fragTexCoord);

	if(color.a == 0.0f)
		discard;

if(useLightMap > 0)
{
		vec2 lightMapCoord = (fragPosition + 1.0f) * 0.5f;
		color = color * texture(lightMap, lightMapCoord);
}
}