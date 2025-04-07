#version 330 core

in vec3 FragPos; // For Phong shading
in vec3 Normal;  // For Phong shading
in vec3 GouraudColor; // For Gouraud shading

out vec4 FragColor;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform int shadingMode; // 0 for Gouraud, 1 for Phong

void main() {
    if (shadingMode == 0) {
        // Gouraud shading: use interpolated color
        FragColor = vec4(GouraudColor, 1.0);
    } else {
        // Phong shading: calculate lighting in the fragment shader
        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(lightPos - FragPos);
        float diff = max(dot(norm, lightDir), 0.0);

        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);

        vec3 ambient = vec3(0.2) * objectColor;
        vec3 diffuse = lightColor * diff * objectColor;
        vec3 specular = lightColor * spec;

        FragColor = vec4(ambient + diffuse + specular, 1.0);
    }
}
