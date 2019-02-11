precision mediump float;

varying vec2 v_uv;
varying vec3 v_pos;
varying vec3 N;

uniform sampler2D u_texture0;
uniform	float u_r;
uniform float u_R;
uniform vec3 u_cam;

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
	vec4 culoare = texture2D(u_texture0, v_uv);
	if (culoare.a < 0.1)
		discard;

	//LUMINI
	float ambientStrength = 1.0;
	vec4 Camb = culoare * vec4(c_amb * ambientStrength, 1.0); //ambientala
	vec3 l = normalize(L);
	vec3 n = normalize(N);
	vec3 R = reflect(l, n);
	vec3 E = normalize(u_cam - v_pos);
	vec3 lPoint = normalize(u_cam - LPoint);
	vec3 lSpot = normalize(u_cam - u_spot_pos);

	vec3 distanta = v_pos - u_spot_pos;
	float alfa = u_spot_opening;
	float beta = clamp(acos(dot(l, normalize(distanta))),0.0,alfa);

	vec4 Cdiff = culoare * vec4(c_luminaDiff * max(dot(n,-l), 0.0),1.0);
	vec4 Cspec = vec4(c_luminaSpec * pow(max(dot(R,E),0.0), specPower),1.0);
	vec4 CdiffPoint = culoare * vec4(c_luminaDiff * max(dot(n,-lPoint), 0.0),1.0);

	float aux = cos(beta * 3.14 / (2.0 * alfa));
	float aux1 = cos(beta * 3.14 / (2.0 * alfa));
	vec4 CdiffSpot = vec4(culoare.rgb * c_luminaDiff * max(dot(n,-lSpot), 0.0) * aux,1.0);
	vec4 CspecSpot = vec4(c_luminaSpec * pow(max(dot(R, E),0.0), specPower),1.0) * cos(beta * 3.14 / (2.0 * alfa)) ;
	
	vec4 Cfinal = ratio*Camb + (1.0-ratio)* (Cdiff + Cspec);
	vec4 Ctotal = ratio*Camb + u_lights_type.y*(1.0-ratio)* (Cdiff + Cspec) 
		+ u_lights_type.z * (1.0 - ratio) * (CdiffPoint + Cspec) + u_lights_type.x * (1.0 - ratio)*(CdiffSpot + CspecSpot);
	culoare = Ctotal;
	//END LUMINI

	float d = distance(vec4(u_cam, 1.0), vec4(v_pos.xyz, 1.0));
	float alpha;
	alpha = (u_R - d) / (u_R - u_r);
	alpha = clamp(alpha, 0.0 , 1.0);
	vec4 cfog = culoare * alpha + vec4(178.0 / 225.0, 177.0 / 225.0, 179.0 / 225.0,1.0) * (1.0 - alpha);
	cfog.a = 1.0;
	gl_FragColor = cfog;
}