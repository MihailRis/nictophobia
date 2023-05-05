#version 330 core

layout (location = 0) in vec3 v_position;
layout (location = 1) in vec2 v_textureCoord;
layout (location = 2) in vec3 v_normal;

out vec2 a_textureCoord;
out vec3 a_normal;

uniform mat4 u_proj;
uniform mat4 u_view;
uniform mat4 u_model;

void main(){
	a_textureCoord = v_textureCoord;
	a_normal = v_normal;
	gl_Position = u_proj * u_view * u_model * vec4(v_position, 1.0);
}
