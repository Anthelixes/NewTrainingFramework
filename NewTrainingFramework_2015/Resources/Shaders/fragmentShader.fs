precision mediump float;
varying vec2 v_uv;
uniform sampler2D u_texture0;
void main()
{
	//gl_FragColor = vec4(v_color, 1.0);
	//gl_FragColor = texture2D(u_texture0, v_uv);
	vec4 culoare = texture2D(u_texture0, v_uv);
	if (culoare.a < 0.1)
		discard;
	gl_FragColor = culoare;
	//gl_FragColor = vec4(v_uv.x, v_uv.y, 0.0, 1.0);
	//gl_FragColor = vec4(0.0, 0.0, 1.0, 1.0);
}
