precision mediump float;

varying vec3 v_color;

varying vec3 Vposition;

varying vec3 v_normW;

uniform samplerCube u_texture_0;

uniform vec3 cameraPosition;

uniform float smallR;

uniform float bigR;

uniform vec3 fogColor;	

void main()
{
    vec3 vectCam = Vposition - cameraPosition;
    vec3 dirReflect = reflect(normalize(vectCam),normalize(v_normW));

    vec4 skyColor = textureCube(u_texture_0, dirReflect);

    float d = distance(cameraPosition,Vposition);

    float alpha;
    if (d <= smallR)
        alpha = 0.0;
    if (d >= bigR)
        alpha = 1.0;
    if (d > smallR && d < bigR)
        alpha = (d - smallR) / (bigR - smallR);

    gl_FragColor=vec4(alpha * fogColor + (1.0 - alpha) * (0.5 * v_color + 0.5 * skyColor.xyz) , alpha);
}
