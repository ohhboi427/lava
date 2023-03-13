#version 460 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec3 a_normal;
layout(location = 2) in vec2 a_uv;

out varyings
{
	vec3 position;
	vec3 normal;
	vec2 uv;
} VS_OUT;

void main()
{
	VS_OUT.position = a_position;
	VS_OUT.normal = a_normal;
	VS_OUT.uv= a_uv;
	gl_Position = vec4(a_position, 1.0);
}
