#version 330 core

in vec2 a_textureCoord;
in vec3 a_normal;
out vec4 f_color;

uniform sampler2D u_texture;

void main(){
	f_color = vec4(a_normal + 0.5f, 1.0f);
}
