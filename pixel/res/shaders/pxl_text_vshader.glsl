#version 330 core

layout(location = 0) in vec4 vertex; // Position (xy) and texture coords (zw)
out vec2 TexCoords;

uniform mat4 projection;

void main() {
    gl_Position = projection * vec4(vertex.xy, 0.0, 1.0); // Apply projection
    TexCoords = vertex.zw; // Pass texture coordinates to the fragment shader
}