#version 330 core

in vec4 fragColor;
in vec2 fragEdges;

uniform vec4 defaultColor;

out vec4 color;

void main()
{
	vec2 coord = gl_PointCoord - vec2(0.5f);
	color = fragColor * smoothstep(0.5f, (fragEdges.x / fragEdges.y) *  0.4999f, length(coord));
}