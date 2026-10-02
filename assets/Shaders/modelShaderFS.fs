precision mediump float;

varying vec2 v_uv;

uniform sampler2D u_texture_0;

uniform samplerCube u_texture_1;

varying vec3 Vposition;

varying vec3 v_posW;

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
    vec3 vectCam = Vposition - cameraPosition;

    vec3 dirReflect = reflect(normalize(vectCam),normalize(v_posW));

    vec4 skyBoxColor = textureCube(u_texture_1, dirReflect);

    float d = distance(cameraPosition,Vposition);

    float alpha;
    if (d <= smallR)
        alpha = 0.0;
    if (d >= bigR)
        alpha = 1.0;
    if (d > smallR && d < bigR)
        alpha = (d - smallR) / (bigR - smallR);

    vec4 colorTexture = texture2D(u_texture_0,v_uv);

    if (colorTexture.a < 0.1) {
        discard;
    }

    vec3 L = normalize(Vposition - lightPosition);

    vec3 Cdiff = colorTexture.xyz * c_lightDiff * max(dot(v_normW,-L), 0.0);
    vec3 E = normalize(Vposition - cameraPosition);
    vec3 R = normalize(reflect(L,v_normW));
    vec3 Cspec = c_lightSpec * pow(max(dot(R,E), 0.0), SpecPower);

    float ratio = 0.5;

    vec3 Camb = colorTexture.xyz * c_amb;

    vec3 Cfinal = ratio * Camb + (1.0 - ratio) * (Cdiff + Cspec); 

    gl_FragColor =  vec4(alpha * fogColor + (1.0 - alpha) * (0.8 * Cfinal + 0.2 * skyBoxColor.xyz ),alpha);
}
