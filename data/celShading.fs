#version 130

uniform vec3 lightPos;	//world light position
uniform vec3 cameraPos;	//camera position
uniform vec3 color;		//color

in vec3 normal;		//normal
in vec4 worldPos;	//world position

out vec4 fragColor;

//adapted from https://github.com/mchamberlain/Cel-Shader/blob/master/shaders/celShader.frag

void main()
{
	vec4 worldPosR = worldPos / worldPos.w;

	vec3 n = normalize(normal);
	vec3 l = normalize(lightPos - worldPosR.xyz);
	vec3 r = normalize(reflect(-l, n));
	vec3 v = normalize(cameraPos - worldPosR.xyz);

	float intensity = 0;
	float shininess = 25;

	float diffuse = dot(normalize(n), normalize(l));
	if(diffuse>0)
	{
		intensity += diffuse;
		
		float specular = pow(dot(normalize(cameraPos-worldPosR.xyz), reflect(normalize(-l),normalize(n))), shininess);
		//float specular = dot(normalize(cameraPos-worldPosR.xyz), reflect(normalize(-l),normalize(n)));
		if(specular>0)
		{
			intensity += specular;
		}
	}

	intensity = pow(intensity, 0.2);

	if (intensity > 0.8) {
 		intensity = 1.1;
	}
	else if (intensity > 0.4) {
 		intensity = 0.8;
	}
	else if (intensity > 0.2) {
 		intensity = 0.5;
	}
	else {
 		intensity = 0.1;
	}


	fragColor.r = color.r * intensity;
	fragColor.g = color.g * intensity;
	fragColor.b = color.b * intensity;
} 