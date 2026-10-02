precision mediump float;

uniform vec3 objectColor;

attribute vec3 a_posL;

varying vec3 v_color;

uniform mat4 matrixModel;

uniform mat4 MVP;

varying vec3 Vposition;

varying vec3 v_normW;

void main()
{
	vec4 posL = vec4(a_posL, 1.0);

	Vposition = (matrixModel * posL).xyz;

	v_normW = normalize(Vposition);

	gl_Position = MVP * posL;

	v_color = objectColor;
}
   