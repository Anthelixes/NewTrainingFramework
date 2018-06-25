attribute vec3 a_posL;
attribute vec2 a_uv;
attribute vec2 a_uv_blend;

uniform mat4 u_mr;
uniform vec3 height;

uniform sampler2D u_texture0;

varying vec2 v_uv;
varying vec2 v_uv_blend;

void main()
{
vec3 pos_nou = a_posL;

vec4 c_blend =  texture2D(u_texture0, a_uv_blend);

pos_nou.y += c_blend.r*height.r+c_blend.g*height.g+c_blend.b*height.b;

gl_Position = u_mr * vec4(pos_nou, 1.0);

v_uv_blend = a_uv_blend;
v_uv = a_uv;
}
