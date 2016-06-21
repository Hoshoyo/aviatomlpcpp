#version 330 core

out vec4 fColor;

in vec2 uvCoords;
in vec3 normal;

uniform sampler2D textSampler;

void main()
{
	//fColor = vec4(1,0,0,1);
	vec3 lightDirection = vec3(1, 1, 1);
	vec4 surfaceColor = texture(textSampler, uvCoords);
	
	float cosAngle = dot(normalize(normal), normalize(lightDirection));
	vec3 diffuse = max(cosAngle * vec3(1,1,1), 0.2);
	fColor = surfaceColor * vec4(diffuse, 1.0);
}