precision mediump float; 

uniform samplerCube u_texture_0;

varying vec3 v_coord;

varying vec3 position;

uniform vec3 cameraPosition;

uniform mat4 matrixModel;

void main()
{
    vec4 culoare = textureCube(u_texture_0, v_coord);
    gl_FragColor = culoare;
}