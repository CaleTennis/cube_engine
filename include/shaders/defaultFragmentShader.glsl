#version 330 core

in vec3 vertexColor;	// input from vertex shader
out vec4 FragColor;		// output color

void main()
{
	FragColor = vec4(vertexColor, 1.0f);
}