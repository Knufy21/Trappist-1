#version 330 core

layout(location = 0) in vec2 vertPosition;
layout(location = 1) in vec4 vertColor;
layout(location = 2) in vec2 vertEdges;

out vec4 fragColor;
out vec2 fragEdges;

void main()
{
	gl_PointSize = vertEdges.y;
	gl_Position = vec4(vertPosition.x, vertPosition.y, 0.0f, 1.0f);
	fragColor = vertColor;
	fragEdges = vertEdges;
}