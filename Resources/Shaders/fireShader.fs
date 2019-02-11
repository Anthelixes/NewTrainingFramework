precision mediump float;

varying vec2 v_uv;
varying vec3 v_pos;

uniform sampler2D u_texture0;
uniform sampler2D u_texture1;
uniform sampler2D u_texture2;

uniform float u_time;
uniform float u_dispMax;

uniform	float u_r;
uniform float u_R;
uniform vec3 u_cam;

void main()
{
	vec2 disp = texture2D(u_texture2, vec2(v_uv.x, v_uv.y + u_time)).rg;

	vec2 offset = disp * 2.0 * u_dispMax - u_dispMax;
	vec2 v_uv_disp = v_uv + offset;
	vec4 c_fire = texture2D(u_texture1, v_uv_disp);
	vec4 c_alpha = texture2D(u_texture0, v_uv);

	c_fire.a = c_fire.a * c_alpha.r;
	gl_FragColor = c_fire;	

	if (c_fire.a < 0.1)
		discard;

	//FOG
	float d = distance(u_cam, v_pos);
	float alpha;
	alpha = (u_R - d) / (u_R - u_r);
	alpha = clamp(alpha, 0.0 , 1.0);
	vec4 cfog = c_fire * alpha + vec4(178.0 / 225.0, 177.0 / 225.0, 179.0 / 225.0,1.0) * (1.0 - alpha);
	cfog.a = 1.0;
	gl_FragColor = cfog;
}
