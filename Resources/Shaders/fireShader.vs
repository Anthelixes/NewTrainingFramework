attribute vec3 a_posL;
attribute vec2 a_uv;

uniform mat4 u_mr;
uniform mat4 u_world;

varying vec2 v_uv;
varying vec3 v_pos;
void main()
{
vec4 posL = u_mr * vec4(a_posL, 1.0);

v_pos = (u_world * vec4(a_posL, 1.0)).xyz;//

gl_Position = posL;

v_uv = a_uv;
}
   