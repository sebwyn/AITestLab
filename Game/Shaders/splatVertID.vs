#version 330

uniform int chunkSize;

layout(location = 0) in uint x8_y8_z8_null4_edge4;

out int layer;
out int vertID;

void main(){
    ivec3 pos = ivec3((x8_y8_z8_null4_edge4 >> 24) & uint(0xFF),
                      (x8_y8_z8_null4_edge4 >> 16) & uint(0xFF),
                      (x8_y8_z8_null4_edge4 >>  8) & uint(0xFF));
    uint edge = x8_y8_z8_null4_edge4 & uint(0x0F);
    pos.x *= 3;
    if(edge == uint(0)){
        pos.x += 1; 
    } else if(edge == uint(8)){
        pos.x += 2; 
    }
    //need to transform position to [-1,1]
    vec3 fpos = vec3(((float(pos.x)/(3*chunkSize))*2.0)-1.0, ((float(pos.y)/chunkSize)*2.0)-1.0, 0.0) + vec3(1.0/(2.0*chunkSize), 1.0/(2.0*chunkSize), 0.0);
    //vec3 fpos = vec3(float(pos.x)/(3*chunkSize), float(pos.y)/chunkSize, 0.0);
    gl_Position = vec4(fpos, 1.0);
    layer = pos.z;
    vertID = gl_VertexID;
} 
