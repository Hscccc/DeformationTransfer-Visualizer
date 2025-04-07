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
uniform vec3 objectColor;

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

    vec3 ambient = vec3(0.2) * objectColor; // 环境光
    vec3 diffuse = lightColor * diff * objectColor; // 漫反射
    vec3 specular = lightColor * spec; // 高光

    GouraudColor = ambient + diffuse + specular; // 将光照结果传递给片段着色器
}