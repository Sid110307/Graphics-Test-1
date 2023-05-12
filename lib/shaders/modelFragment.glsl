#version 330 core

in vec3 outputFragmentPosition;
in vec3 outputNormal;
in vec3 outputColor;
in vec2 outputTextureCoords;

out vec4 FragColor;

uniform sampler2D diffuseTexture;
uniform sampler2D specularTexture;

uniform vec4 lightColor;
uniform vec3 lightPosition;
uniform vec3 cameraPosition;

void main() {
    float ambience = 0.25f;

    vec3 normal = normalize(outputNormal);
    vec3 lightDirection = normalize(lightPosition - outputFragmentPosition);
    float diffuse = max(dot(normal, lightDirection), 0.0f);

    float specularStrength = 0.5f;
    vec3 viewDirection = normalize(cameraPosition - outputFragmentPosition);
    vec3 reflectDirection = reflect(-lightDirection, normal);
    float specular = pow(max(dot(viewDirection, reflectDirection), 0.0f), 32.0f);

    FragColor = texture(diffuseTexture, outputTextureCoords) * lightColor * (ambience + diffuse) + texture(specularTexture, outputTextureCoords).r * specularStrength * specular;
}
