precision mediump float;

uniform float U_Time;

uniform float U_DispMax;

varying vec2 v_uv;

uniform sampler2D u_texture_0;//textura_displacement

uniform sampler2D u_texture_1;//fireTexture

uniform sampler2D u_texture_2;//fireMask

varying vec3 Vposition;

uniform vec3 cameraPosition;

uniform mat4 matrixModel;

uniform float smallR;

uniform float bigR;

uniform vec3 fogColor;	

void main()
{    
    vec2 disp = texture2D(u_texture_0, vec2(v_uv.x, v_uv.y + U_Time)).xy;

    disp = (disp * 2.0 - 1.0) * U_DispMax;

    vec2 v_uv_displaced = v_uv + disp;

    vec4 c_fire = texture2D(u_texture_1, v_uv_displaced);

    vec4 c_fire_alpha = texture2D(u_texture_2, v_uv);

    c_fire.a = c_fire.a * c_fire_alpha.x;
    
    float d = distance(cameraPosition,Vposition);

    float alpha;
    if (d <= smallR)
        alpha = 0.0;
    if (d >= bigR)
        alpha = 1.0;
    if (d > smallR && d < bigR)
        alpha = (d - smallR) / (bigR - smallR);

    if(c_fire.a < 0.1) discard;

    gl_FragColor =  vec4(alpha * fogColor + (1.0 - alpha) * c_fire.xyz,alpha);
}
