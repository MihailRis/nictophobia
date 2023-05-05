#version 330 core

in vec2 a_textureCoord;
in vec3 a_normal;
out vec4 f_color;

uniform sampler2D u_texture;

void main(){
	f_color = vec4(a_normal+0.2, 1.0);//texture(u_texture, a_textureCoord) * vec4(a_normal, 1.0);
}
