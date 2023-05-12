#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 textureCoords;

out vec3 outputFragmentPosition;
out vec3 outputNormal;
out vec3 outputColor;
out vec2 outputTextureCoords;

uniform mat4 camMatrix;
uniform mat4 model;

void main() {
    outputFragmentPosition = vec3(model * vec4(position, 1.0f));
    outputNormal = normal;
    outputColor = color;
    outputTextureCoords = textureCoords;

    gl_Position = camMatrix * vec4(outputFragmentPosition, 1.0f);
}
