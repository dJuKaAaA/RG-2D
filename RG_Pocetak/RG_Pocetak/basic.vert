#version 330 core 


layout(location = 0) in vec2 inPos; 
layout(location = 1) in vec4 inCol; 
uniform vec2 uPos;
out vec4 channelCol;
uniform vec4 colUniform;

void main() 
{
	gl_Position = vec4(inPos + uPos, 0.0, 1.0);
	channelCol = colUniform;
}