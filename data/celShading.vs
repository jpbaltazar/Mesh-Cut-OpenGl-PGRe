#version 140

in vec3 pos;
in vec3 n;

uniform mat4 vp;
uniform mat4 m;

out vec3 normal;
out vec4 worldPos;
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

void main() 
{ 
	gl_Position = vp*m*vec4(pos, 1);

	//TODO1 pass on some transformad vectors to fragment shader
	//when transforming normal, the weight should be set to 0 when
	//transforming it with a 4x4 matrix, otherwise it will also translate
	//our directions, which is unwanted
    //Also, normal vector has to be transformed by inversed transpose of model matrix, due to scaling

	normal = normalize(inverse(transpose(m))*vec4(n, 0.0f)).xyz;
	worldPos = m*vec4(pos, 1.0f);

}