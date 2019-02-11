attribute vec3 a_posL;
attribute vec2 a_uv;
attribute vec2 a_uv_blend;

attribute vec3 a_norm;//

uniform mat4 u_mr;
uniform vec3 u_height;

uniform sampler2D u_texture0;

uniform mat4 u_world;

varying vec2 v_uv;

varying vec3 N;//
varying vec2 v_uv_blend;
varying vec3 v_pos;//modif din v4 in v3

void main()
{
vec3 pos_nou = a_posL;

vec4 c_blend =  texture2D(u_texture0, a_uv_blend);

pos_nou.y += c_blend.r*u_height.r+c_blend.g*u_height.g+c_blend.b*u_height.b;

gl_Position = u_mr * vec4(pos_nou, 1.0);

v_pos = (u_world * vec4(a_posL, 1.0)).xyz;
v_uv_blend = a_uv_blend;
v_uv = a_uv;

N = (u_world * vec4(a_norm, 0.0)).xyz;//
}
