precision mediump float; 

varying vec2 v_uv;
varying vec2 v_uv2;

uniform sampler2D u_texture_0;
uniform sampler2D u_texture_1;
uniform sampler2D u_texture_2;
uniform sampler2D u_texture_3;

uniform vec2 blendTextureOffset;

varying vec3 Vposition;

uniform vec3 cameraPosition;

uniform mat4 matrixModel;

uniform float smallR;

uniform float bigR;

uniform vec3 fogColor;

uniform vec3 lightPosition;

uniform vec3 c_lightDiff;

uniform vec3 c_lightSpec;

uniform float SpecPower;

uniform vec3 c_amb;

varying vec3 v_normW;

void main()
{
    vec4 c_dirt = texture2D(u_texture_0,v_uv);
    vec4 c_rock = texture2D(u_texture_1,v_uv);
    vec4 c_grass = texture2D(u_texture_2,v_uv); 

    vec2 uv_blend = v_uv2 + blendTextureOffset; 

    vec4 c_blend = texture2D(u_texture_3,uv_blend);

    vec4 c_final = c_blend.r * c_rock + c_blend.g * c_grass + c_blend.b * c_dirt;
    c_final.a = 1.0;

    float d = distance(cameraPosition,Vposition);

    float alpha;
    if (d <= smallR)
        alpha = 0.0;
    if (d >= bigR)
        alpha = 1.0;
    if (d > smallR && d < bigR)
        alpha = (d - smallR) / (bigR - smallR);

    vec3 L = normalize(Vposition - lightPosition);

    vec3 Cdiff = c_final.xyz * c_lightDiff * max(dot(v_normW,-L), 0.0);

    vec3 E = normalize(Vposition - cameraPosition);

    vec3 R = normalize(reflect(L,v_normW));
    
    vec3 Cspec = c_lightSpec * pow(max(dot(R,E), 0.0), SpecPower);

    float ratio = 0.5;

    vec3 Camb = c_final.xyz * c_amb;

    vec3 Cfinal = ratio * Camb + (1.0 - ratio) * (Cdiff + Cspec); 

    //gl_FragColor = vec4(c_lightDiff,1.0);
    gl_FragColor = vec4(alpha * fogColor + (1.0 - alpha) * Cfinal.xyz,alpha);
}
