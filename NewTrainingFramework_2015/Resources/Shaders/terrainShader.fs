precision mediump float;

varying vec2 v_uv;
varying vec2 v_uv_blend;

uniform sampler2D u_texture0;
uniform sampler2D u_texture1;
uniform sampler2D u_texture2;
uniform sampler2D u_texture3;

void main()
{
	vec4 c_rock = texture2D(u_texture0, v_uv);
	vec4 c_glass = texture2D(u_texture1, v_uv);
	vec4 c_dirt = texture2D(u_texture2, v_uv);
	vec4 c_blend = texture2D(u_texture3, v_uv_blend);

	//gl_FragColor = c_blend;
	vec4 c_final = c_blend.r*c_rock + c_blend.g*c_glass + c_blend.b*c_dirt;
	c_final.a = 1.0;
	gl_FragColor = c_final;

	//gl_FragColor = vec4 (v_uv_blend.x, v_uv_blend.y, 0.0, 1.0);
	//gl_FragColor = vec4(v_uv.x, v_uv.y, 0.0, 1.0);
	//gl_FragColor = vec4(0.0, 0.0, 1.0, 1.0);
}
