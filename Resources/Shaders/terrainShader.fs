precision mediump float;

varying vec2 v_uv;
varying vec2 v_uv_blend;
varying vec3 v_pos;//modif

uniform sampler2D u_texture0;
uniform sampler2D u_texture1;
uniform sampler2D u_texture2;
uniform sampler2D u_texture3;
uniform float u_r;
uniform float u_R;
uniform vec3 u_cam;

//nou
varying vec3 N;
uniform vec3 c_amb;
uniform vec3 c_luminaDiff;
uniform vec3 c_luminaSpec;
uniform vec3 u_lights_type;
uniform vec3 L;
uniform vec3 LPoint;
uniform float specPower;
uniform float ratio;
uniform vec3 u_spot_pos;
uniform vec3 u_spot_direction;
uniform float u_spot_opening;

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

	//Lumini
	float ambientStrength = 1.0;
	vec4 Camb = c_final * vec4(c_amb * ambientStrength, 1.0); //ambientala
	vec3 l = normalize(L);
	vec3 n = normalize(N);
	vec3 R = reflect(l, n);
	vec3 E = normalize(u_cam - v_pos);
	vec3 lPoint = normalize(u_cam - LPoint);
	vec3 lSpot = normalize(u_cam - u_spot_pos);
	
	vec3 distanta = v_pos - u_spot_pos;
	float alfa = u_spot_opening;
	float beta = clamp(acos(dot(l, normalize(distanta))),0.0,alfa);
	
	vec4 Cdiff = c_final * vec4(c_luminaDiff * max(dot(n,-l), 0.0),1.0);
	vec4 Cspec = vec4(c_luminaSpec * pow(max(dot(R,E),0.0), specPower),1.0);
	vec4 CdiffPoint = c_final * vec4(c_luminaDiff * max(dot(n,-lPoint), 0.0),1.0);
	float aux = cos(beta * 3.14 / (2.0 * alfa));
	float aux1 = cos(beta * 3.14 / (2.0 * alfa));
	vec4 CdiffSpot = vec4(c_final.rgb * c_luminaDiff * max(dot(n,-lSpot), 0.0) * aux,1.0);

	vec4 CspecSpot = vec4(c_luminaSpec * pow(max(dot(R, E),0.0), specPower),1.0) * cos(beta * 3.14 / (2.0 * alfa)) ;
	
	vec4 Cfinal = ratio*Camb + (1.0-ratio)* (Cdiff + Cspec);
	vec4 Ctotal = ratio*Camb + u_lights_type.y*(1.0-ratio)* (Cdiff + Cspec) 
		+ u_lights_type.z * (1.0 - ratio) * (CdiffPoint + Cspec) + u_lights_type.x * (1.0 - ratio)*(CdiffSpot + CspecSpot);
	c_final = Ctotal;
	
	//ceata
	float d = distance(u_cam, v_pos);
	float alpha;
	alpha = (u_R - d) / (u_R - u_r);
	alpha = clamp(alpha, 0.0 , 1.0);
	vec4 cfog = c_final * alpha + vec4(178.0 / 225.0, 177.0 / 225.0, 179.0 / 225.0,1.0) * (1.0 - alpha);
	cfog.a = 1.0;
	gl_FragColor = cfog;
}
