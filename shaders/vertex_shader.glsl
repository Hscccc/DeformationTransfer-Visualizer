#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;

out vec3 FragPos; // For Phong shading
out vec3 Normal;  // For Phong shading
out vec3 GouraudColor; // For Gouraud shading

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;

void main() {
    // Transform vertex position
    FragPos = vec3(model * vec4(aPos, 1.0));
    gl_Position = projection * view * vec4(FragPos, 1.0);

    // Transform normal to world space
    Normal = normalize(mat3(transpose(inverse(model))) * aNormal);

    // Gouraud shading: calculate lighting in the vertex shader
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);

    vec3 ambient = vec3(0.1);
    vec3 diffuse = lightColor * diff;
    vec3 specular = lightColor * spec;

    GouraudColor = ambient + diffuse + specular; // Final color for Gouraud shading
}