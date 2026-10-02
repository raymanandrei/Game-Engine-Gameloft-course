precision mediump float; 

attribute vec3 a_posL;

attribute vec3 a_color;

attribute vec2 a_uv;

attribute vec2 a_uv2;

varying vec2 v_uv;

varying vec2 v_uv2;

varying vec3 v_color;

uniform mat4 MVP;

uniform sampler2D u_texture_3;//Blend

uniform vec3 u_height;

uniform mat4 matrixModel;

varying vec3 Vposition;

varying vec3 v_normW;

void main()
{
	vec4 c_blend = texture2D(u_texture_3,a_uv);
	v_uv = a_uv;
	v_uv2 = a_uv2;

	vec4 pos_nou = vec4(a_posL,1.0);

	pos_nou.y += c_blend.r * u_height.r + c_blend.g * u_height.g + c_blend.b * u_height.b;

	Vposition = (matrixModel * pos_nou).xyz;
	
	v_normW = normalize(matrixModel * vec4(0.0,1.0,0.0,0.0)).xyz;

	gl_Position = MVP * pos_nou;
}