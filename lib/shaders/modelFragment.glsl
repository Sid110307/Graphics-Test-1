#version 330 core

in vec3 outputColor;
in vec2 outputTextureCoords;
in vec3 outputNormal;
in vec3 outputFragmentPosition;

out vec4 FragColor;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;

uniform vec4 lightColor;
uniform vec3 lightPosition;
uniform vec3 cameraPosition;

vec4 pointLight() {
    vec3 lightVector = lightPosition - outputFragmentPosition;
    float distance = length(lightVector);

    float intensity = 1.0f / (0.5f * distance * distance + 0.05f * distance + 1.0f);

    float ambience = 0.25f;
    vec3 normal = normalize(outputNormal);
    vec3 lightDirection = normalize(lightVector);
    float diffuse = max(dot(normal, lightDirection), 0.0f);

    float specularStrength = 0.5f;
    vec3 viewDirection = normalize(cameraPosition - outputFragmentPosition);
    vec3 reflectDirection = reflect(-lightDirection, normal);
    float specular = pow(max(dot(viewDirection, reflectDirection), 0.0f), 32.0f) * specularStrength;

    vec4 diffuseTex = vec4(texture(texture_diffuse1, outputTextureCoords).rgb * (diffuse + ambience), 1.0f);
    vec4 specularTex = vec4(texture(texture_specular1, outputTextureCoords).rgb * specular, 1.0f);

    return (diffuseTex + specularTex) * lightColor * intensity;
}

vec4 directionalLight() {
    float ambience = 0.25f;
    vec3 normal = normalize(outputNormal);
    vec3 lightDirection = normalize(vec3(1.0f, 1.0f, 0.0f));
    float diffuse = max(dot(normal, lightDirection), 0.0f);

    float specularStrength = 0.5f;
    vec3 viewDirection = normalize(cameraPosition - outputFragmentPosition);
    vec3 reflectDirection = reflect(-lightDirection, normal);
    float specular = pow(max(dot(viewDirection, reflectDirection), 0.0f), 32.0f) * specularStrength;

    vec4 diffuseTex = vec4(texture(texture_diffuse1, outputTextureCoords).rgb * (diffuse + ambience), 1.0f);
    vec4 specularTex = vec4(texture(texture_specular1, outputTextureCoords).rgb * specular, 1.0f);

    return (diffuseTex + specularTex) * lightColor;
}

vec4 spotLight() {
    float outerCone = 0.90f;
    float innerCone = 0.95f;

    float ambience = 0.25f;
    vec3 normal = normalize(outputNormal);
    vec3 lightDirection = normalize(lightPosition - outputFragmentPosition);
    float diffuse = max(dot(normal, lightDirection), 0.0f);

    float specularStrength = 0.5f;
    vec3 viewDirection = normalize(cameraPosition - outputFragmentPosition);
    vec3 reflectDirection = reflect(-lightDirection, normal);
    float specular = pow(max(dot(viewDirection, reflectDirection), 0.0f), 32.0f) * specularStrength;

    float angle = dot(vec3(0.0f, -1.0f, 0.0f), -lightDirection);
    float intensity = clamp((angle - outerCone) / (innerCone - outerCone), 0.0f, 1.0f);

    vec4 diffuseTex = vec4(texture(texture_diffuse1, outputTextureCoords).rgb * (diffuse + ambience), 1.0f);
    vec4 specularTex = vec4(texture(texture_specular1, outputTextureCoords).rgb * specular, 1.0f);

    return (diffuseTex + specularTex) * lightColor * intensity;
}

void main() {
    FragColor = spotLight();
}
