precision mediump float;

attribute vec3 a_posL;

attribute vec3 a_color;

attribute vec3 a_norm;

varying vec3 v_color;

attribute vec2 a_uv;

varying vec2 v_uv;

uniform mat4 MVP;

uniform mat4 matrixModel;

varying vec3 Vposition;

varying vec3 v_posW;

varying vec3 v_normW;

void main()
{
	vec4 posL = vec4(a_posL, 1.0);

	Vposition = (matrixModel * posL).xyz;

	v_normW = normalize(matrixModel * vec4(a_norm,0.0)).xyz;

	v_posW = normalize(Vposition);

	v_color = a_color;

	v_uv = a_uv;
	
	gl_Position = MVP * posL;
}
   