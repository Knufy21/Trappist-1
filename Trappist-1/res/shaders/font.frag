#version 330 core

in vec2 fragPosition;
in vec4 fragColor;
in vec2 fragTexCoord;
in float fragTextureID;

out vec4 rcolor;

uniform sampler2D textures[32];

uniform float thickness;
uniform float edge;
uniform vec4 color;

uniform float outlineThickness;
uniform float outlineEdge;
uniform vec4 outlineColor;
uniform vec2 outlineOffset;

void main()
{
	// Thickness of the character (by default 0.5f, with adjustments)
	float characterThickness = 0.5f - thickness;

	// Thickness of the outline
	float outlineThickness = characterThickness - outlineThickness;

	// Letter distance
	float dist = texture(textures[int(fragTextureID)], fragTexCoord).a;

	// Outline distance
	float dist2 = texture(textures[int(fragTextureID)], fragTexCoord + outlineOffset).a;

	// Letter alpha
    //float alpha = smoothstep(characterThickness - edge, characterThickness + edge, dist);
	float alpha = smoothstep(characterThickness, characterThickness, dist);

	// Outline alpha
	//float alpha2 = smoothstep(outlineThickness - outlineEdge, outlineThickness + outlineEdge, dist);
	float alpha2 = smoothstep(outlineThickness, outlineThickness, dist);

	float overallAlpha = alpha + (1.0f - alpha) * alpha2;
	vec4 overallColor = mix(outlineColor, color, alpha / alpha2);

	// Real line of code
	rcolor = vec4(overallColor.rgb, overallAlpha * overallColor.a);

	// Testing
	//float a = overallAlpha * overallColor.a;
	//if(a < 1.0f)
	//	rcolor = vec4(1.0f, 1.0f, 0.0f, 0.0f);
	//else
	//	
	//	rcolor = vec4(overallColor.rgb, a);
}