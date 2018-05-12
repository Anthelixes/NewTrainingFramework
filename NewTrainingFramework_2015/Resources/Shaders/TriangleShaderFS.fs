precision mediump float;
varying vec2 v_uv;
uniform sampler2D u_texture;
void main()
{
	//gl_FragColor = vec4(v_color, 1.0);
	gl_FragColor = texture2D(u_texture, v_uv);
	//gl_FragColor = vec4(v_uv.x, v_uv.y, 0.0, 1.0);
}
