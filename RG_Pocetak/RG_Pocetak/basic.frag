#version 330 core 


in vec4 channelCol; 
out vec4 outCol;

uniform sampler2D uTex; 

void main() //Glavna funkcija sejdera
{
	outCol = channelCol;

}