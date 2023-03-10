#version 460 core

layout(location = 0) in varyings
{
	vec3 position;
	vec3 normal;
	vec2 uv;
} VS_IN;

out vec4 frag_color;

void main()
{
	frag_color = vec4(VS_IN.uv, 0.0, 1.0);
}
