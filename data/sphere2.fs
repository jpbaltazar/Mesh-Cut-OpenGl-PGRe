#version 130

uniform float animationTime;

out vec4 fragColor;

void main()
{
    //TODO 4 
    // Animate the sphere color based on the animation time
    //use functions like the absolute value of sin and cos with, combined with animationTime
    fragColor = vec4(abs(sin(sin(animationTime)*(2*3.14))), abs(sin(cos(animationTime)*(2*3.14))), 1, 1); 
	//fragColor = vec4(0, 0, 1, 1);
}