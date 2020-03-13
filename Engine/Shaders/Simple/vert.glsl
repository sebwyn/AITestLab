#version 330

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexNormal;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

out vec3 fragNormal;

void main(){
    gl_Position = P*M * vec4(vertexPosition_modelspace, 1.0);
    fragNormal = normalize(M * vec4(vertexNormal,0.0)).xyz;
}
