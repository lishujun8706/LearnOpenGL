#version 330 core

out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;

in vec3 Normal;
in vec3 FragPos;

uniform vec3 lightPos;
uniform vec3 viewPos;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};
uniform Material material;

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform Light light;

void main()
{
    // 漫反射
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);

    // 镜面光
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    vec3 ambient  = light.ambient * material.ambient;
    vec3 diffuse  = light.diffuse * (diff * material.diffuse);
    vec3 specular = light.specular * (spec * material.specular);

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);


    /*
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
    vec3 norm = normalize(Normal);

    // 简单地通过让两个向量相减的方式计算向量差
    vec3 lightDir = normalize(lightPos - FragPos);

    // 我们对norm和lightDir向量进行点乘，计算光源对当前片段实际的漫发射影响。
    // 结果值再乘以光的颜色，得到漫反射分量。两个向量之间的角度越大，漫反射分量就会越小
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // 现在我们有了环境光分量和漫反射分量，我们把它们相加，然后把结果乘以物体的颜色，来获得片段最后的输出颜色。
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 8);
    vec3 specular = specularStrength * spec * lightColor;

    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0);
    */
}
