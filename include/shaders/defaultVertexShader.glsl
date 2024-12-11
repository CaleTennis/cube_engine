#version 330 core

layout (location = 0) in vec3 aPos;		// position variable

out vec3 vertexColor; // output to fragment shader

uniform mat4 MVP;

void main()
{
	gl_Position = MVP * vec4(aPos, 1.0f);
	vertexColor = aPos;
}