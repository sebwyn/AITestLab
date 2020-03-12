
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

uniform vec2 tileSize;
uniform vec2 tile;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

out vec2 TexCoord;

void main()
{
    gl_Position = P*V*M * vec4(aPos, 1.0);
    TexCoord = vec2((tile.x*tileSize.x)+(aTexCoord.x*tileSize.x),(tile.y*tileSize.y)+(aTexCoord.y*tileSize.y));
}
