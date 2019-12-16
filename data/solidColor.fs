#version 130

uniform vec3 color; 
uniform vec3 lightPos;

out vec4 fragColor; 

void main() 
{ 
    fragColor = vec4(color, 1);
}