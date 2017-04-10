#version 330 core

in vec4 fragColor;
in vec2 fragEdges;

out vec4 color;

void main()
{
	vec2 coord = gl_PointCoord - vec2(0.5f);
	float a = smoothstep(0.5f, (fragEdges.x / fragEdges.y) *  0.4999f, length(coord));
	color = fragColor;
	color.a *= a;
}